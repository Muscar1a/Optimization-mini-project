#include "declaration.hpp"

// ! *********************************************************************** ! //

/*
Optimuzing only one cycle route.
* The input format for tabu search is a vector<pair<int, int>>
*/

// ! *********************************************************************** ! //

vector<pii> current_sol;
vector<pii> best_sol;
vector<vector<pii>> tabu_list;

// ! *********************************************************************** ! //

bool check_valid(vector<pii> route) {
    // initDelivery is to check whether a passenger has been delivered or not
    for(int i = 1; i <= 2*N + 2*M; i++) initDeliver[i] = false;
    for(int i = 1; i < route.size() - 1; i++) {
        int nodea = route[i].first, nodeb = route[i].second;
        if(nodea <= N && nodea > 0) initDeliver[nodea] = true, initDeliver[nodeb] = true;
        else if(nodea > N && nodea <= N + M) {
            if(initDeliver[nodea + N + M] == true) return false;
            initDeliver[nodea] = true;
        } else if(nodea > N + M) {
            if(initDeliver[nodea - N - M] == false) return false;
            initDeliver[nodea + N + M] = true;
        }
    }
    return true;
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


vector<pii> tabu_search(vector<pii> given) {
    current_sol.clear(), current_sol = given;
    best_sol.clear(), best_sol = current_sol;
    tabu_list.clear();
    
    if(given.size() == 3) return given;
    if(given.size() == 4) {
        if(given[1].first > N && given[1].first <= N + M) return given;
    }
    for(int iteration = 0; iteration < 1000; iteration++) {
        vector<vector<pii>> neighbor = get_neighbor(current_sol);
        // cerr << "Computing\n";
        
        sort(neighbor.begin(), neighbor.end(), [&](vector<pii> a, vector<pii> b) {
            return cal_distance(a) < cal_distance(b);
        });
        // cerr << "After sort\n";
        /*
        cerr << '\n';
        for(auto nei:neighbor) {
            for(auto i:nei) {
                int nodea = i.first, nodeb = i.second;
                if(nodea >= 1 && nodea <= N) cerr << nodea << ' ' << nodeb << ' ';
                else cerr << nodea << ' ';
            }
            cerr << '\n';
        }
        */
        // cerr << "neighbor size = " << neighbor.size() << '\n';
        bool found = false;
        for(int neighbor_id = 0; neighbor_id < neighbor.size(); neighbor_id++) {
            // cerr << "neighbor_id = " << neighbor_id << '\n';
            current_sol = neighbor[neighbor_id];
            if(find(tabu_list.begin(), tabu_list.end(), current_sol) == tabu_list.end()) {
                // cerr << "Jump in?\n";
                /*cerr << "neighbor_id = " << neighbor_id << ": ";
                for(auto i:current_sol) {
                    cerr << "{" << i.first << ", " << i.second << "}, ";
                }*/
                //cerr << cal_distance(current_sol) << '\n';
                bool check = check_valid(current_sol);
                // cerr << "Checking valid of this configuration " << check << '\n';

                if(check_valid(current_sol)) {
                    // cerr << "found\n";
                    current_sol = neighbor[neighbor_id];
                    tabu_list.push_back(current_sol);
                    found = true;
                    break;
                }
            }
        }
        // cerr << "Reach this one time\n";
        /*for(auto i:current_sol) {
            cerr << "{" << i.first << ", " << i.second << "}, ";
        }*/
        // cerr << found << '\n';
        if(!found) {
            // cerr << "Hello\n" << neighbor.size() << '\n';
            current_sol = neighbor[0];
            // cerr << "Bye\n";
        }
        // REACH;
        // cerr << "tabu_list size = " << tabu_list.size() << '\n';
        if(!tabu_list.empty()) tabu_list.erase(tabu_list.begin());
        if(cal_distance(current_sol) < cal_distance(best_sol) && check_valid(current_sol))
            best_sol = current_sol;
    }
    return best_sol;
}

int tabu_search_return_fitness(vector<pii> given) {
    current_sol.clear(), current_sol = given;
    best_sol.clear(), best_sol = current_sol;
    tabu_list.clear();
    
    if(given.size() == 3) return cal_distance(given);
    if(given.size() == 4) {
        if(given[1].first > N && given[1].first <= N + M) return cal_distance(given);
    }
    for(int iteration = 0; iteration < 1000; iteration++) {
        vector<vector<pii>> neighbor = get_neighbor(current_sol);
        // cerr << "Computing\n";
        
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
        if(cal_distance(current_sol) < cal_distance(best_sol) && check_valid(current_sol))
            best_sol = current_sol;
    }
    return cal_distance(best_sol);
}
