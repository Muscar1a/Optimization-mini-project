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
vector<savings> saving;
vector<int> initRoutes[105], routes[105];

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
            saving.push_back({temp, i, j});
            s_value[{i, j}] = s_value[{j, i}] = temp;
        }
    }
    sort(saving.begin(), saving.end(),cmp); // use in clarke-wright savings

    for(int i = 0; i < K; i++) initRoutes[i].push_back(0);
}


void initConfig() {
    for(int i = 0; i < needtotake.size(); i++) {
        int node = needtotake[i].second;
        //* when the current reaching node is a parcel
        if(node > N && node <= N + M) {
            
        }
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
}

// ! **************************REMINDER************************************* ! //

//* the index for car's capacity is in range (0, K - 1)
//* the index for weigh of parcels is in range(1, M)
//* passengers to their delivery point <=> i + N + M
//* parcels to their delivery point <=> i + N + M

// ! *********************************************************************** ! //
