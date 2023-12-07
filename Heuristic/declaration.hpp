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
int d[1005][1005], initDeliver[2005];
int q[205], Q[205], remCap[205];
map<pair<int, int>, int> s_value; // saving_value
vector<pair<int, int>> needtotake;
vector<savings> save;
vector<int> initRoutes[105], routes[105];
vector<int> considering;

// ! *********************************************************************** ! //

bool cmp(savings a, savings b) {
    return a.saving > b.saving;
}

int Rand(int L, int R) {
    return L + rand() % (R - L + 1);
}

void init() {
    for(int i = 1; i <= N + M; i++) {
        needtotake.push_back({d[0][i], i});
        initDeliver[i] = false;
    }
    sort(needtotake.begin(), needtotake.end());
    for(int i = 1; i <= 2*N + 2*M; i++) {
        for(int j = i + 1; j <= 2*N + 2*M; j++) {
            int temp = d[0][i] + d[0][j] - d[i][j];
            save.push_back({temp, i, j});
            s_value[{i, j}] = s_value[{j, i}] = temp;
        }
    }
    sort(save.begin(), save.end(), cmp);

    for(int i = 0; i < K; i++) initRoutes[i].push_back(0);
}

pair<pair<int, int>, int> try_to_return_thing(int from, int to, int k, int* currentCapacity) {
    considering.clear();
    int* Cap = currentCapacity;
    for(auto p:initRoutes[k]) {
        if(p > N && p <= N + M && !initDeliver[p]) considering.push_back(p);
    }
    int mn = INT_MAX, goth, ori; //goth = go through
    //i am return only one parcel to their destination
    for(auto g:considering) {
        // g is parcel => g + N + M is the destination, we have to go throught this
        int pastThis = g + N + M;
        if(mn > d[from][pastThis] + d[pastThis][to] && (Cap[k] + q[g - N]) > q[to - N]) {
            mn = d[from][pastThis] + d[pastThis][to];
            ori = g;
            goth = pastThis;
        }
    }
    return {{goth, ori}, mn};
}

void initConfig() {
    for(int i = 0; i < needtotake.size(); i++) {
        int node = needtotake[i].second;    //* => currently accessing node
        int insRoute, mn = INT_MAX;
                
        //* when the current reaching node is a parcel
        if(node > N && node <= N + M) {
            bool rtg = false; // return then go
            int go, ori; // if have to return then go
            //* current parcel capacity us q[node - N]
            for(int k = 0; k < K; k++) {
                int last = initRoutes[k].back();
                if(remCap[k] >= q[node - N]) {
                    if(mn > d[last][node]) {
                        mn = d[last][node];
                        remCap[k] -= q[node - N];
                        insRoute = k;
                        rtg = false;
                    }
                } else {
                    int temp = INT_MAX, tempInsRoute;
                    bool tempRtg = false;
                    //? try to return things
                    pair<pair<int, int>, int> gothrought = try_to_return_thing(last, node, k, remCap);
                    int mntemp = gothrought.second;
                    if(mn > mntemp) {
                        mn = mntemp;
                        insRoute = k;
                        rtg = true;
                        go = gothrought.first.first;
                        ori = gothrought.first.second;
                    }
                }
            }
            // push to initRoute step
            if(rtg) {
                initRoutes[insRoute].push_back(go);
                initRoutes[insRoute].push_back(node);
                remCap[insRoute] = remCap[insRoute] + q[ori - N] - q[node - N];
                initDeliver[ori] = true;
            } else {
                initRoutes[insRoute].push_back(node);
                remCap[insRoute] -= q[node - N];
            }
        } else if(node >= 1 && node <= N) { //* the current node has a passenger waiting
            int mn = INT_MAX;
            for(int k = 0; k < K; k++) {
                int last = initRoutes[k].back();
                if(mn > d[last][node]) {
                    mn = d[last][node];
                    insRoute = k;
                }
            }
            initRoutes[insRoute].push_back(node);
            initRoutes[insRoute].push_back(node + N + M);
            
        }
    }

    // * fulfill the initial routes
    for(int k = 0; k < K; k++) {
        considering.clear();
        for(auto p:initRoutes[k]) {
            if(p > N && p <= N + M && !initDeliver[p]) considering.push_back(p);
        }
        for(auto p:considering) {
            initDeliver[p] = true;
            initRoutes[k] .push_back(p + N + M);
        }
        initRoutes[k].push_back(0);
    }
}

void printInitConfig() {
    cout << "need to take\n";
    for(auto i:needtotake) cout << i.first << " " << i.second << '\n';
    cout << '\n';
    cout << "Initial configuration\n";
    for(int i = 0; i < K; i++) {
        cout << "i = " << i << ":\n";
        for(auto j:initRoutes[i]) cout << j << ' ';
        cout << '\n';
    }
    cout << "Initial sum of each route\n";
    for(int k = 0; k < K; k++) {
        int sum = 0;
        for(int i = 1; i < initRoutes[k].size(); i++) {
            sum += d[initRoutes[k][i - 1]][initRoutes[k][i]];
        }
        cout << "Routes " << k << " = " << sum << "\n";
    }
}



// ! **************************REMINDER************************************* ! //

//* the index for car's capacity is in range (0, K - 1)
//* the index for weigh of parcels is in range(1, M)
//* passengers to their delivery point <=> i + N + M
//* parcels to their delivery point <=> i + N + M

// ! *********************************************************************** ! //
