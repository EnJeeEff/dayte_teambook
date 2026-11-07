/**
 * Author: dayte timofeyu finalku
 * Description: Прибавление и максимум на $[l, r)$ с отложенными операциями.
 * Input: индексы $0..n-1$; add(0, 0, n, x, l, r), get(0, 0, n, l, r).
 * Time: O(\log n)
 */
const int MAXN = 2E5 + 1;
int segtree[MAXN * 4];
int push[MAXN * 4];

void make_push(int v) {
    push[2 * v + 1] += push[v];
    push[2 * v + 2] += push[v];
    segtree[2 * v + 1] += push[v];
    segtree[2 * v + 2] += push[v];
    push[v] = 0;
}

void add(int v, int tl, int tr, int up, int l, int r) {
    if (tl == l && tr == r) {
        push[v] += up;
        segtree[v] += up;
        return;
    }
    int tc = (tl + tr) / 2;
    make_push(v);
    if (l < tc) {
        add(2 * v + 1, tl, tc, up, l, min(tc, r));
    }
    if (r > tc) {
        add(2 * v + 2, tc, tr, up, max(l, tc), r);
    }

    segtree[v] = max(segtree[2 * v + 1], segtree[2 * v + 2]);
}

int get(int v, int tl, int tr, int l, int r) {
    if (tl == l && tr == r) {
        return segtree[v];
    }
    int tc = (tl + tr) / 2;
    int ans = -1e18;
    make_push(v);
    if (l < tc) {
        ans = max(ans, get(2 * v + 1, tl, tc, l, min(r, tc)));
    }
    if (r > tc) {
        ans = max(ans, get(2 * v + 2, tc, tr, max(l, tc), r));
    }

    return ans;
}
