#include <bits/stdc++.h>
using namespace std;

void solchuan() {

}

string bai = "";
int32_t main() {

    for(int test = 1; test <= 20; test++){
		
        string s = to_string(test);
        
        string in = "E:/bikipluyenrong/baitap/" + bai + "/test" + s + "/" + bai + ".inp";
        string ou = "E:/bikipluyenrong/baitap/" + bai + "/test" + s + "/" + bai + ".out";
        cerr << ou << "\n";
        freopen(in.c_str(), "r", stdin);
        freopen(ou.c_str(), "w", stdout);

		s = "";
        solchuan();
        // cerr << in << "\n" << ou << "\n"; 
    }
    return 0;
}
