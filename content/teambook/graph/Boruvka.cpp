/**
 * Author: dayte timofeyu finalku
 * Description: Минимальное остовное дерево алгоритмом Борувки: на каждой фазе каждая компонента берёт минимальное исходящее ребро. Равные веса различаются парой (вес, $a \cdot$ BIG $+ b$). Удобен, когда минимальное ребро из компоненты находится быстро без явного графа.
 * Input: n, m, затем m рёбер (a, b, c), вершины с 1, $n <$ BIG. Вывод: вес остова.
 * Time: O(m \log n)
 */
const int MAXN = 2e5 + 1;
const int BIG = 1e9;
const int LOG = 21;
vector<pair<int, int> > adj[MAXN];
int n, m;

void solve() {
    cin >> n >> m;

    int i;
    for (i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }
    vector<int> setOf(n + 1);
    iota(all(setOf), 0);

    // ori[s] --- минимальное ребро из компоненты s
    vector<pair<int, int> > ori;
    vector<vector<int> > insideSet(n + 1);
    for (i = 0; i <= n; i++) {
        insideSet[i].push_back(i);
    }

    auto combine = [&](int a, int b) {
        a = setOf[a];
        b = setOf[b];
        if (setOf[a] == setOf[b]) {
            return;
        }
        if (insideSet[a].size() > insideSet[b].size()) {
            swap(a, b);
        }
        for (auto &el : insideSet[a]) {
            setOf[el] = b;
        }
        copy(all(insideSet[a]), back_inserter(insideSet[b]));
        insideSet[a].clear();
    };

    int t = LOG;
    int allW = 0;
    while (t--) {
        ori.assign(n + 1, make_pair((long long)1e18, 0LL));
        for (i = 1; i <= n; i++) {
            for (auto &[to, w] : adj[i]) {
                pair<int, int> curPair = {w, min(i, to) * BIG + max(i, to)};
                if (setOf[i] != setOf[to] && curPair < ori[setOf[i]]) {
                    ori[setOf[i]] = curPair;
                }
            }
        }

        for (i = 1; i <= n; i++) {
            if (setOf[i] != i || ori[i].second == 0) continue;
            int a = ori[i].second / BIG, b = ori[i].second % BIG;
            // a и b не обязательно лежат в i
            if (setOf[a] != setOf[b]) {
                combine(a, b);
                allW += ori[i].first;
            }
        }
    }

    cout << allW;
}
