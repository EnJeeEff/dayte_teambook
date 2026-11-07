/**
 * Author: dayte timofeyu finalku
 * Description: Heavy-light декомпозиция: сумма на пути через $O(\log n)$ отрезков эйлерова обхода.
 * Input: дерево в adj, корень 1; вызвать dfsSubtrees(), eulerTour(). add и sum --- заглушки под Фенвика или дерево отрезков по позициям tin. getSum(a, b) --- сумма на пути.
 * Time: O(\log^2 n) на запрос, O(n) на построение
 */
const int MAXN = 1e5 + 1;
const int INF = 1e9;

int valueOf[MAXN];
int sizes[MAXN], parentOf[MAXN], tin[MAXN], tout[MAXN], top[MAXN];

vector<int> adj[MAXN];

// размеры поддеревьев, тяжёлый сын --- adj[v][0]
void dfsSubtrees(int v = 1, int p = -1) {
    sizes[v] = 1;
    parentOf[v] = p;
    for (auto &e : adj[v]) {
        if (e != p) {
            dfsSubtrees(e, v);
            sizes[v] += sizes[e];
        }
    }
    if (adj[v].size() == 1 && adj[v][0] == p) return;

    int maxSubtree = 0;
    int maxInd;
    for (int i = 0; i < adj[v].size(); i++) {
        if (adj[v][i] != p && maxSubtree < sizes[adj[v][i]]) {
            maxSubtree = sizes[adj[v][i]];
            maxInd = i;
        }
    }
    swap(adj[v][maxInd], adj[v][0]);
}

vector<int> tour{0};
void eulerTour(int v = 1, int head = 1, int p = -1) {
    tin[v] = tour.size();
    top[v] = head;
    tour.push_back(0);
    if (adj[v].size() != 1 || adj[v][0] != p) {
        eulerTour(adj[v][0], head, v);
        for (int i = 1; i < adj[v].size(); i++) {
            if (adj[v][i] != p) {
                eulerTour(adj[v][i], adj[v][i], v);
            }
        }
    }

    tout[v] = tour.size() - 1;
}

void add(int ind, int value) {} // заглушка

int sum(int a, int b) {} // заглушка

bool isAncestor(int v, int to) {
    return tin[v] <= tin[to] && tout[v] >= tout[to];
}

int getSum(int a, int b) {
    int res = 0;
    while (!isAncestor(top[a], b)) {
        res += sum(tin[top[a]], tin[a]);
        a = parentOf[top[a]];
    }
    while (top[a] != top[b]) {
        res += sum(tin[top[b]], tin[b]);
        b = parentOf[top[b]];
    }

    if (tin[a] > tin[b]) swap(a, b);
    res += sum(tin[a], tin[b]);

    return res;
}
