/**
 * Author: dayte timofeyu finalku
 * Description: Минимальное остовное дерево алгоритмом Прима на матрице смежности; для плотных графов.
 * Input: n, m, затем m рёбер (a, b, c), вершины с 1, $n <$ MAXN, граф связный. Вывод: вес остова. Матрица занимает $8 \cdot$ MAXN$^2$ байт (72 МБ).
 * Time: O(n^2)
 */
const int MAXN = 3000;
int n, m;
int matrix[MAXN][MAXN];

void solve() {
    cin >> n >> m;

    int i;
    for (i = 0; i <= n; i++) {
        fill_n(matrix[i], n + 1, 1e18);
    }
    for (i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        matrix[a][b] = min(matrix[a][b], c);
        matrix[b][a] = min(matrix[b][a], c);
    }

    int t = n;
    int allW = 0;

    vector<int> minEdge(n + 1, 1e18), color(n + 1);
    minEdge[1] = 0;

    int u, v, w;
    while (t--) {
        v = -1;
        for (u = 1; u <= n; u++) {
            if (!color[u] && (v == -1 || minEdge[u] < minEdge[v])) {
                v = u;
            }
        }
        color[v] = true;
        if (v != 1) {
            allW += minEdge[v];
        }

        for (u = 1; u <= n; u++) {
            w = matrix[v][u];
            if (w < minEdge[u]) {
                minEdge[u] = w;
            }
        }
    }

    cout << allW;
}
