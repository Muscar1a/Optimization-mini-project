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
    cin >> K;
    for(int t = 1; t <= K; t++) {
        cin >> x;
        for(int i = 1; i <= x; i++) {
            cin >> a[i];
        }
        int sum = 0;
        for(int i = 1; i <= x; i++) {
            sum += d[a[i - 1]][a[x]];
        }
        cout << t << ": " << sum << '\n';
    }

    cout << "My solution\n";

    cin >> K;
    for(int t = 1; t <= K; t++) {
        cin >> x;
        for(int i = 1; i <= x; i++) {
            cin >> a[i];
        }
        int sum = 0;
        for(int i = 1; i <= x; i++) {
            sum += d[a[i - 1]][a[x]];
        }
        cout << t << ": " << sum << '\n';
    }
    return 0;
}
