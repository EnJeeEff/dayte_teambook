/**
 * Author: dayte timofeyu finalku
 * Description: Выпуклая оболочка обходом Грэхема; точки на сторонах не включаются.
 * Input: Требует Vectors.cpp с typedef long long T. n, затем n точек. Вывод: число вершин, вершины против часовой стрелки, площадь.
 * Time: O(n \log n)
 */
vec2 start(inf, inf);
int startInd;

bool comp(vec2 a, vec2 b) {
    a -= start;
    b -= start;
    return a % b == 0 && a.length() < b.length() || a % b > 0;
}

signed main() {
    int n;
    cin >> n;

    int i;
    vector<vec2> points(n);
    for (i = 0; i < n; i++) {
        cin >> points[i];
        if (start.x > points[i].x || start.x == points[i].x && start.y > points[i].y) {
            start = points[i];
            startInd = i;
        }
    }

    swap(points[startInd], points[0]);
    sort(points.begin() + 1, points.end(), comp);

    vector<vec2> stack{points[0], points[1]};

    for (i = 2; i < n; i++) {
        while (stack.size() > 1) {
            ll crossProd = (stack.back() - stack[stack.size() - 2]) % (points[i] - stack.back());
            if (crossProd <= 0) {
                stack.pop_back();
            }
            else {
                break;
            }
        }
        stack.push_back(points[i]);
    }

    cout << stack.size() << '\n';
    ll sum = 0;
    for (auto &p : stack)
        cout << p << '\n';

    for (i = 1; i < stack.size(); i++)
        sum += (stack[i - 1] - start) % (stack[i] - start);

    if (sum % 2) {
        cout << sum / 2 << ".5";
    }
    else {
        cout << sum / 2;
    }
}
