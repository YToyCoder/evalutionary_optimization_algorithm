// differential algorithm
# if !defined(_DIFFERENTIAL_ALGORITHM_H)
# define _DIFFERENTIAL_ALGORITHM_H
# include<vector>
# include<cstdlib>
namespace _M_evalutionary_optimization_algorithm
{
# define VARLEN 4
# define VARMAX 10
# define VARMIN -10
typedef std::vector<double> variables_t;
double Uniform(double min,double max);
double objective_function(std::vector<double> vars);
void differential_algorithm();
} // _M_evalutionary_optimization_algorithm

# endif