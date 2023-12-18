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
#define taskname "checking"

// ! ********************************************************************** ! //

int n, N, M, K;
int x, a[2005], q[2005], Q[2005];
vector<int> routes[1005];
int d[1005][1005];


int32_t main() {
    if(ifstream(taskname".inp")) {
        freopen(taskname".inp", "r", stdin);
        freopen(taskname".out", "w", stdout);
    }
    cin >> N >> M >> K;
    for(int i = 1; i <= M; i++) cin >> q[i];
    for(int i = 0; i < K; i++) cin >> Q[i];
    for(int i = 0; i <= 2*N + 2*M; i++) {
        for(int j = 0; j <= 2*N + 2*M; j++) cin >> d[i][j];
    }

    cout << "Teacher's solution\n";

    int sum = 0;
    //cin >> K;
    //for(int t = 1; t <= K; t++) {
        cin >> x;
        for(int i = 1; i <= x; i++) {
            cin >> a[i];
        }
        for(int i = 2; i <= x; i++) {
            cout << "a[i-1] = " << a[i-1] << " - a[i] = " << a[i] << " - " << d[a[i - 1]][a[i]] << '\n';
            sum += d[a[i - 1]][a[i]];
        }
        cout << sum << '\n';
    //}

    sum = 0;
    cout << "My solution\n";
    //cin >> K;
    //for(int t = 1; t <= K; t++) {
        cin >> x;
        for(int i = 1; i <= x; i++) {
            cin >> a[i];
        }
        for(int i = 2; i <= x; i++) {
            cout << "a[i-1] = " << a[i-1] << " - a[i] = " << a[i] << " - " << d[a[i - 1]][a[i]] << '\n';
            sum += d[a[i - 1]][a[i]];
        }
        cout << sum << '\n';
    //
    cout << "Testing\n";
    vector<pair<int, int>> route({{0, -1}, {4, -1}, {3, 9}, {6, -1}, {12, -1}, {10, -1}, {2, 8}, {0, -1}});
    sum = 0;
    for(int i = 1; i < route.size(); i++) {
        if(route[i].first <= N && route[i].first > 0) {
            if(route[i - 1].first <= N && route[i].first > 0) {
                sum += d[route[i - 1].second][route[i].first];
                sum += d[route[i].first][route[i].second];
            } else {
                sum += d[route[i - 1].first][route[i].first];
                sum += d[route[i].first][route[i].second];
            }
        } else {
            if(route[i - 1].first <= N && route[i - 1].first > 0) 
                sum += d[route[i - 1].second][route[i].first];
            else sum += d[route[i - 1].first][route[i].first];
        }
    }
    cout << "\n" << sum;
    return 0;
}