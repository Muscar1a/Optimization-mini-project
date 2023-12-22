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
#define taskname "complete"
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
    int biggest_fitness_among_routes;
};

vector<population> pop;
population ans;

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
            if(route[i - 1].first <= N && route[i - 1].first > 0)
                sum += d[route[i - 1].second][route[i].first];
            else
                sum += d[route[i - 1].first][route[i].first];
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


vector<pii> current_sol;
vector<pii> best_sol;
vector<vector<pii>> tabu_list;

// ! *********************************************************************** ! //

bool check_valid(vector<pii> route) {
    // initDelivery is to check whether a passenger has been delivered or not
    for(int i = 1; i <= 2*N + 2*M; i++) initDeliver[i] = false;
    for(int i = 1; i < route.size() - 1; i++) {
        int nodea = route[i].first, nodeb = route[i].second;
        if(nodea <= N && nodea > 0) initDeliver[nodea] = true, initDeliver[nodeb] = true;
        else if(nodea > N && nodea <= N + M) {
            if(initDeliver[nodea + N + M] == true) return false;
            initDeliver[nodea] = true;
        } else if(nodea > N + M) {
            if(initDeliver[nodea - N - M] == false) return false;
            initDeliver[nodea + N + M] = true;
        }
    }
    return true;
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
    return neighborhood;
}


vector<pii> tabu_search(vector<pii> given) {
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
        if(!found)
            current_sol = neighbor[0];
        if(!tabu_list.empty()) tabu_list.erase(tabu_list.begin());
        if(cal_distance(current_sol) < cal_distance(best_sol) && check_valid(current_sol))
            best_sol = current_sol;
    }
    return best_sol;
}

int tabu_search_return_fitness(vector<pii> given) {
    current_sol.clear(), current_sol = given;
    best_sol.clear(), best_sol = current_sol;
    tabu_list.clear();
    
    if(given.size() == 3) return cal_distance(given);
    if(given.size() == 4) {
        if(given[1].first > N && given[1].first <= N + M) return cal_distance(given);
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
        if(cal_distance(current_sol) < cal_distance(best_sol) && check_valid(current_sol))
            best_sol = current_sol;
    }
    return cal_distance(best_sol);
}

// ! *********************************************************************** ! //


const int SIZEofPopulation = 16;
const int tournament_size = 4;
const double mutation_rate = 0.2;
const double crossover_rate = 0.5;

int delivery[1005], size_pop = 20;

vector<vector<int>> partial_full_pop;
vector<int> temp;
vector<vector<pii>> full_pop;

vector<pii> create_cycle_for_each(vector<int> route) {
    vector<pii> fullRoute;
    for(int i = 0; i < route.size(); i++) {
        int node = route[i];
        if(node == 0) fullRoute.push_back({0, -1});
        else {
            if(node <= N) fullRoute.push_back({node, node + N + M});
            else {
                fullRoute.push_back({node, -1});
                fullRoute.push_back({node + N + M, -1});
            }
        }
    }
    return fullRoute;
}

vector<vector<pii>> create_full_route(vector<int> route) {
    temp.clear(), partial_full_pop.clear();
    for(int i = 0; i < route.size(); i++) {
        if(i == 0) {
            temp.push_back(0);
            continue;
        }
        if(route[i] == 0) {
            temp.push_back(0);
            partial_full_pop.push_back(temp);
            temp.clear();
            temp.push_back(0);
        } else temp.push_back(route[i]);
    }
    full_pop.clear();
    for(auto i:partial_full_pop) {
        //for(auto j:i) cout << j << ' ';
        full_pop.push_back(create_cycle_for_each(i));
        //cout << '\n';
    }
    return full_pop;
}

int return_biggest_fitness_each_config(vector<int> child) {
    vector<vector<pii>> meo = create_full_route(child);
    int biggest_fitness = 0;
    for(auto x:meo) {
        int tmp = tabu_search_return_fitness(x);
        biggest_fitness = max(biggest_fitness, tmp);
    }
    return biggest_fitness;
}

