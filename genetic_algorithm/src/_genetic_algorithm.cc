# include"../include/_genetic_algorithm.h"
# include"../include/load_infor.h"
# include<vector>
# include<iostream>
# include<ctime>
namespace _M_evalutionary_optimization_algorithm
{
// @param double min
// @param double max
// @return double Uniform-distribution-val
double Uniform(double min,double max){
    return (max-min)*((double)rand()/32767.0)+min;
}
void genetic_algorithm(){
  srand((unsigned)time(NULL)*10);
  auto cities = load_infor("../data/cities");
  int pop_size = 30;
  double mutate_probability = 0.2;
  int generation_size = 1000;
  double best = INT_MAX;

  // chromomose prototype
  std::vector<int> prototype(cities.size());
  for(int gene=0 ; gene<cities.size(); ++gene){
    prototype[gene] = gene;
  }
  // init pop 
  std::vector<std::vector<int> > pop(pop_size);
  for(int ind=0 ; ind<pop_size; ++ind){
    for(int shift=0 ; shift<cities.size()/2 ; ++shift){
      std::size_t other = Uniform(shift+1,cities.size());
      int tmp = prototype[shift];
      prototype[shift] = prototype[other];
      prototype[other] = tmp ;
    }
    double res = objective_function(prototype,cities);
    if(best>res){
      best=res;
      std::cout << best << std::endl;
    }
    pop[ind]=prototype;
  }
  for(int generation=0 ; generation<generation_size ; ++generation){
    std::vector<std::vector<int> > new_generation;
    for(int ind=0 ; ind<pop_size; ++ind){
      // select parents
      auto parents = selectParents(pop,cities);
      auto children = crossover(parents[0],parents[1]);
      for(std::vector<int>& child:children){
        mutate(child,mutate_probability);
        double res = objective_function(child,cities);
        if(best>res){
          best=res;
          std::cout << best << std::endl;
        }
      }
      for(std::vector<int>& child:children){
        new_generation.push_back(child);
      }
    }
    pop = new_generation;
  }
}

double objective_function(const std::vector<int>& chromosome,const std::vector<city_infor>& cities){
  double res = 0;
  for(int city=1 ; city<cities.size(); ++city){
    res += distance(cities[chromosome[city]],cities[chromosome[city-1]]);
  }
  res += distance(cities[chromosome[0]],cities[chromosome[chromosome.size()-1]]);
  return res;
}
std::vector<std::vector<int> > selectParents(const std::vector<std::vector<int> >& pop,const std::vector<city_infor>& cities){
  double max_v = INT_MAX;
  double min_v = 0;
  std::vector<double> vals;
  for(int i=0 ; i<pop.size(); ++i){
    vals.push_back(objective_function(pop[i],cities));
    if(vals[i]< min_v ){
      min_v = vals[i];
    }
    if(vals[i]> max_v){
      max_v = vals[i];
    }
  }

  double sum = 0;
  for(int i=0 ; i<pop.size() ; ++i){
    vals[i] = max_v - vals[i];
    sum += vals[i];
  }
  // 归一化
  for(int i=0 ;i<pop.size() ; ++i){
    vals[i] = vals[i]/sum;
  }
  // 选择
  double random_v1 = Uniform(0,1);
  double random_v2 = random_v1;
  int p1 = -1;
  int p2 = -1;
  while(random_v1==random_v2){
    random_v2 = Uniform(0,1);
  }
  sum = 0;
  for(int i=0; i<pop.size(); ++i){
    if(random_v1>sum && random_v1<sum+vals[i]){
      p1 = i;
    }
    if(random_v2>sum && random_v2<sum+vals[i]){
      p2 = i;
    }
  }
  p1 == -1 ? (p1=pop.size() -1 ):0;
  p2 == -1 ? (p2=pop.size() -1 ):0;
  return std::vector<std::vector<int> >{pop[p1],pop[p2]};
}
std::vector<std::vector<int> > crossover(std::vector<int>& p1,std::vector<int>& p2){
  std::vector<std::vector<int> > children{p1,p2};
  int start = Uniform(0,p1.size());
  int end   = Uniform(0,p1.size());
  int tmp   = start;
  if(tmp > end ){
    start = end;
    end   = tmp;
  }
  for(;start<=end;++start){
    children[0][start] = p2[start];
    children[1][start] = p1[start];
  }
  return children;
}
void mutate(std::vector<int>& ind,double mutate_probability){
  for(int i=0 ; i<ind.size(); ++i){
    double random_v = Uniform(0,1);
    if(random_v<mutate_probability){
      std::swap(ind[i],ind[(int)Uniform(0,ind.size()-1)]);
    }
  }
}

}// _M_evalutionary_optimization_algorithm