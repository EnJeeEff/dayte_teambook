/**
 * Author: dayte timofeyu finalku
 * Description: Алгоритм Мо: offline-запросы на отрезках. Запросы группируются по блокам длины BL $\approx \sqrt n$, внутри блока сортируются по r змейкой. Здесь считается сумма; для другой функции поменять moveLeft и moveRight.
 * Input: n, m, затем $a_0, \dots, a_{n-1}$, затем m запросов (l, r), нумерация с 1, границы включительно. Вывод: ответ на каждый запрос.
 * Time: O((n + m) \sqrt n)
 */
const int BL = 300;

vector<int> a;
int l = 0, r = -1;
int sum = 0;

void moveRight(int to) {
    while (r < to) {
        sum += a[++r];
        assert(l <= r);
    }
    while (r > to) {
        sum -= a[r--];
        assert(l <= r);
    }
}

void moveLeft(int to) {
    while (l < to) {
        sum -= a[l++];
        assert(l <= r);
    }
    while (l > to) {
        sum += a[--l];
        assert(l <= r);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    int allBlocks = (n + BL - 1) / BL;

    int i, j;
    vector<vector<tuple<int, int, int> > > blocks(allBlocks);

    a.resize(n);
    for (auto &x : a) cin >> x;

    for (i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        blocks[l / BL].emplace_back(r, l, i);
    }
    int blId;

    for (blId = 0; blId < allBlocks; blId++) {
        if (blId % 2) {
            sort(all(blocks[blId]));
        } else {
            sort(all(blocks[blId]), greater<tuple<int, int, int> >());
        }
    }

    vector<int> ans(m);
    for (blId = 0; blId < (n + BL - 1) / BL; blId++) {
        for (auto &[qr, ql, qi] : blocks[blId]) {
            // порядок сдвигов сохраняет l <= r
            if (ql > r) {
                moveRight(qr);
                moveLeft(ql);
            } else {
                moveLeft(ql);
                moveRight(qr);
            }
            ans[qi] = sum;
        }
    }

    for (auto &x : ans) cout << x << '\n';
}
