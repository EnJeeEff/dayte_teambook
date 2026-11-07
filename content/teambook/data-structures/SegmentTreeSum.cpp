/**
 * Author: dayte timofeyu finalku
 * Description: Присваивание в точке, сумма на $[l, r)$.
 * Input: индексы $0..n-1$; setValue(0, 0, n, p, x), get(0, 0, n, l, r).
 * Time: O(\log n)
 */
const int MAXN = 2e5 + 1;
int segtree[4 * MAXN];
 
void setValue(int v, int tl, int tr, int p, int x) {
    if (tr - tl == 1) {
        segtree[v] = x;
        return;
    }
    int tc = (tl + tr) / 2;
    if (p < tc) {
        setValue(2 * v + 1, tl, tc, p, x);
    } else {
        setValue(2 * v + 2, tc, tr, p, x);
    }
    segtree[v] = segtree[2 * v + 1] + segtree[2 * v + 2];
}
 
int get(int v, int tl, int tr, int l, int r) {
    if (tl == l && tr == r) {
        return segtree[v];
    }
    int tc = (tl + tr) / 2;
    int ans = 0;
    if (l < tc) {
        ans += get(2 * v + 1, tl, tc, l, min(r, tc));
    }
    if (r > tc) {
        ans += get(2 * v + 2, tc, tr, max(l, tc), r);
    }
 
    return ans;
}