//* createPopulation is ok
void createPopulation() {
    // cerr << "Create population\n";
    vector<int> t;
    for(int i = 1; i <= K; i++)
        t.push_back(0);
    for(int i = 1; i <= N + M; i++) 
        t.push_back(i);
    t.push_back(0);
    for(int p = 0; p < SIZEofPopulation; p++) {
        random_shuffle(t.begin() + 1, t.end() - 1);
        bool ok = true;
        while(1) {
            ok = true;
            for(int i = 1; i < t.size(); i++) {
                if(t[i] == 0 && t[i - 1] == 0) ok = false;
            }
            if(ok == true) break;
            else random_shuffle(t.begin() + 1, t.end() - 1);
        }
        pop.push_back({t, 0});
    }

    //* original size of 'pop' = 1000
    for(int x = 0; x < SIZEofPopulation; x++) {
        vector<vector<pii>> meomeo = create_full_route(pop[x].route);
        int biggest_fitness = 0;

        //* remind that the population fitness must store the value of longest route among routes;
        //* tabu search just return the shortest path among variation of combination of routes
        
        // cout << "Start tabu searching\n";
        for(auto x:meomeo) {
            // REACH;
            int tmp = tabu_search_return_fitness(x);
            biggest_fitness = max(biggest_fitness, tmp);
        }
        pop[x].biggest_fitness_among_routes = biggest_fitness;
    }
}

//* tournament is ok
population tournament(vector<population> pop, int tournament_size) {
    population select;
    int smallest_fitness = INT_MAX;
    for(int p = 0; p < tournament_size; p++) {
        int random_index = Rand(0, pop.size() - 1); 
        population par = pop[random_index];
        if(smallest_fitness > par.biggest_fitness_among_routes) {
            //!REACH;
            smallest_fitness = par.biggest_fitness_among_routes;
            select = par;
        }
    }
    return select;    
}

//* making_children is ok
pair<vector<int>, vector<int>> making_children(vector<int> par1, vector<int> par2) {
    int sz = par1.size();
    int point1 = sz / 3;
    int point2 = sz / 3  + point1 - 1;
    int ok1[2005], ok2[2005];
    // ok1 and ok2 are counting arrays, notice that ok1[0] and ok2[0] must <= K - 1
    vector<int> child1 = par1, child2 = par2;
    for(int i = point1; i <= point2; i++) {
        ok1[child1[i]]++;
        ok2[child2[i]]++;
    }
    int cnt1 = 1, cnt2 = 1;
    for(int i = 1; i < sz - 1; i++) {
        if(cnt1 == point1) cnt1 = point2 + 1;
        if(cnt2 == point1) cnt2 = point2 + 1;
        if(ok1[par2[i]] == 0) {
            child1[cnt1] = par2[i];
            ok1[par2[i]]++;
            cnt1++;
        } else if(par2[i] == 0 && ok1[par2[i]] < K - 2) {
            child1[cnt1] = par2[i];
            ok1[par2[i]]++;
            cnt1++;
        }
        if(ok2[par1[i]] == 0) {
            child2[cnt2] = par1[i];
            ok2[par1[i]]++; 
            cnt2++;
        } else if(par1[i] == 0 && ok2[par1[i]] < K - 2) {
            child2[cnt2] = par1[i];
            ok2[par1[i]]++;
            cnt2++;   
        }
    }
    return {child1, child2};
}


