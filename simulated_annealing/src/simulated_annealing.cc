# include"../include/simulated_annealing.h"
# include"../include/load_infor.h"
# include<cstdlib>
# include<ctime>
# include<cmath>
# include<iostream>
# include<fstream>
namespace _M_evalutionary_optimization_algorithm
{
void simulated_annealing()
{
    srand((unsigned)time(NULL));
    // load information of cities
    auto cities = load_infor("data/cities");
    int total_number_of_cities = cities.size();
    // set params
    double K = 0.9;
    double T = total_number_of_cities*100;
    // init first solve
    std::vector<int> solve;
    for ( int city=0 ; city<total_number_of_cities ; city++ ){
        solve.push_back(city);
    }
    for( int i=0 ; i<total_number_of_cities/2 ; i++ ){
        int loc_1 = rand()%total_number_of_cities;
        int loc_2 = loc_1;
        while(loc_2 == loc_1){
            loc_2 = rand()%total_number_of_cities;
        }
        int tmp = solve[loc_1] ;
        solve[loc_1] = solve[loc_2];
        solve[loc_2] = tmp;
    }
    // some data
    double best_val = PathLen(cities,solve);
    std::vector<int> best_solve = solve;
    std::ofstream outfile;
    outfile.open("result",std::ofstream::ate);
    for(;K>0.6;T *=K){
        // candidate solve
        std::vector<int> candidate_solve = solve;
        int loc_1 = rand()%total_number_of_cities;
        int loc_2 = loc_1;
        while(loc_2 == loc_1){
            loc_2 = rand()%total_number_of_cities;
        }
        int tmp = candidate_solve[loc_1] ;
        candidate_solve[loc_1] = candidate_solve[loc_2];
        candidate_solve[loc_2] = tmp;
        double candidate_val = PathLen(cities,candidate_solve);
        if(candidate_val<PathLen(cities,solve)){
            solve = candidate_solve;
        }else{
            double tmp_rand = rand()/32767.0;
            if(tmp_rand < std::exp(PathLen(cities,solve)-candidate_val)/T){
                solve = candidate_solve;
            }
        }
        if(candidate_val<best_val){
            best_val = candidate_val;
        }
        outfile << "best val ever--" << best_val << std::endl;
    }
    outfile.close();
}
double PathLen(std::vector<city_infor> all_cities,std::vector<int> path)
{
    double pathLen = 0;
    for ( int city=0 ; city<all_cities.size()-1 ; city++ ){
        pathLen += distance(all_cities[path[city]],all_cities[path[city+1]]);
    }
    pathLen += distance(all_cities[0],all_cities[all_cities.size()-1]);
    return pathLen;
}
}// _M_evalutionary_optimization_algorithm