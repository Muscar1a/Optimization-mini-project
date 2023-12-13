#include "declaration.hpp"

// ! *********************************************************************** ! //

int delivery[1005];


void createInitSol() {
    cerr << routes[0][0] << '\n';
    for(int k = 0; k < K; k++) {
        for(int i = 1; i <= N + M; i++) delivery[i] = 0; // reset the delivery checking
        sort(initRoutes[k].begin(), initRoutes[k].end());
        for(int i = 0; i < initRoutes[k].size(); i++) {
            int node = initRoutes[k][i];
            if(node == 0) continue;
            else {
                /*
                    because i am creating an initial configuration, whenever i reach 
                    a parcel or passenger, i'll deliver them straight to their point, so
                    we can temparory ignore the cars' capacity
                */
                routes[k].push_back(node);
                routes[k].push_back(node + N + M);
            }
        }
        routes[k].push_back(0);
        cerr << k << '\n';
        for(auto i:routes[k]) cerr << i << " ";
        cerr << '\n';
    }
}