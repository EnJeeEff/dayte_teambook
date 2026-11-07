/**
 * Author: dayte timofeyu finalku
 * Description: Минимум на отрезке статического массива; подходит любая идемпотентная операция (min, max, gcd).
 * Input: Sparse<T> s(a) по vector a; s.query(l, r) --- минимум на $[l, r]$, границы включительно.
 * Time: O(1) на запрос, O(n \log n) на построение
 */
const int LOG = 20; // 2^LOG > n

template <typename T>
struct Sparse {
    int n;
    vector<vector<T> > sparse;

    Sparse() = default;

    Sparse (vector<T>& a) {
        n = a.size();
        sparse.assign(LOG, vector<T>(n));
        build(a);
    }

    void build(vector<T> &based) {
        int i, j;
        for (i = n - 1; i >= 0; i--) {
            sparse[0][i] = based[i];
            for (j = 1; i + (1 << j) <= n; j++) {
                sparse[j][i] = min(sparse[j - 1][i], sparse[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int query(int a, int b) {
        int lg = log2(b - a + 1);
        return min(sparse[lg][a], sparse[lg][b - (1 << lg) + 1]);
    }
};
