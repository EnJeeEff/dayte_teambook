/**
 * Author: dayte timofeyu finalku
 * Description: p[i] --- длина наибольшего собственного префикса $a[0..i]$, совпадающего с его суффиксом.
 * Input: строка a. Для поиска needle раскомментировать первую строку: вхождения --- позиции, где p[i] = |needle|.
 * Time: O(|a| + |needle|)
 */
vector<int> prefixFunction(string a, string needle) {
    // a = needle + '#' + a;

    vector<int> p(a.size());
    int i;
    for (i = 1; i < a.size(); i++) {
        int k = p[i - 1];
        while (k > 0 && a[i] != a[k]) {
            k = p[k - 1];
        }
        if (a[i] == a[k]) {
            k++;
        }
        p[i] = k;
    }

    return p;
}
