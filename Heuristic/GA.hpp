#include<bits/stdc++.h>
#include "declaration.hpp"
using namespace std;

#define pii pair<int, int> 

vector<int> children(vector<int> listNode, vector<pii> state) {

}
vector<pii> generateValidState() {
    vector<pii> state = {{0, -1}};
    vector<int> listNode(N + M);
    iota(listNode.begin(), listNode.end(), 1);
    int cap = 0;
    while(1) {
        vector<int> listNext = children(listNode, state);
        int nextCity; bool ok = false;
        while(1) {
           nextCity = listNext[rand() % listNext.size()];
            if(nextCity != 0) {
                if(nextCity > N && nextCity <= N + M) {
                    
                }
            }
        }
        state.push_back({nextCity, -1});
    }
    state.push_back({0, -1});
    return state;
}

auto gene(int maxIter = 10, int population_size = 40, double crossover_rate = 0.6) {
    vector<pair<vector<pii>, int>> list_gene;
    while(list_gene.size() != population_size) {
        vector<pii> initGene = generateValidState();
    }
}
