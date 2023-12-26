#include<bits/stdc++.h>
#include "declaration.hpp"

//! ****************************************************************** !//

vector<pii> generateValidState() {
    vector<pii> state = {{0, -1}};
    vector<int> list_node(2*N + 2*M + 1);
    
}

pair<int, vector<pii>> hill_climbing() {
    vector<pii> initState = generateValidState();
}

auto solvingHeuristic() {
    int sub_opt_cost = INT_MAX;
    vector<int> sub_opt_config;
    while(sub_opt_cost >= INT_MAX) {
        for(int play = 0; play <= 2; play++) {
            pair<int, vector<pii>> res = hill_climbing();
            
        }
    }
}