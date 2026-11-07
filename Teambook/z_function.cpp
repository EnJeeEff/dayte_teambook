/**
 * Author: dayte timofeyu finalku
 * Description: z[i] --- длина наибольшего общего префикса строк $a$ и $a[i..]$; z[0] = 0.
 * Input: строка a. Для поиска needle раскомментировать первую строку: вхождения --- позиции, где z[i] = |needle|.
 * Time: O(|a| + |needle|)
 */
vector<int> zFunction(string a, string needle) {
    // a = needle + '#' + a;

    vector<int> z(a.size());
    int left = 0, right = 0;
    int i;
    for (i = 1; i < a.size(); i++) {
        z[i] = max<int>(0, min(right - i, z[i - left]));
        while (i + z[i] < a.size() && a[z[i]] == a[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }

    return z;
}