vector<population> crossover(vector<population> parents, double crossover_rate) {
    vector<population> offspring, par = parents;
    vector<int> parent_index(parents.size());
    iota(parent_index.begin(), parent_index.end(), 0);

    while(true) {
        if(parent_index.size() == 0) break;
        if(parent_index.size() == 1) {
            offspring.push_back(par[parent_index[0]]);
            break;
        }
        int par_index_0 = Rand(0, parent_index.size() - 1);
        int par_index_1 = Rand(0, parent_index.size() - 1);
        while(par_index_0 == par_index_1) {
            par_index_1 = Rand(0, parent_index.size() - 1);
        }
        if(par_index_0 > par_index_1) swap(par_index_0, par_index_1);
        parent_index.erase(parent_index.begin() + par_index_1);
        parent_index.erase(parent_index.begin() + par_index_0);
        
        population par_0 = par[par_index_0], par_1 = par[par_index_1];
        //vector<int> child_0 = par_0, child_1 = par_1;

        double r = double(Rand(0, 100)) * 1.0 / 100.0;

        if(r < crossover_rate) {
            offspring.push_back(par_0);
            offspring.push_back(par_1);
        } else {
            pair<vector<int>, vector<int>> children = making_children(par_0.route, par_1.route); 
            int t1 = return_biggest_fitness_each_config(children.first);
            int t2 = return_biggest_fitness_each_config(children.second);
            offspring.push_back({children.first, t1});
            offspring.push_back({children.second, t2});
        }
    }
    return offspring;
}


//* looks ok
vector<population> next_generation(vector<population> pop, int tournament_size, double mutation_rate, double crossover_rate) {
    vector<population> selected_parents;
    for(int n = 0; n < pop.size(); n++) {
        population selected_parent = tournament(pop, tournament_size);
        selected_parents.push_back(selected_parent);
    }
    vector<population> next_gen;
    next_gen = crossover(selected_parents, crossover_rate);
    //next_gen = mutate(next_gen, mutation_rate);
    return next_gen;
}

population evaluate(vector<population> pop) {
    population success;
    int biggest = INT_MAX;
    for(int i = 0; i < pop.size(); i++) {
        if(pop[i].biggest_fitness_among_routes < biggest) {
            success = pop[i];
            biggest = pop[i].biggest_fitness_among_routes;
        }
    }
    return success;
}


using namespace std;
using namespace std::chrono;


// ! **************************REMINDER************************************* ! //

//* the index for car's capacity is in range (0, K - 1)
//* the index for weigh of parcels is in rannge(1, M)

// ! *********************************************************************** ! //

void Enter() {
    cin >> N >> M >> K;
    if(N > 10) exit(0);
    for(int i = 1; i <= M; i++) cin >> q[i];
    for(int i = 0; i < K; i++) {
        cin >> Q[i];
        remCap[i] = Q[i];
    }
    for(int i = 0; i <= 2*N + 2*M; i++) {
        for(int j = 0; j <= 2*N + 2*M; j++) cin >> d[i][j];
    }
    for(int i = 0; i < K; i++) {
        routes[i].push_back(0);
    }
}

void solve() {
    createPopulation();
   // population parameter = pop
    for(int generation = 0; generation < 5; generation++) {
        pop = next_generation(pop, tournament_size, mutation_rate, crossover_rate);
        ans = evaluate(pop);
    //    cerr << "Generation = " << generation << '\n';
    }
    vector<vector<pii>> final_ans = create_full_route(ans.route);
    
    cout << K << "\n";
    for(int i = 0; i < K; i++) {
        vector<pii> temp = tabu_search(final_ans[i]);
        vector<int> meo;
        for(int i = 0; i < temp.size(); i++) {
            if(temp[i].first >= 1 && temp[i].first <= N) {
                meo.push_back(temp[i].first);
                meo.push_back(temp[i].second);
            } else meo.push_back(temp[i].first);
        }
        cout << meo.size() << '\n';
        for(auto x:meo) cout << x << ' ';
        cout << '\n';
    }
}

// TODO: write the main function and mutate
int32_t main() {
    
    tachyon;
    if(ifstream(taskname".inp")) {
        freopen(taskname".inp", "r", stdin);
        freopen(taskname".out", "w", stdout);
    }
    srand(static_cast<unsigned>(std::time(0)));
    auto start = high_resolution_clock::now();
    Enter();
    init();
    // testing();
    solve();
    
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(stop - start);
    cerr << fixed << setprecision(5) << (double)duration.count() / 1000 << '\n';
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
