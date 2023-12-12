#include "declaration.hpp"

// ! *********************************************************************** ! //

vector<int> newRoute;

int cal_distance(vector<int> route) {
    int s = 0;
    for(int i = 1; i < route.size(); i++) {
        s += d[route[i - 1]][route[i]];
    }
    return s;
}

/*vector<int> opt_swap(vector<int> route, int i, int j) {
    vector<int> nRoute(route.begin(), route.begin() + i);
    for(int k = j; k >= i + 1; k--) nRoute.push_back(route[i]);
    for(int k = j + 1; k < route.size(); k++) nRoute.push_back(route[i]);
    bool ok = false;
    for(int k = 0; k < route.size(); k++) {
        cerr << route[k] << ' ';
    }
    cerr << '\n';
    return nRoute;
}*/

pair<vector<int>, bool> opt_swap(vector<int> path, int i, int j) {
    vector<int> route = path;
	reverse(begin(route) + i + 1, begin(route) + j + 1);
    bool ok = false;
    for(int i = 1; i < route.size() - 1; i++) {
        if(route[i] >= 1 && route[i] <= N && route[i + 1] == route[i] + N + M) ok = true;
        else ok = false;
    }
    return {route, ok};
}

void two_opt_operation() {
    cout << "I am running in opt\n";
    vector<int> original_config;
    for(int k = 0; k < K; k++) {
        // 2-opt in each route
        original_config.clear();
        k = 1;
        original_config = initRoutes[k];
        bool improvement = true;
        while(improvement) {
            cerr << improvement << '\n';
            improvement = false;
            for(int i = 1; i < initRoutes[k].size() - 2; i++) {
                for(int j = i + 1; j < initRoutes[k].size() - 1; j++) {
                    pair<vector<int>, bool> tmp = opt_swap(initRoutes[k], i, j);
                    newRoute = tmp.first;
                    bool ok = tmp.second;
                    int new_dist = cal_distance(newRoute);
                    
                    if(new_dist < sumRoutes[k]) {
                        if(ok) {
                            sumRoutes[k] = new_dist;
                            initRoutes[k] = newRoute;
                            // TODO: check for the 2opt
                            for(auto i:newRoute) cerr << i << ' ';
                            cerr << ": " << new_dist << '\n';
                        }
                        improvement = true;
                    }
                }
            }
            if(initRoutes[k] == original_config) break;
        }
        return;
    }
}

void printAfter2Opt() {
    cout << "After 2-opt operation\n";
    for(int k = 0; k < K; k++) {
        cout << "Route " << k << ":\n";
        for(auto i:initRoutes[k]) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    cout << "Sum after 2-opt\n";
    for(int k = 0; k < K; k++) {
        cout << "Routes " << k << " = " << sumRoutes[k] << "\n";
    }
}