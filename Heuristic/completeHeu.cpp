//Mus
//#define _CRT_NONSTDC_NO_WaRNINGS
#include <bits/stdc++.h>
using namespace std;

//#define int long long
typedef long long ll;
typedef long double ld;
#define tachyon         ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0)
#define reset(x, num)   memset(x, num, sizeof(x))
#define all(x)          (x.begin(), x.end())
#define MOD (ll)(1e9 + 7)
const int maxn = 1e5 + 10, inf = 0x3f3f3f3f;
#define taskname "complete"
#define pii pair<int, int>
unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
random_device rd; 
mt19937 g(seed);
// ! *************************DECLARATION********************************** ! //

struct savings {
    int saving, i, j;
};
int K, N, M;
int d[2005][2005], initDeliver[2005], sumRoutes[2005];
int q[205], Q[205], remCap[205];
map<pair<int, int>, int> s_value; // saving_value
vector<pair<int, int>> needtotake;
vector<savings> save;
vector<int> initRoutes[105], routes[105];
vector<int> considering;

// ! *********************************************************************** ! //

int Rand(int L, int R) {
    return L + rand() % (R - L + 1);
}

auto uniform_random_configuration(int num_vehicles, int num_pass_par) {
    // uniform random configurations
    vector<int> config(num_pass_par);
    iota(config.begin(), config.end(), 1);
    shuffle(config.begin(), config.end(), g);
    vector<vector<pair<int, int>>> configuration;
    int num_per_car = num_pass_par / num_vehicles;
    for(int i = 0; i < num_vehicles; i++) {
        auto start = config.begin() + i * num_per_car;
        auto end = (i == num_vehicles - 1) ? config.end() : start + num_per_car;
        vector<pair<int, int>> single_config;
        for(auto it = start; it != end; it++) {
            if(*it >= 1 && *it <= N)
                single_config.push_back({*it, *it + N + M});
            else 
                single_config.push_back({*it, -1});
        }
        configuration.push_back(single_config);
    }
    for(int i = 0; i < num_vehicles; i++) {
        vector<pair<int, int>> single_config = configuration[i];
        for(auto k:configuration[i]) {
            if(k.first > N)
                single_config.push_back({k.first + N + M, -1});
        }
        //sort(single_config.begin(), single_config.end());
        single_config.insert(single_config.begin(), {0, -1});
        single_config.push_back({0, -1});
        configuration[i] = single_config;
    }
    return configuration;
}

auto random_configuration(int num_vehicles, int num_pass_par) {
    vector<vector<pair<int, int>>> configuration(num_vehicles);
    for(int p = 1; p <= num_pass_par; p++) {
        int index = Rand(0, num_vehicles - 1);
        if(p >= 1 && p <= N) {
            configuration[index].push_back({p, p + N + M});
        } else {
            configuration[index].push_back({p, - 1});
            configuration[index].push_back({p + N + M, -1});
        }
    }
    for(int i = 0; i < num_vehicles; i++) {
        vector<pair<int, int>> single_config = configuration[i];
        //sort(single_config.begin(), single_config.end());
        single_config.insert(single_config.begin(), {0, -1});
        single_config.push_back({0, -1});
        configuration[i] = single_config;
    }
    return configuration;
}
int cal_distance(vector<pii> route) {
    int sum = 0;
    for(int i = 1; i < route.size(); i++) {
        if(route[i].first <= N && route[i].first > 0) {
            if(route[i - 1].first <= N && route[i - 1].first > 0) {
                sum += d[route[i - 1].second][route[i].first];
                sum += d[route[i].first][route[i].second];
            } else {
                sum += d[route[i - 1].first][route[i].first];
                sum += d[route[i].first][route[i].second];
            }
        } else {
            if(route[i - 1].first <= N && route[i - 1].first > 0) {
                sum += d[route[i - 1].second][route[i].first];
            }
            else {
                sum += d[route[i - 1].first][route[i].first];
            }
        }
    }
    return sum;
}

// ! **************************REMINDER************************************* ! //

//* the index for car's capacity is in range (0, K - 1)
//* the index for weigh of parcels is in range(1, M)
//* passengers to their delivery point <=> i + N + M
//* parcels to their delivery point <=> i + N + M

// ! *********************************************************************** ! //



// ! *********************************************************************** ! //
vector<pii> current_sol;
vector<pii> best_sol;
vector<vector<pii>> tabu_list;

