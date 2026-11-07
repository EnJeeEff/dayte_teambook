/**
 * Author: dayte timofeyu finalku
 * Description: Суффиксный массив удвоением с цифровой сортировкой, LCP (Касаи) и число различных подстрок.
 * Input: строка s из stdin, к ней дописывается \$. Вывод: число различных непустых подстрок.
 * Time: O(n \log n)
 */
const int MAXN = 5e5 + 1;

int equiv[MAXN];

int n;
// стабильная сортировка пар классов
void radixSort(vector<tuple<int, int, int>> &array) {
    int i;
    // по второму, затем по первому
    for (const auto &type : {1, 0}) {
        auto getKey = [&](int pos) {
            return type == 1 ? get<1>(array[pos]) : get<0>(array[pos]);
        };

        vector<int> start(n), quantity(n);
        for (i = 0; i < n; i++) {
            quantity[getKey(i)]++;
        }
        for (i = 1; i < n; i++) {
            start[i] = start[i - 1] + quantity[i - 1];
        }

        vector<tuple<int, int, int> > newArray(n);
        for (i = 0; i < n; i++) {
            newArray[start[getKey(i)]++] = array[i];
        }

        array = newArray;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // $ меньше всех символов
    string str;
    cin >> str;
    str += '$';
    n = str.size();

    // классы для длины 1
    vector<tuple<int, int, int> > array(n);
    int i;
    for (i = 0; i < n; i++) {
        array[i] = {str[i], str[i], i};
    }
    sort(all(array));
    for (i = 1; i < n; i++) {
        auto [prevLeft, prevRight, prevPos] = array[i - 1];
        auto [left, right, pos] = array[i];
        equiv[pos] = equiv[prevPos] + (make_pair(prevLeft, prevRight) != make_pair(left, right));
    }

    // удваиваем длину, пересчитываем классы
    for (int k = 1; k < n; k <<= 1) {
        for (auto &[left, right, s] : array) {
            left = equiv[s];
            right = equiv[(s + k) % n];
        }
        radixSort(array);

        equiv[get<2>(array[0])] = 0;
        for (i = 1; i < n; i++) {
            auto [prevLeft, prevRight, prevPos] = array[i - 1];
            auto [left, right, pos] = array[i];
            equiv[pos] = equiv[prevPos] + (make_pair(prevLeft, prevRight) != make_pair(left, right));
        }
    }

    // LCP (Касаи)
    vector<int> suffInd(n);
    for (int i = 0; i < n; i++) { suffInd[get<2>(array[i])] = i; }
    vector<int> lcp(n - 1);
    int startAt = 0;
    for (int i = 0; i < n - 1; i++) {
        int prev = get<2>(array[suffInd[i] - 1]);
        int curr_cmp = startAt;
        while (str[i + curr_cmp] == str[prev + curr_cmp]) { curr_cmp++; }
        lcp[suffInd[i] - 1] = curr_cmp;
        startAt = max<int>(curr_cmp - 1, 0);
    }

    // число различных подстрок
    int diff = 0;
    for (int i = 0; i < lcp.size(); i++) {
        diff += n - 1 - i - lcp[i];
    }
    cout << diff << endl;
}
