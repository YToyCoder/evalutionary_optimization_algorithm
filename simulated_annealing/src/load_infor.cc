# include"../include/load_infor.h"
# include<fstream>
# include<sstream>
# include<cmath>
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
}// _M_evalutionary_optimization_algorithm