# include"../include/differential_algorithm.h"
# include<vector>
# include<iostream>
# include<cstdlib>
# include<ctime>

namespace _M_evalutionary_optimization_algorithm
{
// @param double min
// @param double max
// @return double Uniform-distribution-val
double Uniform(double min,double max){
    return (max-min)*((double)rand()/32767.0)+min;
}
// @param std::vector<double> variables
// @return double result
double objective_function(std::vector<double> vars)
{
    double result = 0;
    for (size_t i = 0; i < vars.size() ; i++){
        if( i%2 == 0 )
            result += vars[i]*vars[i];
        else result -= vars[i]*vars[i];
    }
    return result;
}
// classic differential algorithm 
// reference book :《進化優化算法-基於仿生和種群的計算機智能方法》
void differential_algorithm()
{
    srand((unsigned)time(NULL));
    int pop_size = 10 ;// 種群大小
    double best_val = (double)INT_MAX;// 初始化最優值為最大值
    variables_t best_ind;
    double F = 0.4;// 0.4~0.9
    double crossover_p = 0.1;//交叉概率
    // init pop
    std::vector<variables_t> pop(pop_size);
    for(int ind=0 ; ind<pop_size ; ind++){
        for (int var=0 ; var<VARLEN ; var++)
            pop[ind].push_back(Uniform(VARMIN,VARMAX));
        double ind_val = objective_function(pop[ind]);
        if ( ind_val < best_val){
            best_val = ind_val;
            best_ind = pop[ind];
        }
        std::cout << best_val << std::endl;
    }
    int generation_size = 100;
    // main loop
    for ( int generation=0 ; generation<generation_size ; generation++ ){
        std::vector<variables_t> u_pop(pop_size);// store for all individual coming from crossover and mutate
        for ( int ind=0 ; ind<pop_size ; ind++ ){
            // select 變異向量
            int r1 = rand()%pop_size;
            int r2 = r1;
            int r3 = r1;
            while(r2 == r1) r2 = rand()%pop_size;
            while(r3 == r1 || r3 == r2 ) r3 = rand()%pop_size;
            variables_t v(VARLEN);
            // crossover?
            for (int var=0 ; var<VARLEN ; var++ )
                v[var] = pop[r1][var] + F*(pop[r2][var] - pop[r3][var]);
            int rand_j = rand()%VARLEN;
            for ( int var=0 ; var<VARLEN ; var++){
                double rand_p = Uniform(0,1);
                if ( rand_p < crossover_p || var == rand_j )
                    u_pop[ind].push_back(v[var]);
                else u_pop[ind].push_back(pop[ind][var]);
            }
            if ( objective_function(u_pop[ind])<best_val){
                best_val = objective_function(u_pop[ind]);
                best_ind = u_pop[ind];
            }
        }
        // select better individual
        for ( int ind=0 ; ind<pop_size ; ind++ )
            if ( objective_function(u_pop[ind])<objective_function(pop[ind]))
                pop[ind] = u_pop[ind];
        std::cout << best_val << std::endl;
    }
}
} // _M_evalutionary_optimization_algorithm