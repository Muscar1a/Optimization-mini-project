#include<bits/stdc++.h>
#include "declaration.hpp"
using namespace std;

#define pii pair<int, int> 

// the random configuration is a vector of vector of pair<int, int>
bool find(vector<pii> a, pii b) {
    for(auto i:a) {
        if(i.first == b.first && i.second == b.second) return true;
    }
    return false;
}

int current_cap(vector<pii> state) {
    int cap = 0;
    for(auto i:state) {
        if(i.first > N && i.first <= N + M) cap -= q[i.first - N];
        else if(i.first > N + M) cap += q[i.first - 2*N - M];
    }
}
vector<pii> Children(vector<pii> listNode, vector<pii> state, int capacity) {
    int curCap = current_cap(state);
    vector<pii> child;
    for(auto i:listNode) {
       
    }
}

vector<pii> generateValidState(vector<pii> initConfig, int capacity) {
    vector<pii> listNode = initConfig;
    vector<pii> state = {{0, -1}};
    int curCap = 0;
    while(1) {
        return {{-1, -1}};
    }
}

auto gene(vector<pii> initConfig, int capacity, int maxIter = 10, int population_size = 40, double crossover_rate = 0.6) {
    vector<pair<vector<pii>, int>> list_gene;
    while(list_gene.size() != population_size) {
        vector<pii> initGene = generateValidState(initConfig, capacity);
        list_gene.push_back({initGene, cal_distance(initGene)});
        for(auto i:initGene) {
            if(i.first >= 1 && i.first <= N) cout << i.first << ' ' << i.second << ' ';
            else cout << i.first << ' ';
        }
        cout << '\n';
        return;
    }
}
