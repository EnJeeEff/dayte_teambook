/**
 * Author: dayte timofeyu finalku
 * Description: LCA через минимум на эйлеровом обходе. Требует SparseTable.cpp.
 * Input: дерево в adj, корень 1; dfs1(), затем lcaSparse = Sparse<int>(eulerTour); lca(a, b).
 * Time: O(1) на запрос, O(n \log n) на построение
 */
int tin[MAXN], backTin[2 * MAXN];
int parent[MAXN];
vector<int> eulerTour;

void dfs1(int v = 1, int p = 1) {
    tin[v] = eulerTour.size();
    backTin[tin[v]] = v;
    eulerTour.push_back(tin[v]);
    parent[v] = p;
    for (auto &e : adj[v]) {
        if (e != p) {
            dfs1(e, v);
            eulerTour.push_back(tin[v]);
        }
    }
}

Sparse<int> lcaSparse;
int mark[MAXN];

int lca(int a, int b) {
    int ta = tin[a];
    int tb = tin[b];
    if (ta > tb) {
        swap(ta, tb);
    }
    int lca = backTin[lcaSparse.query(ta, tb)];

    return lca;
}
