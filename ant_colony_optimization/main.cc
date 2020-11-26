# include<iostream> 
# include<string>
# include<vector>
# include"include/ant_colony_algorothm.h"

int main(int argc,char *argv[])
{
    std::vector<_M_evalutionary_optimization_algorithm::city_infor> cities = _M_evalutionary_optimization_algorithm::load_infor("data/countries");
    try {
    _M_evalutionary_optimization_algorithm::ant_colony_algorithm_for_TSP(cities);
    }catch(std::string e){
        std::cerr <<  e << std::endl;
    }
    // _M_evalutionary_optimization_algorithm::test_for_micro();
    return 0;
}