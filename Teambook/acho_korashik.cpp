/**
 * Author: dayte timofeyu finalku
 * Description: Ахо--Корасик: бор с суффиксными ссылками для поиска набора строк в тексте.
 * Input: addToTrie(s, id) для каждого образца из букв a--z. Переход по символу --- getGo(v, c), ближайший терминальный суффикс --- firstSuperSuf(v).
 * Time: O(n + m + z), $n$ --- длина текста, $m$ --- суммарная длина образцов, $z$ --- число вхождений
 */
const int al = 26;
struct Node {
    vector<int> go;
    int suf, supersuf;
    int parC, parent;
    int terminal;

    Node(int c, int par) {
        parC = c;
        parent = par;
        terminal = 0;
        // суффиксная ссылка
        suf = -1;
        // ближайший терминальный суффикс
        supersuf = -1;
        // переходы
        go.assign(al, -1);
    }
};

vector<Node> trie{Node(0, -1)};

int addToTrie(string &a, int id, int v = 0, int pos = 0) {
    if (pos == a.size()) {
        trie[v].terminal = 1;
        return v;
    }
    if (trie[v].go[a[pos] - 'a'] == -1) {
        trie.emplace_back(a[pos] - 'a', v);
        trie[v].go[a[pos] - 'a'] = trie.size() - 1;
    }
    return addToTrie(a, id, trie[v].go[a[pos] - 'a'], pos + 1);
}

int getGo(int v, int c);

int getSuf(int v) {
    if (trie[v].suf != -1)
        return trie[v].suf;
    if (v == 0 || trie[v].parent == 0)
        return trie[v].suf = 0;
    return trie[v].suf = getGo(getSuf(trie[v].parent), trie[v].parC);
}

int getGo(int v, int c) {
    if (c >= 'a')
        c -= 'a';
    if (trie[v].go[c] != -1)
        return trie[v].go[c];
    if (v == 0)
        return trie[v].go[c] = 0;
    return trie[v].go[c] = getGo(getSuf(v), c);
}

int firstSuperSuf(int v) {
    if (trie[v].supersuf != -1)
        return trie[v].supersuf;
    if (trie[v].terminal)
        return trie[v].supersuf = v;
    return trie[v].supersuf = firstSuperSuf(getSuf(v));
}
