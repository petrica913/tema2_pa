#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Graph {
    int64_t to, cost;
};

vector<int64_t> dijkstra(int64_t source, const vector<vector<Graph>>& adj) {
    int64_t n = adj.size();
    vector<int64_t> d(n, INT64_MAX);

    priority_queue<pair<int64_t, int64_t>, vector<pair<int64_t, int64_t>>,
                    greater<pair<int64_t, int64_t>>> pq;

    d[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int64_t distance = pq.top().first;
        int64_t node = pq.top().second;
        pq.pop();

        for (const auto& edge : adj[node]) {
            int64_t neigh = edge.to;
            int64_t new_dist = distance + edge.cost;

            if (new_dist < d[neigh]) {
                d[neigh] = new_dist;
                pq.push({new_dist, neigh});
            }
        }
    }

    return d;
}

int main() {
    int64_t n, m;
    ifstream fin("drumuri.in");
    ofstream fout("drumuri.out");
    fin >> n >> m;
    vector<vector<Graph>> g(n + 1), gt(n + 1);
    for (int64_t i = 0; i < m; i++) {
        int64_t a, b, c;
        fin >> a >> b >> c;
        g[a].push_back({b, c});
        gt[b].push_back({a, c});
    }
    int64_t x, y, z;
    fin >> x >> y >> z;
    vector<int64_t> distX = dijkstra(x, g);
    vector<int64_t> distY = dijkstra(y, g);
    vector<int64_t> distZ = dijkstra(z, gt);
    int64_t minDist = INT64_MAX;
    for (int64_t i = 1; i <= n; i++) {
        if (distX[i] == INT64_MAX ||
            distY[i] == INT64_MAX || distZ[i] == INT64_MAX) {
            continue;
        }
        int64_t sum = distX[i] + distY[i] + distZ[i];
        if (sum < minDist) {
            minDist = sum;
        }
    }
    fout << minDist << endl;
    return 0;
}
