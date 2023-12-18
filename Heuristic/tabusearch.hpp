#include "declaration.hpp"

// ! *********************************************************************** ! //

int cal_distance(vector<pii> route) {
    int sum = 0;
    for(int i = 1; i < route.size(); i++) {
        if(route[i].first <= N && route[i].first > 0) {
            if(route[i - 1].first <= N && route[i].first > 0) {
                sum += d[route[i - 1].second][route[i].first];
                sum += d[route[i].first][route[i].second];
            } else {
                sum += d[route[i - 1].first][route[i].first];
                sum += d[route[i].first][route[i].second];
            }
        } else {
            if(route[i - 1].first <= N && route[i - 1].first > 0) 
                sum += d[route[i - 1].second][route[i].first];
            else sum += d[route[i - 1].first][route[i].first];
        }
    }
    return sum;
}

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
    vector<vector<pii>> neighborhood;
    for(int i = 1; i < current_sol.size() - 2; i++) {
        for(int j = i + 1; j < current_sol.size() - 1; j++) {
            vector<pii> neighbor = current_sol;
            swap(neighbor[i], neighbor[j]);
            neighborhood.push_back(neighbor);
        }
    }
    return neighborhood;
}


vector<pii> tabu_search(vector<pii> given) {
    vector<pii> current_sol = given;
    vector<pii> best_sol = current_sol;
    vector<vector<pii>> tabu_list;

    
    for(int iteration = 0; iteration < 1000; iteration++) {
        vector<vector<pii>> neighbor = get_neighbor(current_sol);
        
        
        sort(neighbor.begin(), neighbor.end(), [&](vector<pii> a, vector<pii> b) {
            return cal_distance(a) < cal_distance(b);
        });
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
        //cerr << "neighbor size = " << neighbor.size() << '\n';
        bool found = false;
        for(int neighbor_id = 0; neighbor_id < neighbor.size(); neighbor_id++) {
            current_sol = neighbor[neighbor_id];
            if(find(tabu_list.begin(), tabu_list.end(), current_sol) == tabu_list.end()) {
                /*cerr << "neighbor_id = " << neighbor_id << ": ";
                for(auto i:current_sol) {
                    cerr << "{" << i.first << ", " << i.second << "}, ";
                }*/
                //cerr << cal_distance(current_sol) << '\n';
                bool check = check_valid(current_sol);
                //cerr << "Checking valid of this configuration " << check << '\n';

                if(check_valid(current_sol)) {
                    //cerr << "found\n";
                    current_sol = neighbor[neighbor_id];
                    tabu_list.push_back(current_sol);
                    found = true;
                    break;
                }
            }
        }
        /*cerr << "Reach this one time\n";
        for(auto i:current_sol) {
            cerr << "{" << i.first << ", " << i.second << "}, ";
        }*/
        if(!found)
            current_sol = neighbor[0];
        //REACH;
        //cerr << "tabu_list size = " << tabu_list.size() << '\n';
        tabu_list.erase(tabu_list.begin());
        if(cal_distance(current_sol) < cal_distance(best_sol) && check_valid(current_sol))
            best_sol = current_sol;
    }
    return best_sol;
}