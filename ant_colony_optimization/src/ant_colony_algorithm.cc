# include"../include/ant_colony_algorothm.h"
# include<vector>
# include<set>
# include<cmath>
# include<ctime>
# include<cstdlib>
# include<string>
# include<fstream>
# include<cstdlib>
# include<cstdio>
# include<sstream>
# include<algorithm>
# include<numeric>
# include<iostream>
# include<climits>
# include<cassert>

namespace _M_evalutionary_optimization_algorithm
{
// @param std::string file path
// @return std::vector<city_infor> vector for city_infor class ( location information )
std::vector<city_infor> load_infor(std::string path)
{
    std::ifstream infile(path);
    std::string line;
    std::vector<city_infor> cities;
    while (std::getline(infile,line))
    {
        std::istringstream sline(line);
        int x;
        int y;
        sline >> x >> y;
        cities.push_back(city_infor(x,y));
    }
    infile.close();
    return cities;
};

// @param city_infor city a
// @param city_infor city b
// @return double distance between a and b
double distance(city_infor a, city_infor b)
{
    double x_2 = std::abs(a.x-b.x);
    double y_2 = std::abs(a.y-b.y);
    return std::sqrt(std::pow(x_2,2)+std::pow(y_2,2));
}

// @param size_t size of a group of cities
// @return std::vector<double> 
std::vector<double> init_path(size_t cities_size)
{
    std::vector<double> all_path(cities_size*(cities_size-1));
    return all_path;
}

// reference book :《進化優化算法-基於仿生和種群的計算機智能方法》【美】丹·西蒙 清華大學出版社
// @param std::vector<city_infor> all city location information
void ant_colony_algorithm_for_TSP( std::vector<city_infor> cities )
{
    std::ofstream outfile;
    outfile.open("distance",std::ofstream::ate);
    srand((unsigned)time(NULL));
    int cities_size = cities.size();
    std::set<int> cities_number;
    for(int i=0;i<cities_size ; i++)
        cities_number.insert(i);

    // 信息素與啓發式信息的想讀重要性
    double alpha = 1;
    double beta  = 4;
    // 沉積常數
    int Q        = 100;
    // 揮發率
    double rho   = 0.6;
    // 城市之間的信息素
    double kao_0   = std::pow(10,-3);
    std::vector<double> pheromones = init_path(cities_size);
    for(int i=0 ; i<pheromones.size() ; i++)
        pheromones.at(i)=kao_0;
    // 蟻群大小
    int ant_colony_size = 10;
    double best_distance = INT32_MAX;
    std::vector<int> best_solve(cities_size);
    std::vector<std::set<int>> ant_cities_number;
    for(int i=0 ; i<1000 ; i++)
    {
        ant_cities_number.clear();
        // init ant colony size array to store path for every ant
        std::vector<std::vector<int>> ant_colony_path(ant_colony_size);
        // init starting cities of ant for every ant
        for(int i=0 ; i< ant_colony_size ; i++)
            ant_cities_number.push_back(cities_number);
        for(int ant=0 ; ant < ant_colony_size ; ant++)
        {
            ant_colony_path[ant].clear();
            ant_colony_path[ant].push_back(rand()%cities_size);
            std::set<int>::iterator ant_iter = ant_cities_number[ant].find(*ant_colony_path[ant].rbegin());
            if(ant_iter == ant_cities_number[ant].end())
                throw "can not find cities in ant_cities_number :(" + std::to_string(ant)+" )";
            ant_cities_number[ant].erase(ant_iter);
        }
        for(int q=1 ; q < cities_size ; q++)
        {
            // next rest cities
            for(int ant=0 ; ant<ant_colony_size ; ant++)
            {
                int current_city = *ant_colony_path[ant].rbegin();
                std::vector<double> p(cities_size,0.0);
                for(int rest_cities:ant_cities_number[ant])
                    p[rest_cities] =std::pow(pheromones[GET_PATH_LOC( current_city,rest_cities)],alpha)/
                                    std::pow(distance(cities[current_city],cities[rest_cities]),beta);
                    
                double sum = std::accumulate(p.begin(),p.end(),0.0);
                for(int i=0; i<p.size() ; i++)
                    p[i] = p[i]/sum ;
                // Uniform Distribution 0-1(fake)
                double rand_p = rand()/32767.0;
                // select city
                sum = 1 ;
                for( int rest_cities:ant_cities_number[ant])
                {
                    sum -= p[rest_cities];
                    if(rand_p >= sum){
                        current_city = rest_cities;
                        goto label_1;
                    }
                }
                label_1:
                ant_colony_path[ant].push_back(current_city);
                // delete city from set in case repeating selecting
                ant_cities_number[ant].erase(current_city);
            }
        }
        for(int phe_loc=0 ; phe_loc<pheromones.size() ; phe_loc++)
            pheromones[phe_loc] *= (1-rho);
        for( std::vector<int> path_for_ant_k:ant_colony_path)
        {
            double sum_len = 0;
            for(int city=0 ; city<path_for_ant_k.size()-1 ; city++)
                sum_len += distance(cities[path_for_ant_k[city]],cities[path_for_ant_k[city+1]]);
            sum_len += distance(cities[0],cities[cities.size()-1]);
            if(sum_len < best_distance)
            {
                best_distance = sum_len;
                best_solve = path_for_ant_k;
            }
            // std::cout << best_distance << std::endl;
            outfile << best_distance << std::endl;
            for(int city = 0 ; city < path_for_ant_k.size() -1 ; city++)
                pheromones[GET_PATH_LOC(path_for_ant_k[city],path_for_ant_k[city+1])] = Q/sum_len;
        }
    }
    for( int it:best_solve)
        outfile << it << " " ;
    outfile << std::endl;
    outfile.close();
}
void test_for_micro()
{
    std::cout << ">>> test for micro <<<" << std::endl;
    std::cout << "i = 1 && j = 2 : " << GET_PATH_LOC(1,2) << std::endl;
}
}// _M_evalutionary_optimization_algorithm