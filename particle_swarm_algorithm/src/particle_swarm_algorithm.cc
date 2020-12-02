# include"../include/particle_swarm_algorithm.h"
# include<vector>
# include<string>
# include<fstream>
# include<sstream>
# include<cmath>
# include<ctime>
# include<iostream>

namespace _M_evalutionary_optimization_algorithm
{
// n 元函數
double function(std::vector<double> variables)
{
    double val = 0;
    for(int i=0;i<variables.size() ; i++)
        if (i%2 == 0) val += (i+1)*variables[i]*variables[i];
        else val += (i+1)*variables[i]*variables[i];
    return val;
}
double Uniform(double min,double max){
    return (max-min)*((double)rand()/32767.0)+min;
}
// distance between two individual
double distanceBetween(variables_t a , variables_t b)
{
    double distance = 0;
    for (int i=0 ; i<a.size() && i<b.size() ; i++){
        distance += std::abs(a[i]-b[i]);
    }
    return distance;
}
// get the closest neighborhood_size neiborhoods of self_loc
std::vector<int> get_neighborhood(std::vector<variables_t> pop,int self_loc,int neighborhood_size)
{
    std::vector<double> distance(pop.size());
    std::vector<int> neighborhoods;
    // for all individual in pop
    for(int ind=0 ; ind<pop.size() ; ind++ ){
        distance[ind] = distanceBetween(pop[self_loc],pop[ind]);
        neighborhoods.push_back(ind);
        // insert ind to neighborhoods
        for(int neighbor=neighborhoods.size()-1 ; neighbor>0 ; --neighbor ){
            if( distanceBetween(pop[self_loc] ,pop[neighborhoods[neighbor]])<
                distanceBetween(pop[self_loc],pop[neighborhoods[neighbor-1]])){
                int tmp = neighborhoods[neighbor];
                neighborhoods[neighbor] = neighborhoods[neighbor-1];
                neighborhoods[neighbor-1] = tmp;
            }else{
                break;
            }
        }
        // to keep the neighborhood size
        if(neighborhoods.size() > neighborhood_size){
            neighborhoods.erase(--neighborhoods.end());
        }
    }
    return neighborhoods;
}
variables_t argmin(std::vector<variables_t> neighborhoods)
{
    variables_t min_ind = neighborhoods[0];
    for( int ind=1 ; ind<neighborhoods.size() ; ind++ ){
        if(function(neighborhoods[ind])<function(min_ind)){
            min_ind = neighborhoods[ind];
        }
    }
    return min_ind;
}
void particle_swarm_algorithm()
{
    srand((unsigned)time(NULL));
    int N = 10 ;// pop-size
    int var_size = 4;
    std::vector<variables_t> pop(N);
    for(int ind=0 ; ind<N ; ind++){
        for (int var_loc=0 ; var_loc<var_size ; var_loc++){
            pop[ind].push_back(rand()%(VAR_MAX-VAR_MIN)+VAR_MIN+1);
        }
    }
    // init v by 0
    std::vector<variables_t> v(N);
    for(int ind=0 ; ind<N ; ind++){
        for(int var_loc=0 ; var_loc<var_size ; var_loc++ ){
            v[ind] = variables_t(var_size,0);
        }
    }
    std::vector<variables_t> best_loc = pop;
    int neighborhood_size = 5;
    // 定义最大影响值
    double sigma1 = 2.05;
    double sigma2 = 2.05;
    // max velocity(speed)
    variables_t max_v = {2.0,2.0,3.0,2.5};
    // mian loop
    for (int loop=0 ; loop<100 ; loop++ ){
        // loop for every individual in pop
        for ( int ind= 0 ; ind<N ; ind++ ){
            std::vector<variables_t> neighborhood;
            for(int neighbor:get_neighborhood(pop,ind,neighborhood_size)){
                neighborhood.push_back(pop[neighbor]);
            }
            variables_t h = argmin(neighborhood);
            // simple version(random effective variable)
            double sigma1_var = Uniform(0,sigma1);
            double sigma2_var = Uniform(0,sigma2);
            variables_t v_var = v[ind];
            for(int var=0; var<v[ind].size() ; var++ ){
                v_var[var] += sigma1_var*(best_loc[ind][var]-pop[ind][var]) + 
                                sigma2_var*(h[var]-pop[ind][var]);
            }
            for(int var=0 ; var<max_v.size() ; var++ ){
                if(std::abs(v_var[var])>max_v[var]){
                    v_var[var] = v_var[var]*max_v[var]/std::abs(v_var[var]);
                }
            }
            v[ind]=v_var;
            for(int var=0 ; var<var_size ; var++ ){
                pop[ind][var] += v_var[var];
            }
            for (int var=0; var<var_size ; var++ ){
                pop[ind][var] += v[ind][var];
            }
            std::vector<variables_t> tmp{pop[ind],best_loc[ind]};
            best_loc[ind] = argmin(tmp);
            std::cout << "best-individual - val:" << function(best_loc[ind]) << std::endl;
        }
    }
}

} // _M_evalutionary_optimization_algorithm