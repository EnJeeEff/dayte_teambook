/**
 * Author: dayte timofeyu finalku
 * Description: Максимальный поток: Форд--Фалкерсон с масштабированием.
 * Input: addDirectedEdge(a, b, c), задать start и finish. Все $c \le 2^{16}$, иначе увеличить начальный шаг.
 * Time: O(E^2 \log C)
 */
const int BL = 317;
const int MAXN = 101;
const int INF = 1e9;

vector<int> adj[MAXN];
int used[MAXN];

struct Edge {
    int to, c, f = 0;
};

// исток и сток
int start, finish;

vector<Edge> edges;

int n;
bool dfs(int v, int p) {
    if (v == finish)
        return p;

    used[v] = 1;

    for (auto id : adj[v]) {
        auto &e = edges[id];
        auto &inv = edges[id ^ 1];
        if (!used[e.to] && e.f < e.c && e.c - e.f >= p) {
            int change = dfs(e.to, p);
            if (change) {
                e.f += p;
                inv.f -= p;
                return 1;
            }
        }
    }

    return 0;
}

void addDirectedEdge(int a, int b, int capacity) {
    adj[a].push_back(edges.size());
    edges.push_back({b, capacity});
    adj[b].push_back(edges.size());
    edges.push_back({a, 0});
}

signed main() {
    // ...

    int ans = 0, add;
    for (add = (1 << 16); add; add >>= 1) {
        while (true) {
            ranges::fill(used, 0);
            bool delta = dfs(start, add);
            if (delta == 0) break;
            ans += add;
        }
    }

    cout << ans;
}
