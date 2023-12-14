#include "sorting.hpp"

// ! *********************************************************************** ! //


int delivery[1005], size_pop = 20;

int eval_fitness(vector<int> route) {
    int sum = 0;
    for(int i = 1; i < route.size(); i++) {
        sum += d[route[i - 1]][route[i]];
    }
    return sum;
}

void createEachRoute(vector<int> given) {
    // reset the delivery array
    for(int i = 1; i <= N + M; i++) delivery[i] = false;
    vector<int> route;
    route.push_back(0);
    for(int i = 0; i < given.size(); i++) {
        if(given[i] <= N) {
            route.push_back(given[i]);
            route.push_back(given[i] + N + M);
        } else if(given[i] <= N + M && given[i] > N) 
            route.push_back(given[i]);
        
    }
    // TODO: generate the initial complete route
}

void createPopulation() {
    cerr << "Creating population\n";
    for(int p = 1; p <= 20; p++) {
        cerr << "Population " << p << '\n';
        for(int i = 1; i <= N + M; i++) {
            int index = Rand(0, K - 1);
            pop[p].temp[index].push_back(i);
            pop[p].temp[index].push_back(i);
        }
        for(int i = 0; i < K; i++)
            pop[p].temp[i].push_back(0);
        for(int k = 0; k < K; k++) {
            for(auto i:pop[p].temp[k]) {
                pop[p].routes[k].push_back(i);
                pop[p].routes[k].push_back(i + N + M);
            }
            pop[p].biggest = INT_MIN;
            int sum = eval_fitness(pop[p].routes[k]);
            pop[p].fitness[k] = sum;
            pop[p].isUseThisPop = true;
            pop[p].biggest = max(pop[p].biggest, sum);
        }
    }
    
}


void selection() {
    mergeSort(pop, 1, size_pop);
    for(int i = size_pop / 2 + 1; i <= size_pop; i++) {
        pop[i].isUseThisPop = false;
    }
    size_pop /= 2;
}

void crossover(population par1, population par2) {
    
}