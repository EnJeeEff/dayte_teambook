/**
 * Author: dayte timofeyu finalku
 * Description: Длина наибольшей строго возрастающей подпоследовательности. dp[l] --- минимальный последний элемент возрастающей подпоследовательности длины l.
 * Input: n, затем $a_0, \dots, a_{n-1}$ из stdin.
 * Time: O(n \log n)
 */
void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto &x : a) cin >> x;

    int i;
    vector<int> dp(n + 1, 1e18);
    dp[0] = -1e18;
    for (i = 0; i < n; i++) {
        auto lb = lower_bound(all(dp), a[i]);
        *lb = a[i];
    }

    for (i = n; i > 0 && dp[i] == 1e18; i--);
    cout << i;
}
