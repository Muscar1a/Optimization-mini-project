#include "GA.hpp"

// ! *********************************************************************** ! //

vector<vector<pii>> get_neighbor(vector<pii> current_sol) {
    vector<vector<pii>> neighborhood;
    for(int i = 0; i < current_sol.size(); i++) {
        for(int j = i + 1; j < current_sol.size(); i++) {
            vector<pii> neighbor = current_sol;
            swap(neighbor[i], neighbor[j]);
            neighborhood.push_back(neighbor);
        }
    }
    return neighborhood;
}
void tabu_search() {
    vector<pii> current_sol;
    vector<pii> best_sol, tabu_list;
    
    for(int iteration = 0; iteration < 1000; iteration++) {
        vector<vector<pii>> neighbor = get_neighbor(current_sol);
    }
}