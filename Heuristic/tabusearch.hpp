#include "GA.hpp"

// ! *********************************************************************** ! //

//! haven't create initial solution yet
bool cmp(vector<pii> a, vector<pii> b) {
    int suma = 0, sumb = 0;
    for(int i = 1; i < a.size(); i++) {
        if(a[i].first <= N && a[i].first >= 1) {
            if(a[i - 1].first <= N && a[i - 1].first >= 1)
                suma += d[a[i - 1].second][a[i].first];    
            else 
                suma += d[a[i - 1].first][a[i].first];
            suma += d[a[i].first][a[i].second];
        } else {
            suma += d[a[i - 1].first][a[i].first];
        }
    }
    for(int i = 1; i < b.size(); i++) {
    }
}

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