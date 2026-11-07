/**
 * Author: dayte timofeyu finalku
 * Description: Нерекурсивное дерево отрезков: максимум и его индекс на $[l, r)$. Для минимума --- min и $+10^{18}$.
 * Input: Maxtree t(a) по vector a; t.getMax(l, r) --- пара (максимум, индекс).
 * Time: O(\log n) на запрос, O(n) на построение
 */
struct Maxtree {
    int n;
    vector<pair<int, int> > tree;
 
    Maxtree(vector<int> els) {
        n = els.size();
        tree.assign(2 * n, {-1e18, -1});
        int i;
        for (i = 0; i < n; i++) {
            tree[i + n] = {els[i], i};
        }
        for (i = n - 1; i >= 0; i--) {
            tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
        }
    }
 
    pair<int, int> getMax(int l, int r) {
        l += n;
        r += n;
 
        pair<int, int> mx{-1e18, -1};
        while (l < r) {
            if (l & 1) {
                mx = max(mx, tree[l++]);
            }
            if (r & 1) {
                mx = max(mx, tree[--r]);
            }
            l >>= 1;
            r >>= 1;
        }
 
        return mx;
    }
};
