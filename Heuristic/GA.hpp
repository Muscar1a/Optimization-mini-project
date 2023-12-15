#include "declaration.hpp"

// ! *********************************************************************** ! //

/*
1. Initial population
2. Evaluation fitness -> remove weakness individual
3. Selection
4. Crossover
5. Mutation

*/

// ! *********************************************************************** ! //


int delivery[1005], size_pop = 20;

int eval_fitness(vector<int> route) {
    int sum = 0;
    for(int i = 1; i < route.size(); i++) {
        sum += d[route[i - 1]][route[i]];
    }
    return sum;
}


void createPopulation() {
    vector<int> t;
    for(int i = 1; i <= K; i++)
        t.push_back(0);
    for(int i = 1; i <= N + M; i++) 
        t.push_back(i);
    t.push_back(0);
    for(int p = 1; p <= 20; p++) {
        random_shuffle(t.begin() + 1, t.end() - 1);
        pop[p].route = t;
    }
    for(int p = 1; p <= 10; p++) {
        cerr << p << '\n';
        for(auto i:pop[p].route) cerr << i << ' ';
        cerr << '\n';
    }
}