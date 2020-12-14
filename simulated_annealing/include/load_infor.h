# if !defined(_LOAD_INFOR_H)
# define _LOAD_INFOR_H
# include<vector>
# include<string>
namespace _M_evalutionary_optimization_algorithm
{
struct city_infor
{
    city_infor() = default;
    city_infor(double x_ , double y_ ):x(x_),y(y_){}
    double x;
    double y;
};
std::vector<city_infor> load_infor(std::string path);
double distance(city_infor a, city_infor b);
double PathLen(std::vector<city_infor> all_cities,std::vector<int> path);
}// _M_evalutionary_optimization_algorithm
# endif