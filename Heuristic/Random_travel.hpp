#include "declaration.hpp"

// ! ************************************************************************ ! //

class RandomizedTravel {
private:
    int numVertices;
    vector<vector<int>> edges;
    vector<int> vertices;
    int numEdges;
    vector<vector<int>> distanceMatrix;
    int numPassengers;
    int capacity;
    vector<vector<double>> boardProbability;
    vector<vector<double>> boardCount;

public:
    RandomizedTravel(int numVertices, vector<vector<int>> distanceMatrix, int capacity): 
        numVertices(numVertices),
        edges(numVertices),
        vertices(numVertices),
        numEdges(0),
        distanceMatrix(distanceMatrix),
        numPassengers((numVertices - 1) / 2),
        capacity(capacity),
        boardProbability(numVertices - 1, vector<double>(numVertices - 1, 0)),
        boardCount(numVertices - 1, vector<double>(numVertices - 1, 1)) {}
  

    auto random_travel(int maxiter = 10, int num_examples = 100) {
        
    }
};