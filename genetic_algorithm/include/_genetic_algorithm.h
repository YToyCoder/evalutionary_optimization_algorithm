# if !defined(_GENETICALGORITHM_H)
# define _GENETICALGORITHM_H
# include<vector>
# include"../include/load_infor.h"
namespace _M_evalutionary_optimization_algorithm
{
// @param double min
// @param double max
// @return double Uniform-distribution-val
double Uniform(double min,double max);
double objective_function(const std::vector<int>& chromosome,const std::vector<city_infor>& cities);
std::vector<std::vector<int> > selectParents(const std::vector<std::vector<int> >& pop,const std::vector<city_infor>& cities);
std::vector<std::vector<int> > crossover(std::vector<int>& p1,std::vector<int>& p2);
void mutate(std::vector<int>& ind,double mutate_probability);
void genetic_algorithm();
}// _M_evalutionary_optimization_algorithm
# endif