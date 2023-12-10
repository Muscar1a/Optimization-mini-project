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

vector<int> opt_swap(vector<int> route, int i, int j) {
    vector<int> nRoute(route.begin(), route.begin() + i);
    for(int k = j; k >= i + 1; k--) nRoute.push_back(route[i]);
    for(int k = j + 1; k < route.size(); k++) nRoute.push_back(route[i]);
    return nRoute;
}

void two_opt_operation() {
    for(int k = 0; k < K; k++) {
        // 2-opt in each route
        for(int i = 1; i < initRoutes[k].size() - 2; i++) {
            for(int j = i + 1; j < initRoutes[k].size() - 1; j++) {
                newRoute = opt_swap(initRoutes[k], i, j);
                int new_dist = cal_distance(initRoutes[k]);
                
                if(new_dist < sumRoutes[k]) {
                    sumRoutes[k] = new_dist;
                    initRoutes[k] = newRoute;
                }
            }
        }
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