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

// ! *************************DECLARATION********************************** ! //

struct savings {
    int saving, i, j;
};
int K, N, M;
int d[1005][1005], initDeliver[2005], sumRoutes[2005];
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

auto random_configuration(int num_vehicles, int num_passengers_parcels) {
    vector<int> config(num_passengers_parcels);
    vector<pair<int, int>> temp;
    vector<vector<pair<int, int>>> split_config;
    random_device rd;
    mt19937 g(rd());
    iota(config.begin(), config.end(), 1);
    shuffle(config.begin(), config.end(), g);

    int cnt = 0;
    for(int i = 0; i < config.size(); i++) {
        ++cnt;
        if(config[i] >= 1 && config[i] <= N) temp.push_back({config[i], config[i] + N + M});
        else temp.push_back({config[i], -1});
        if(cnt == (num_passengers_parcels / num_vehicles)) {
            split_config.push_back(temp);
            temp.clear();
            cnt = 0;
        }
    }
    for(int i = 0; i < num_vehicles; i++) {
        temp = split_config[i];
        for(auto j:temp) {
            if(j.first > N) temp.push_back({j.first + N + M, -1});
        }
        sort(temp.begin(), temp.end());
        split_config[i] = temp;
        temp.clear();
    }
    return split_config;
}

vector<vector<int>> distance_matrix_for_each_vehicles(vector<pair<int, int>> passenger_list) {
    vector<int> temp;
    for(auto i:passenger_list) {
        temp.push_back(i.first);
        if(i.second != -1) temp.push_back(i.second);
    }
    sort(temp.begin(), temp.end());
    int pass_size = temp.size();
    vector<vector<int>> result_matrix(pass_size, vector<int>(pass_size));
    for (size_t i = 0; i < pass_size; ++i) {
        for (size_t j = 0; j < pass_size; ++j) {
            result_matrix[i][j] = d[temp[i]][temp[j]];       
        }
    }
    return result_matrix;
}

// ! **************************REMINDER************************************* ! //

//* the index for car's capacity is in range (0, K - 1)
//* the index for weigh of parcels is in range(1, M)
//* passengers to their delivery point <=> i + N + M
//* parcels to their delivery point <=> i + N + M

// ! *********************************************************************** ! //
