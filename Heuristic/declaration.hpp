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
#define taskname "almost"
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
    // uniform random configuration
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
