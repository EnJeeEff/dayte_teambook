/**
 * Author: dayte timofeyu finalku
 * Description: Прибавление в точке, сумма на отрезке.
 * Input: индексы $1..$MAXN$-1$; update(i, x); get(r) --- сумма на $[1, r]$; sum(l, r) --- сумма на $[l, r]$.
 * Time: O(\log n)
 */
const int MAXN = 5e5 + 1;
 
int f[MAXN];
void update(int a, int x) {
    for (; a < MAXN; a = (a | (a - 1)) + 1) {
        f[a] += x;
    }
}
 
int get(int a) {
    int res = 0;
    for (; a; a &= a - 1) {
        res += f[a];
    }
    return res;
}

int sum(int l, int r) {
    return get(r) - get(l - 1);
}
