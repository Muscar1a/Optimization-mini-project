//Mus
//#define _CRT_NONSTDC_NO_WaRNINGS
#include <bits/stdc++.h>
#include "GA.hpp"
using namespace std;
using namespace std::chrono;


// ! **************************REMINDER************************************* ! //

//* the index for car's capacity is in range (0, K - 1)
//* the index for weigh of parcels is in rannge(1, M)

// ! *********************************************************************** ! //

void Enter() {
    cin >> N >> M >> K;
    for(int i = 1; i <= M; i++) cin >> q[i];
    for(int i = 0; i < K; i++) {
        cin >> Q[i];
        remCap[i] = Q[i];
    }
    for(int i = 0; i <= 2*N + 2*M; i++) {
        for(int j = 0; j <= 2*N + 2*M; j++) cin >> d[i][j];
    }
    for(int i = 0; i < K; i++) {
        routes[i].push_back(0);
    }
}

void testing() {
    //createPopulation();
    pair<vector<int>, vector<int>> child_making = making_children({0, 2, 6, 3, 0, 5, 4, 1, 0}, {0, 1, 0, 6, 5, 2, 3, 4, 0});
    vector<int> child1, child2;
    child1 = child_making.first;
    child2 = child_making.second;
    for(auto i:child1) cout << i << ' ';
    cout << '\n';
    for(auto i:child2) cout << i << ' ';
    /*
    vector<population> new_pop = next_generation(pop, tournament_size, mutation_rate, crossover_rate);
    int cnt = 0;
    for(auto p:new_pop) {
        cout << ++cnt << " - " << p.biggest_fitness_among_routes << ":\n";
        for(auto i:p.route) cout << i << ' ';
        cout << '\n';
    }
    */
}

void solve() {
    createPopulation();
   // population parameter = pop
    for(int generation = 0; generation < 5; generation++) {
        pop = next_generation(pop, tournament_size, mutation_rate, crossover_rate);
        ans = evaluate(pop);
    //    cerr << "Generation = " << generation << '\n';
    }
    vector<vector<pii>> final_ans = create_full_route(ans.route);
    
    cout << K << "\n";
    for(int i = 0; i < K; i++) {
        vector<pii> temp = tabu_search(final_ans[i]);
        vector<int> meo;
        for(int i = 0; i < temp.size(); i++) {
            if(temp[i].first >= 1 && temp[i].first <= N) {
                meo.push_back(temp[i].first);
                meo.push_back(temp[i].second);
            } else meo.push_back(temp[i].first);
        }
        cout << meo.size() << '\n';
        for(auto x:meo) cout << x << ' ';
        cout << '\n';
    }
}

// TODO: write the main function and mutate
int32_t main() {
    
    tachyon;
    if(ifstream(taskname".inp")) {
        freopen(taskname".inp", "r", stdin);
        freopen(taskname".out", "w", stdout);
    }
    srand(static_cast<unsigned>(std::time(0)));
    auto start = high_resolution_clock::now();
    Enter();
    init();
    // testing();
    solve();
    
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(stop - start);
    //! cerr << fixed << setprecision(5) << (double)duration.count() / 1000 << '\n';
	return 0;
}

/*
INPUT SAMPLE
3 3 2
8 4 5 
16 16 
0 8 7 9 6 5 11 6 11 12 12 12 13 
8 0 4 1 2 8 5 13 19 12 4 8 9 
7 4 0 3 3 8 4 12 15 8 5 6 7 
9 1 3 0 3 9 4 14 19 11 3 7 8 
6 2 3 3 0 6 6 11 17 11 6 9 10 
5 8 8 9 6 0 12 5 16 15 12 15 15 
11 5 4 4 6 12 0 16 18 7 4 3 4 
6 13 12 14 11 5 16 0 15 18 17 18 19 
11 19 15 19 17 16 18 15 0 13 21 17 17 
12 12 8 11 11 15 7 18 13 0 11 5 4 
12 4 5 3 6 12 4 17 21 11 0 7 8 
12 8 6 7 9 15 3 18 17 5 7 0 1 
13 9 7 8 10 15 4 19 17 4 8 1 0


*/