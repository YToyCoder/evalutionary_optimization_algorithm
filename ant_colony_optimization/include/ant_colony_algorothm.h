// ant colony algorithm
# if !defined(_ANT_COLONY_ALGORITHM_H)
# define _ANT_COLONY_ALGORITM_H
# include<vector>
# include<string>
# define GET_PATH_LOC(i,j) (( ((i)>(j))? ((((i)-1)*(i))/2 + (j)+1) : (((j)*((j)-1))/2 + (i)+1) )-1)
// >>> ant colony algorithm <<<
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
void ant_colony_algorithm_for_TSP(std::vector<city_infor> cities);
void test_for_micro();
} // _M_evalutionary_optimization_algorithm

# endif