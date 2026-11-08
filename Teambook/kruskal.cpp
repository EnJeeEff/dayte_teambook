/**
 * Author: dayte timofeyu finalku
 * Description: Минимальное остовное дерево алгоритмом Краскала. Требует DSU.cpp.
 * Input: n, m, затем m рёбер (a, b, c), вершины с 1. Вывод: вес остова.
 * Time: O(m \log m)
 */
void solve() {
    int n, m;
    cin >> n >> m;

    int i;
    DSU dsu(n + 1);
    vector<tuple<int, int, int> > edg;
    for (i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edg.emplace_back(c, a, b);
    }
    sort(all(edg));

    int allW = 0;
    for (auto &[c, a, b] : edg) {
        if (dsu.unite(a, b)) {
            allW += c;
        }
    }

    cout << allW;
}
