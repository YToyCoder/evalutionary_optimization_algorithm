# if !defined(_PARTICLE_SWAM_ALGORITHM_H)
# define _PARTICLE_SWAM_ALGORITHM_H

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
void particle_swam_algorithm();
} // _M_evalutionary_optimization_algorithm

# endif