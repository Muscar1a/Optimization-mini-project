#include<bits/stdc++.h>
using namespace std;

class Greedy_Method{
private:
    int num_vertices, distance_matrix[2005][2005], capacity;
    // num_vertices = num_cities
public:
    Greedy_Method(int _num_vertices, int _distance_matrix[][2005], int _capacity) {
        num_vertices = _num_vertices;
        for(int i = 0; i <= num_vertices; i++) {
            for(int j = 0; j <= num_vertices; j++) {
                distance_matrix[i][j] = _distance_matrix[i][j];
            }
        }
        capacity = _capacity;
    }

    auto greedy_search() {
        vector<int> frontier;
        frontier.push_back(1);
    }
};