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

const int max_iter = 1000;

int delivery[1005], size_pop = 20;

vector<pair<int, int>> create_cycle_for_each(vector<int> route) {
    vector<pair<int, int>> fullRoute;
    for(int i = 0; i < route.size(); i++) {
        int node = route[i];
        if(node == 0) fullRoute.push_back({0, -1});
        else {
            if(node <= N) fullRoute.push_back({node, node + N + M});
            else {
                fullRoute.push_back({node, -1});
                fullRoute.push_back({node + N + M, -1});
            }
        }
    }
}

void eval_fitness(vector<int> origin_config) {
    vector<int> temp[K + 5];
    temp[0].push_back(0);
    int k = 0;
    cerr << origin_config.size() << '\n';
    for(int i = 1; i < origin_config.size(); i++) {
        if(origin_config[i] != 0) temp[k].push_back(origin_config[i]);
        else {
            temp[k].push_back(0);
            k++;
            temp[k].push_back(0);
        }
    }
    // Create full cycle for each route
    // Calculate lenght for each route in a config
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
        bool ok = true;
        while(1) {
            ok = true;
            for(int i = 1; i < t.size(); i++) {
                if(t[i] == 0 && t[i - 1] == 0) ok = false;
            }
            if(ok == true) break;
            else random_shuffle(t.begin() + 1, t.end() - 1);
        }
        pop[p].route = t;
        //* route: pop[p].route
    }
}