#include "tabusearch.hpp"

// ! *********************************************************************** ! //

/*
1. Initial population
2. Evaluation fitness -> remove weakness individual
3. Selection
4. Crossover
5. Mutation

*/

//* the struct population is just storing only one route with k + 1 nnumbers zero
//* meanwhile tabu search need vector<pair<int, int>> as input

// ! *********************************************************************** ! //

const int SIZEofPopulation = 16;
const int tournament_size = 4;
const double mutation_rate = 0.2;
const double crossover_rate = 0.5;

int delivery[1005], size_pop = 20;

vector<vector<int>> partial_full_pop;
vector<int> temp;
vector<vector<pii>> full_pop;

vector<pii> create_cycle_for_each(vector<int> route) {
    vector<pii> fullRoute;
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
    return fullRoute;
}

vector<vector<pii>> create_full_route(vector<int> route) {
    temp.clear(), partial_full_pop.clear();
    for(int i = 0; i < route.size(); i++) {
        if(i == 0) {
            temp.push_back(0);
            continue;
        }
        if(route[i] == 0) {
            temp.push_back(0);
            partial_full_pop.push_back(temp);
            temp.clear();
            temp.push_back(0);
        } else temp.push_back(route[i]);
    }
    full_pop.clear();
    for(auto i:partial_full_pop) {
        //for(auto j:i) cout << j << ' ';
        full_pop.push_back(create_cycle_for_each(i));
        //cout << '\n';
    }
    return full_pop;
}

int return_biggest_fitness_each_config(vector<int> child) {
    vector<vector<pii>> meo = create_full_route(child);
    int biggest_fitness = 0;
    for(auto x:meo) {
        int tmp = tabu_search_return_fitness(x);
        biggest_fitness = max(biggest_fitness, tmp);
    }
    return biggest_fitness;
}

//* createPopulation is ok
void createPopulation() {
    // cerr << "Create population\n";
    vector<int> t;
    for(int i = 1; i <= K; i++)
        t.push_back(0);
    for(int i = 1; i <= N + M; i++) 
        t.push_back(i);
    t.push_back(0);
    for(int p = 0; p < SIZEofPopulation; p++) {
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
        pop.push_back({t, 0});
    }

    //* original size of 'pop' = 1000
    // temp to create a full route, but just trying
    for(int x = 0; x < SIZEofPopulation; x++) {
        /* 
        cout << "Route " << x + 1 << ": ";
        for(int i = 0; i < pop[x].route.size(); i++) cout << pop[x].route[i] << ' ';
        cout << '\n' << "Discreting route: \n";
        */
        vector<vector<pii>> meomeo = create_full_route(pop[x].route);
        /* cout << "x = " << x << '\n';
        cout << "Size of vector meomeo: " << meomeo.size() << '\n';
        cout << "Original route\n"; 
        for(auto i:meomeo) {
            for(auto j:i) {
                if(j.first >= 1 && j.first <= N) cout << j.first << ' ' << j.second << ' ';
                else cout << j.first << ' ';
            }
            cout << '\n';
        }*/
        int biggest_fitness = 0;

        //* remind that the population fitness must store the value of longest route among routes;
        //* tabu search just return the shortest path among variation of combination of routes
        
        // cout << "Start tabu searching\n";
        for(auto x:meomeo) {
            // REACH;
            int tmp = tabu_search_return_fitness(x);
            /*for(auto i:tmp) {
                if(i.first >= 1 && i.first <= N) cout << i.first << ' ' << i.second << ' ';
                else cout << i.first << ' ';
            }
            cout << "\n\n";*/
            biggest_fitness = max(biggest_fitness, tmp);
        }
        pop[x].biggest_fitness_among_routes = biggest_fitness;
        // cout << pop[x].biggest_fitness_among_routes << '\n';
    }
    /* 
    for(int p = 0; p < SIZEofPopulation; p++) {
        cout << "p = " << p + 1 << " - " << pop[p].biggest_fitness_among_routes << ":\n";
        for(auto i:pop[p].route) cout << i << ' ';
        cout << " - " << pop[p].biggest_fitness_among_routes << '\n';
    
    }
     */
}

//* tournament is ok
population tournament(vector<population> pop, int tournament_size) {
    //!cerr << "Tournament\n";
    //!cerr << pop.size() << '\n';
    population select;
    int smallest_fitness = INT_MAX;
    for(int p = 0; p < tournament_size; p++) {
        int random_index = Rand(0, pop.size() - 1); 
        population par = pop[random_index];
        //!for(auto i:par.route) cerr << i << " ";
        //!cerr << " - " << par.biggest_fitness_among_routes << '\n';
        if(smallest_fitness > par.biggest_fitness_among_routes) {
            //!REACH;
            smallest_fitness = par.biggest_fitness_among_routes;
            select = par;
        }
    }
    // cerr << "The selected parent\n";
    // for(auto i:select.route) cerr << i << " ";
    //* after a while for searching, it seems that no need to reduce the size of populations
    //! after tournament step, the size of population will be reduced
    /*sort(prepare_to_del.begin(), prepare_to_del.end(), greater<int>());
    for(auto i:prepare_to_del) {
        pop.erase(pop.begin() + i);
    }*/
    //!cerr << "Selected chromosome after tournament:\n";
    //!for(auto i:select.route) cerr << i << ' ';
    //!cerr << " - " << select.biggest_fitness_among_routes << '\n';
    return select;    
}