bool check_valid(vector<pii> route) {
    // initDelivery is to check whether a passenger has been delivered or not
    for(int i = 1; i <= 2*N + 2*M; i++) initDeliver[i] = false;
    bool check = true;
    for(int i = 1; i < route.size() - 1; i++) {
        int nodea = route[i].first, nodeb = route[i].second;
        if(nodea <= N && nodea > 0) initDeliver[nodea] = true, initDeliver[nodeb] = true;
        else if(nodea > N && nodea <= N + M) {
            if(initDeliver[nodea + N + M] == true) check = false;;
            initDeliver[nodea] = true;
        } else if(nodea > N + M) {
            if(initDeliver[nodea - N - M] == false) check = false;
            initDeliver[nodea + N + M] = true;
        }
    }
    /*for(int i = 1; i < route.size() - 1; i++) {
        int nodea = route[i].first, nodeb = route[i].second;
        if(nodea > N && nodea <= N + M) {
            if(capacity >= q[nodea - N]) capacity -= q[nodea - N];
            else check = false;
        } else if(nodea > N + M) {
            capacity += q[nodea - N - M];
        }
    }*/
    return check;
}

//* guarantee true
bool check_valid_with_capacity(vector<pii> route, int capacity) {
    for(int i = 1; i <= 2*N + 2*M; i++) initDeliver[i] = false;
    bool check = true;
    for(int i = 1; i < route.size() - 1; i++) {
        int nodea = route[i].first, nodeb = route[i].second;
        if(nodea <= N && nodea > 0) initDeliver[nodea] = true, initDeliver[nodeb] = true;
        else if(nodea > N && nodea <= N + M) {
            if(initDeliver[nodea + N + M] == true) check = false;;
            initDeliver[nodea] = true;
        } else if(nodea > N + M) {
            if(initDeliver[nodea - N - M] == false) check = false;
            initDeliver[nodea + N + M] = true;
        }
    }
    for(int i = 1; i < route.size() - 1; i++) {
        int nodea = route[i].first, nodeb = route[i].second;
        if(nodea > N && nodea <= N + M) {
            if(capacity >= q[nodea - N]) capacity -= q[nodea - N];
            else check = false;
        } else if(nodea > N + M) {
            capacity += q[nodea - 2*N - M];
        }
    }

    return check;
}

vector<vector<pii>> get_neighbor(vector<pii> current_sol) {
    // cerr << "Getting neighbour\n";
    vector<vector<pii>> neighborhood;
    for(int i = 1; i < current_sol.size() - 2; i++) {
        for(int j = i + 1; j < current_sol.size() - 1; j++) {
            vector<pii> neighbor = current_sol;
            swap(neighbor[i], neighbor[j]);
            neighborhood.push_back(neighbor);
        }
    }
    // cerr << "neighborhood size = " << neighborhood.size() << '\n';
    return neighborhood;
}


vector<pii> tabu_search(vector<pii> given, int capacity) {
    current_sol.clear(), current_sol = given;
    best_sol.clear(), best_sol = current_sol;
    tabu_list.clear();
    
    if(given.size() == 3) return given;
    if(given.size() == 4) {
        if(given[1].first > N && given[1].first <= N + M) return given;
    }
    for(int iteration = 0; iteration < 1000; iteration++) {
        vector<vector<pii>> neighbor = get_neighbor(current_sol);
        sort(neighbor.begin(), neighbor.end(), [&](vector<pii> a, vector<pii> b) {
            return cal_distance(a) < cal_distance(b);
        });
        bool found = false;
        for(int neighbor_id = 0; neighbor_id < neighbor.size(); neighbor_id++) {
            current_sol = neighbor[neighbor_id];
            if(find(tabu_list.begin(), tabu_list.end(), current_sol) == tabu_list.end()) {
                bool check = check_valid(current_sol);

                if(check_valid(current_sol)) {
                    current_sol = neighbor[neighbor_id];
                    tabu_list.push_back(current_sol);
                    found = true;
                    break;
                }
            }
        }
        if(!found) {
            current_sol = neighbor[0];
        }
        if(!tabu_list.empty()) tabu_list.erase(tabu_list.begin());
        if(cal_distance(current_sol) < cal_distance(best_sol) && check_valid_with_capacity(current_sol, capacity))
            best_sol = current_sol;
    }
    return best_sol;
}


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