//Mus
//#define _CRT_NONSTDC_NO_WaRNINGS
#include <bits/stdc++.h>
#include "tabu_seach.hpp"

using namespace std;
using namespace std::chrono;


// ! **************************REMINDER************************************* ! //

//* the index for car's capacity is in range (0, K - 1)
//* the index for weigh of parcels is in range(1, M)

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
}

/* outline
with each route, create a matrix distance for that route, then use the optimize algorithm
*/

void output_answer(vector<vector<pii>> ans) {
    cout << K << '\n';
    for(int i = 0; i < K; i++) {
        int cnt = 0;
        for(auto k:ans[i]) {
            if(k.first >= 1 && k.first <= N) cnt += 2;
            else cnt++;
        }
        cout << cnt << '\n';
        for(auto k:ans[i]) {
            if(k.first >= 1 && k.first <= N) cout << k.first << ' ' << k.second << ' ';
            else cout << k.first << ' ';
        }
        cout << " - " << cal_distance(ans[i]) << '\n';
    }
}

vector<vector<pii>> ans, final_ans;
vector<pii> single_ans;

void solving_tabu_seach() {
    cout << "Tabu-search\n";
    auto start = high_resolution_clock::now();
    vector<vector<pair<int, int>>> schedule;
    int mn = INT_MAX, mx = 0;
    for(int iterator = 0; iterator < 10; iterator++) {
        schedule.clear();
        if(iterator&1) schedule = random_configuration(K, N + M);
        else 
            schedule = uniform_random_configuration(K, N + M);
        ans.clear();
        bool is_valid = true;
        for(int id = 0; id < schedule.size(); id++) {
            if(check_valid_with_capacity(schedule[id], Q[id]) == false) {
                is_valid = false;
                break;
            }
            single_ans.clear();
            int num_cities = schedule[id].size();
            single_ans = tabu_search(schedule[id], Q[id]);
            ans.push_back(single_ans);
        }
        if(is_valid == false) continue;
        mx = 0;
        for(int id = 0; id < K; id++) {
            mx = max(mx, cal_distance(ans[id]));
        } 
        if(mn > mx) {
            mn = mx;
            final_ans = ans;
        }
    }
    output_answer(final_ans);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Running time = " << fixed << setprecision(5) << (double)duration.count() / 1000 << '\n';
}

void solving() {
    solving_tabu_seach();
}

void testing() {
    
}

int32_t main() {
    tachyon;
    if(ifstream(taskname".inp")) {
        freopen(taskname".inp", "r", stdin);
        freopen(taskname".out", "w", stdout);
    }
    srand(static_cast<unsigned>(std::time(0)));
    Enter();
    testing();
    solving();
    
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(stop - start);
    // cerr << fixed << setprecision(5) << (double)duration.count() / 1000 << '\n';
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