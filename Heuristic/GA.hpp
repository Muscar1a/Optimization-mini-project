#include<bits/stdc++.h>

using namespace std;

#define pii pair<int, int> 

class Genetic_Algorithm {
private:
int N, M, K;
public:
    vector<pii> generateValidState() {
        vector<pii> initGene;
        for(int i = 1; i <= M; i++) {
            initGene.push_back({i, i + N + M});
        }
        for(int i = 1; i <= N; i++) {
            initGene.push_back({i, i + N});
        }
        return initGene;
    }

    auto gene(int maxIter = 10, int population_size = 40, double crossover_rate = 0.6) {
        vector<pair<vector<pii>, int>> list_gene;
        while(list_gene.size() != population_size) {
            vector<pii> initGene = generateValidState();
        }
    }
    
};