//* making_children is ok
pair<vector<int>, vector<int>> making_children(vector<int> par1, vector<int> par2) {
    int sz = par1.size();
    int point1 = sz / 3;
    int point2 = sz / 3  + point1 - 1;
    int ok1[2005], ok2[2005];
    // ok1 and ok2 are counting arrays, notice that ok1[0] and ok2[0] must <= K - 1
    vector<int> child1 = par1, child2 = par2;
    for(int i = point1; i <= point2; i++) {
        ok1[child1[i]]++;
        ok2[child2[i]]++;
    }
    int cnt1 = 1, cnt2 = 1;
    for(int i = 1; i < sz - 1; i++) {
        if(cnt1 == point1) cnt1 = point2 + 1;
        if(cnt2 == point1) cnt2 = point2 + 1;
        if(ok1[par2[i]] == 0) {
            child1[cnt1] = par2[i];
            ok1[par2[i]]++;
            cnt1++;
        } else if(par2[i] == 0 && ok1[par2[i]] < K - 2) {
            child1[cnt1] = par2[i];
            ok1[par2[i]]++;
            cnt1++;
        }
        if(ok2[par1[i]] == 0) {
            child2[cnt2] = par1[i];
            ok2[par1[i]]++; 
            cnt2++;
        } else if(par1[i] == 0 && ok2[par1[i]] < K - 2) {
            child2[cnt2] = par1[i];
            ok2[par1[i]]++;
            cnt2++;   
        }
    }
    return {child1, child2};
}

//* ok
vector<population> crossover(vector<population> parents, double crossover_rate) {
    //!cerr << "Cross over step\n";
    vector<population> offspring, par = parents;
    vector<int> parent_index(parents.size());
    iota(parent_index.begin(), parent_index.end(), 0);

    while(true) {
        //!cerr << "Size of parent_index = " << parent_index.size() << '\n';
        if(parent_index.size() == 0) break;
        if(parent_index.size() == 1) {
            offspring.push_back(par[parent_index[0]]);
            break;
        }
        int par_index_0 = Rand(0, parent_index.size() - 1);
        int par_index_1 = Rand(0, parent_index.size() - 1);
        while(par_index_0 == par_index_1) {
            par_index_1 = Rand(0, parent_index.size() - 1);
        }
        //!cerr << par_index_0 << ' ' << par_index_1 << '\n';
        if(par_index_0 > par_index_1) swap(par_index_0, par_index_1);
        parent_index.erase(parent_index.begin() + par_index_1);
        parent_index.erase(parent_index.begin() + par_index_0);
        
        population par_0 = par[par_index_0], par_1 = par[par_index_1];
        //vector<int> child_0 = par_0, child_1 = par_1;

        double r = double(Rand(0, 100)) * 1.0 / 100.0;
        //!cerr << "rate = " << r << '\n';
        if(r < crossover_rate) {
           //! cerr << "Not crosver\n";
            // if we push the par again, their biggest_fitness_among_routes are still the same
            offspring.push_back(par_0);
            offspring.push_back(par_1);
        } else {
            //!cerr << "Crossover\n";
            // when we cross over, we need to calculate the biggest_fitness_among_routes of their children
            pair<vector<int>, vector<int>> children = making_children(par_0.route, par_1.route); 
            int t1 = return_biggest_fitness_each_config(children.first);
            int t2 = return_biggest_fitness_each_config(children.second);
            offspring.push_back({children.first, t1});
            offspring.push_back({children.second, t2});
        }
    }
    return offspring;
}

//! haven't used yet
vector<population> mutate(vector<population> chromesomes, double mutation_rate) {
    cerr << "Mutation step\n";
    vector<population> mutated_chromesomes;
    for(int i = 0; i < chromesomes.size(); i++) {
        double r = double(Rand(0, 100)) * 1.0 / 100.0;
        if(r <= mutation_rate) {
            // when their is a mutation occurs, we also need to calculate its biggeqst_fitness_among_routes again
            int random_index = Rand(1, chromesomes[i].route.size() - 2);
            int random_index_2 = Rand(1, chromesomes[i].route.size() - 2);
            while(random_index == random_index_2) {
                random_index_2 = Rand(1, chromesomes[i].route.size() - 2);
            }
            cerr << random_index << ' ' << random_index_2 << '\n';
            swap(chromesomes[i].route[random_index], chromesomes[i].route[random_index_2]);
           // chromesomes[i].biggest_fitness_among_routes = return_biggest_fitness_each_config(chromesomes[i].route);
        }
    }
    cerr << "End mutation step\n";
    return mutated_chromesomes;
}

//* looks ok
vector<population> next_generation(vector<population> pop, int tournament_size, double mutation_rate, double crossover_rate) {
    // cerr << "Next generation operation\n";
    vector<population> selected_parents;
    for(int n = 0; n < pop.size(); n++) {
        population selected_parent = tournament(pop, tournament_size);
        selected_parents.push_back(selected_parent);
    }
   //! cerr << '\n' << "Size of the selected parents in next_gen operation: " << selected_parents.size() << '\n';
    vector<population> next_gen;
    next_gen = crossover(selected_parents, crossover_rate);
    cerr << next_gen.size() << '\n';
    next_gen = mutate(next_gen, mutation_rate);
    return next_gen;
}

population evaluate(vector<population> pop) {
    population success;
    int biggest = INT_MAX;
    for(int i = 0; i < pop.size(); i++) {
        if(pop[i].biggest_fitness_among_routes < biggest) {
            success = pop[i];
            biggest = pop[i].biggest_fitness_among_routes;
        }
    }
    return success;
}
