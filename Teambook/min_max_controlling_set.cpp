/**
 * Author: dayte timofeyu finalku
 * Description: Минимальное вершинное покрытие двудольного графа (Кёниг); его дополнение --- максимальное независимое множество. Требует Matchings.cpp.
 * Input: n, m --- размеры долей, затем рёбра (a, b) до конца ввода, нумерация с 1. Вывод: размер паросочетания; размеры частей покрытия; вершины покрытия в левой доле, затем в правой.
 * Time: O(VE)
 */
bool saturatedL[MAXN], visL[MAXN], visR[MAXN];
void dfs2(int v) {
    if (visL[v]) {
        return;
    }

    visL[v] = 1;
    for (auto &e : leftPart[v]) {
        visR[e] = 1;
        if (match[e] != -1) {
            dfs2(match[e]);
        }
    }
}

signed main() {
    ranges::fill(match, -1);
    int n, m;
    cin >> n >> m;

    int i, j;
    int a, b;
    while (cin >> a >> b) {
        a--; b--;
        leftPart[a].push_back(b);
    }

    kuhn();

    for (i = 0; i < m; i++) {
        if (match[i] != -1) {
            saturatedL[match[i]] = true;
        }
    }

    for (i = 0; i < n; i++) {
        if (!saturatedL[i]) {
            dfs2(i);
        }
    }

    vector<int> firstSet, secondSet;
    for (i = 0; i < n; i++) {
        if (!visL[i]) {
            firstSet.push_back(i);
        }
    }
    for (i = 0; i < m; i++) {
        if (visR[i]) {
            secondSet.push_back(i);
        }
    }

    cout << power << '\n' << firstSet.size() << ' ' << secondSet.size() << '\n';
    for (auto &el : firstSet)
        cout << el + 1 << ' ';
    cout << '\n';
    for (auto &el : secondSet)
        cout << el + 1 << ' ';
}
