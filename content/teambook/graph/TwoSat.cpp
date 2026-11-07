/**
 * Author: dayte timofeyu finalku
 * Description: 2-SAT через компоненты сильной связности (Косарайю). Вершина $2i$ --- $x_i$, $2i+1$ --- $\lnot x_i$.
 * Input: n, m, затем m строк (a, ta, b, tb) --- дизъюнкция $(x_a = t_a) \lor (x_b = t_b)$, переменные с 0. Вывод: строка из n значений или unsat.
 * Time: O(n + m)
 */
const int MAXN = 2e5 * 2 + 2;
vector<int> adj[MAXN], adjRev[MAXN];
int color[MAXN], comp[MAXN];

vector<int> topsort;
void dfs1(int v) {
    if (color[v]) {
        return;
    }
    color[v] = 1;
    for (auto &e : adj[v]) {
        dfs1(e);
    }
    topsort.push_back(v);
}

int compTimer = 0;
void dfs2(int v) {
    comp[v] = compTimer;
    for (auto &e : adjRev[v]) {
        if (!comp[e]) {
            dfs2(e);
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    int i;
    for (i = 0; i < m; i++) {
        int ai, t1, bi, t2;
        cin >> ai >> t1 >> bi >> t2;
        int aPos = ai * 2, aNeg = ai * 2 + 1;
        int bPos = bi * 2, bNeg = bi * 2 + 1;
        if (!t1) {
            swap(aPos, aNeg);
        }
        if (!t2) {
            swap(bPos, bNeg);
        }
        adj[aNeg].push_back(bPos);
        adj[bNeg].push_back(aPos);

        adjRev[bPos].push_back(aNeg);
        adjRev[aPos].push_back(bNeg);
    }

    for (i = 0; i < 2 * n; i++) {
        dfs1(i);
    }
    reverse(all(topsort));

    for (auto &i : topsort) {
        if (!comp[i]) {
            compTimer++;
            dfs2(i);
        }
    }

    bool sat = true;
    for (i = 0; i < n; i++) {
        sat &= comp[i * 2] != comp[i * 2 + 1];
    }
    if (!sat) {
        cout << "unsat";
    } else {
        for (i = 0; i < n; i++) {
            cout << (comp[i * 2] > comp[i * 2 + 1]);
        }
    }
    cout << '\n';
    topsort.clear();
    compTimer = 0;
    for (i = 0; i < 2 * n; i++) {
        comp[i] = color[i] = 0;
        adj[i].clear();
        adjRev[i].clear();
    }
}
