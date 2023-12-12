#include "declaration.hpp"

// ! *********************************************************************** ! //

vector<int> newRoute;
bool checking[5005];

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

vector<int> opt_swap(vector<int> path, int i, int j) {
    vector<int> route = path;
	reverse(begin(route) + i + 1, begin(route) + j + 1);
    bool ok = false;
    return route;
}

bool check_valid(vector<int> route) {
    memset(checking, false, sizeof(checking));
    bool final_check = true;
    for(int i = 1; i < route.size() - 1; i++) {
        if(route[i] <= N + M) checking[route[i]] = true;
        else { 
            if(checking[route[i] - N - M] == true && (route[i] - N - M) <= N && (route[i] - N - M) == route[i - 1]) checking[route[i]] = true;
            else if(checking[route[i] - N - M] == true && (route[i] - N - M) > N && (route[i] - N - M) <= (N + M)) checking[route[i]] = true;
        }        
    }
    for(int i = 1; i < route.size() - 1; i++)
        if(checking[route[i]] == false) {
            final_check = false;
            break;
        }
    return final_check;
}

vector<vector<int>> consider;

vector<int> two_opt_for_each(vector<int> &given_route, int k) {
    vector<int> route = given_route, original_route = route;
    int cur_sum = sumRoutes[k], cur_min_sum = sumRoutes[k]; 
    bool improving = true;
    consider.clear();
    while(improving) {
        consider.clear();
        consider.push_back(route);
        improving = false;
        for(int i = 0; i < route.size() - 2; i++) {
            for(int j = i + 1; j < route.size() - 1; j++) {
                newRoute = opt_swap(route, i, j);
                int new_dist = cal_distance(newRoute);
                
                if(new_dist < cur_sum) {
                    cur_sum = new_dist;
                    route = newRoute;
                    consider.push_back(newRoute);
                    improving = true;
                }
            }
        }
        for(auto c:consider) {
            //for(auto i:c) cerr << i << ' ';
            //cerr << '\n';
            bool ok = check_valid(c);
            if(!ok) continue;
            int sum = cal_distance(c);
            if(sum < cur_min_sum) {
                cur_min_sum = sum;
                original_route = c;
            }
        }
        // ? some problem occur leads to infinite loop, eventhough it reaches stop point?
    }
    return original_route;
}

void two_opt_operation() {
    vector<int> original_config;
    for(int k = 0; k < K; k++) {
        // 2-opt in each route
        k = 0;
        vector<int> temp = two_opt_for_each(initRoutes[k], k);
        cout << temp.size() << '\n';
        for(auto i:temp) cout << i << ' ';
        cout << '\n';
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