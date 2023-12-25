#include "declaration.hpp"
// ! *********************************************************************** ! //

/*
Optimuzing only one cycle route.
* The input format for tabu search is a vector<pair<int, int>>
*/

// ! *********************************************************************** ! //


// ! *********************************************************************** ! //
vector<pii> current_sol;
vector<pii> best_sol;
vector<vector<pii>> tabu_list;

bool check_valid(vector<pii> route) {
    // initDelivery is to check whether a passenger has been delivered or not
    for(int i = 1; i <= 2*N + 2*M; i++) initDeliver[i] = false;
    bool check = true;
    for(int i = 1; i < route.size() - 1; i++) {
        int nodea = route[i].first, nodeb = route[i].second;
        if(nodea <= N && nodea > 0) initDeliver[nodea] = true, initDeliver[nodeb] = true;
        else if(nodea > N && nodea <= N + M) {
            if(initDeliver[nodea + N + M] == true) check = false;;
            initDeliver[nodea] = true;
        } else if(nodea > N + M) {
            if(initDeliver[nodea - N - M] == false) check = false;
            initDeliver[nodea + N + M] = true;
        }
    }
    /*for(int i = 1; i < route.size() - 1; i++) {
        int nodea = route[i].first, nodeb = route[i].second;
        if(nodea > N && nodea <= N + M) {
            if(capacity >= q[nodea - N]) capacity -= q[nodea - N];
            else check = false;
        } else if(nodea > N + M) {
            capacity += q[nodea - N - M];
        }
    }*/
    return check;
}

//* guarantee true
bool check_valid_with_capacity(vector<pii> route, int capacity) {
    for(int i = 1; i <= 2*N + 2*M; i++) initDeliver[i] = false;
    bool check = true;
    for(int i = 1; i < route.size() - 1; i++) {
        int nodea = route[i].first, nodeb = route[i].second;
        if(nodea <= N && nodea > 0) initDeliver[nodea] = true, initDeliver[nodeb] = true;
        else if(nodea > N && nodea <= N + M) {
            if(initDeliver[nodea + N + M] == true) check = false;;
            initDeliver[nodea] = true;
        } else if(nodea > N + M) {
            if(initDeliver[nodea - N - M] == false) check = false;
            initDeliver[nodea + N + M] = true;
        }
    }
    for(int i = 1; i < route.size() - 1; i++) {
        int nodea = route[i].first, nodeb = route[i].second;
        if(nodea > N && nodea <= N + M) {
            if(capacity >= q[nodea - N]) capacity -= q[nodea - N];
            else check = false;
        } else if(nodea > N + M) {
            capacity += q[nodea - 2*N - M];
        }
    }

    return check;
}

vector<vector<pii>> get_neighbor(vector<pii> current_sol) {
    // cerr << "Getting neighbour\n";
    vector<vector<pii>> neighborhood;
    for(int i = 1; i < current_sol.size() - 2; i++) {
        for(int j = i + 1; j < current_sol.size() - 1; j++) {
            vector<pii> neighbor = current_sol;
            swap(neighbor[i], neighbor[j]);
            neighborhood.push_back(neighbor);
        }
    }
    // cerr << "neighborhood size = " << neighborhood.size() << '\n';
    return neighborhood;
}


vector<pii> tabu_search(vector<pii> given, int capacity) {
    current_sol.clear(), current_sol = given;
    best_sol.clear(), best_sol = current_sol;
    tabu_list.clear();
    
    if(given.size() == 3) return given;
    if(given.size() == 4) {
        if(given[1].first > N && given[1].first <= N + M) return given;
    }
    for(int iteration = 0; iteration < 1000; iteration++) {
        vector<vector<pii>> neighbor = get_neighbor(current_sol);
        sort(neighbor.begin(), neighbor.end(), [&](vector<pii> a, vector<pii> b) {
            return cal_distance(a) < cal_distance(b);
        });
        bool found = false;
        for(int neighbor_id = 0; neighbor_id < neighbor.size(); neighbor_id++) {
            current_sol = neighbor[neighbor_id];
            if(find(tabu_list.begin(), tabu_list.end(), current_sol) == tabu_list.end()) {
                bool check = check_valid(current_sol);

                if(check_valid(current_sol)) {
                    current_sol = neighbor[neighbor_id];
                    tabu_list.push_back(current_sol);
                    found = true;
                    break;
                }
            }
        }
        if(!found) {
            current_sol = neighbor[0];
        }
        if(!tabu_list.empty()) tabu_list.erase(tabu_list.begin());
        if(cal_distance(current_sol) < cal_distance(best_sol) && check_valid_with_capacity(current_sol, capacity))
            best_sol = current_sol;
    }
    return best_sol;
}
