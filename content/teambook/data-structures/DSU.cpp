/**
 * Author: dayte timofeyu finalku
 * Description: Система непересекающихся множеств: объединение по размеру и сжатие путей.
 * Input: DSU d(n) --- элементы $0..n$; d.find(v), d.unite(a, b) --- true, если a и b были в разных множествах.
 * Time: O(\alpha(n))
 */
struct DSU {
    vector<int> parent, size;
    
    DSU(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find(parent[v]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
            return true;
        }
        return false;
    }
};
