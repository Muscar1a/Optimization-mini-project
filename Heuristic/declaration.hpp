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
#define REACH           cerr << "REACH HERE!\n"
const int maxn = 1e5 + 10, inf = 0x3f3f3f3f;
#define taskname "almost"
#define pii             pair<int, int>
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

struct population {
    vector<int> route;
    int fitness;
};
vector<population> pop;

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

}


// ! **************************REMINDER************************************* ! //

//* the index for car's capacity is in range (0, K - 1)
//* the index for weigh of parcels is in range(1, M)
//* passengers to their delivery point <=> i + N + M
//* parcels to their delivery point <=> i + N + M

// ! *********************************************************************** ! //
