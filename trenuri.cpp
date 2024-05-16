#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int dfs(const string& node, const string& destination,
    unordered_map<string, int>& memo,
    unordered_map<string, vector<string>>& adj) {

    if (node == destination) {  // destination reached
        return 1;
    }

    if (memo.find(node) != memo.end()) {  // already visited
        return memo[node];  // return the memoized value
    }

    int maxLength = 0;
    for (const string& neighbor : adj[node]) {  // visit all neighbors
        // get the length of the path from the neighbor to the destination
        int currentLength = dfs(neighbor, destination, memo, adj);
        if (currentLength > 0) {  // if the path exists
            maxLength = max(maxLength, currentLength + 1);
        }
    }

    memo[node] = maxLength;  // memoize the maximum length
    return maxLength;  // return the maximum length
}

int main() {
    ifstream fin("trenuri.in");
    ofstream fout("trenuri.out");

    string startCity, endCity;
    fin >> startCity >> endCity;

    int M;
    fin >> M;

    unordered_map<string, vector<string>> adj;
    unordered_map<string, int> memo;

    for (int i = 0; i < M; ++i) {
        string u, v;
        fin >> u >> v;
        adj[u].push_back(v);
        if (adj.find(v) == adj.end()) {
            adj[v] = vector<string>();
        }
    }

    int result = dfs(startCity, endCity, memo, adj);
    fout << result << endl;

    fin.close();
    fout.close();

    return 0;
}
