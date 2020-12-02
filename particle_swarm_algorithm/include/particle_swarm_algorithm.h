# if !defined(_PARTICLE_SWARM_ALGORITHM_H)
# define _PARTICLE_SWARM_ALGORITHM_H
# include<vector>
# include<cstdlib>

namespace _M_evalutionary_optimization_algorithm
{
typedef std::vector<double> variables_t;
# define VAR_MAX 100
# define VAR_MIN -100

double Uniform(double min,double max);
double distanceBetween(variables_t a,variables_t b);
double function(std::vector<double> variables);
std::vector<int> get_neighborhood(std::vector<variables_t> pop,int self_loc,int neighborhood_size);
variables_t argmin(std::vector<variables_t> neighborhoods);
void particle_swarm_algorithm();
} // _M_evalutionary_optimization_algorithm

# endif