
#include "common.h"
#include <algorithm>
#include <climits>
#include <queue>

struct FlowEdge {
    int to;
    int rev;
    long long capacity;
};

static void addEdge(vector<vector<FlowEdge>>& g, int u, int v,
                    long long capacity) {
    FlowEdge a{v, (int)g[v].size(), capacity};
    FlowEdge b{u, (int)g[u].size(), 0};
    g[u].push_back(a);
    g[v].push_back(b);
}

static long long dfs(int u, int sink, long long pushed,
                     vector<int>& level, vector<int>& ptr,
                     vector<vector<FlowEdge>>& g) {
    if (u == sink)
        return pushed;

    for (int& i = ptr[u]; i < (int)g[u].size(); i++) {
        FlowEdge& e = g[u][i];

        if (e.capacity <= 0 || level[e.to] != level[u] + 1)
            continue;

        long long flow = dfs(e.to, sink, min(pushed, e.capacity),
                             level, ptr, g);

        if (flow == 0)
            continue;

        e.capacity -= flow;
        g[e.to][e.rev].capacity += flow;
        return flow;
    }

    return 0;
}

FlowResult maxflow(const Graph& input) {
    vector<vector<FlowEdge>> g(input.V);

    for (int u = 0; u < input.V; u++) {
        for (auto e : input.adj[u])
            addEdge(g, u, e.to, e.capacity);
    }

    long long flow = 0;
    vector<int> level(input.V);
    vector<int> ptr(input.V);

    while (true) {
        fill(level.begin(), level.end(), -1);

        queue<int> q;
        q.push(input.source);
        level[input.source] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto e : g[u]) {
                if (e.capacity > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }

        if (level[input.sink] == -1)
            break;

        fill(ptr.begin(), ptr.end(), 0);

        while (true) {
            long long pushed = dfs(input.source, input.sink, LLONG_MAX,
                                   level, ptr, g);

            if (pushed == 0)
                break;

            flow += pushed;
        }
    }

    vector<bool> visited(input.V, false);
    queue<int> q;
    q.push(input.source);
    visited[input.source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto e : g[u]) {
            if (e.capacity > 0 && !visited[e.to]) {
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }

    FlowResult result;
    result.maxFlow = flow;
    result.minCut = 0;

    for (int i = 0; i < input.V; i++) {
        if (visited[i])
            result.sourceSide.push_back(i);
        else
            result.sinkSide.push_back(i);
    }

    for (int u = 0; u < input.V; u++) {
        for (auto e : input.adj[u]) {
            if (visited[u] && !visited[e.to]) {
                result.minCut += e.capacity;
                result.cutEdges.push_back({u, e.to, e.capacity});
            }
        }
    }

    return result;
}
