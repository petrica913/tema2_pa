#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    fstream fin("numarare.in");
    ofstream fout("numarare.out");

    int N, M;
    fin >> N >> M;
    vector<vector<int>> adj(N + 1), adj2(N + 1);

    set<int> in_degree;
    for (int i = 0; i < 2 * M; ++i) {
        int u, v;
        fin >> u >> v;
        if (i < M) {
            adj[u].push_back(v);
            in_degree.insert(u);
        } else {
            adj2[u].push_back(v);
        }
    }

    vector<int> dp(N + 1, 0);
    dp[1] = 1;
    for (int u : in_degree) {
        for (int v : adj[u]) {
            for (int w : adj2[u]) {
                if (w > v) {
                    break;
                }
                if (w == v) {
                    dp[v] = (dp[v] + dp[u]) % MOD;
                }
            }
        }
    }

    fout << dp[N] << "\n";
    return 0;
}
