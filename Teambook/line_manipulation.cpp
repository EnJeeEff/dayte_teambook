#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cmath>
#include<numeric>
#include<complex>
#include<iomanip>
#include<numbers>
#include<random>
#include<set>
#include<deque>
#include<unordered_map>

using namespace std;

typedef long long ll;

#define all(a) begin(a), end(a)
#define contains(st, a) (st.find(a) != st.end())

const double eps = 1e-12;

struct Line {
    double a, b, c;

    Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
};

struct Circle {
    double x, y, r;
};

struct vec2 {
    double x, y;

    vec2(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    vec2 operator+(const vec2 &other) const {
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator*(const double scalar) const {
        return vec2(x * scalar, y * scalar);
    }

    double squareLength() {
        return x * x + y * y;
    }

    double length() {
        return sqrt(squareLength());
    }
};

vec2 operator-(const vec2 &a, const vec2 &b) {
    return a + b * -1;
}

vec2 &operator+=(vec2 &a, const vec2 &b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

vec2 &operator-=(vec2 &a, const vec2 &b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

double operator%(const vec2 &a, const vec2 &b) {
    return a.x * b.y - a.y * b.x;
}

double operator*(const vec2 &a, const vec2 &b) {
    return a.x * b.x + a.y * b.y;
}

double distance(vec2 circ, Line line) {
    return pow((-line.a * circ.x - line.b * circ.y - line.c), 2) / (line.a * line.a + line.b * line.b);
}

vector<vec2> intersection(Circle a, Circle b) {
    double x1, y1, r1, x2, y2, r2;
    x1 = a.x;
    y1 = a.y;
    r1 = a.r;
    x2 = b.x;
    y2 = b.y;
    r2 = b.r;

    double squareDist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    double squareRad = (r1 + r2) * (r1 + r2);
    
    // if (squareDist == 0 && r1 == r2) {
    //     cout << 3;
    //     return 0;
    // } ИСКЛЮЧЕНО

    // Разница двух уравнений
    Line dif(2 * (x2 - x1), 2 * (y2 - y1), x1 * x1 + y1 * y1 - x2 * x2 - y2 * y2 - r1 * r1 + r2 * r2);

    double d = (-dif.a * x1 - dif.b * y1 - dif.c) / (dif.a * dif.a + dif.b * dif.b);
    double x0 = x1 + d * dif.a;
    double y0 = y1 + d * dif.b;

    d = distance({a.x, a.y}, dif);
    // if (d > r1 * r1) {
    //     cout << 0;
    //     return 0;
    // } ИСКЛЮЧЕНО
    if (fabs(d - r1 * r1) < eps) {
        return {{x0, y0}};
    }

    double cat = sqrt(r1 * r1 - d);
    double mult = sqrt(cat * cat / (dif.a * dif.a + dif.b * dif.b));
    double interX1 = x0 + dif.b * mult;
    double interY1 = y0 - dif.a * mult;
    double interX2 = x0 - dif.b * mult;
    double interY2 = y0 + dif.a * mult;
    return {{interX1, interY1}, {interX2, interY2}};
}

double distanceFromSegmentToPoint(vec2 a, vec2 b, vec2 p) {
    vec2 normal {(a - b).y, -(a - b).x};
    ll signA = (p - a) % normal;
    ll signB = (p - b) % normal;

    if (signA > 0 && signB < 0 || signA < 0 && signB > 0)
        return fabs((p - a) % (p - b)) / (a - b).length();
    return min((p - a).length(), (p - b).length());
}

int main() {
    double x1, y1, x2, y2, xt, yt, rt;
    cin >> x1 >> y1 >> x2 >> y2 >> xt >> yt >> rt;

    Circle danger{xt, yt, rt};
    cout << fixed << setprecision(16);
    if (distanceFromSegmentToPoint({x1, y1}, {x2, y2}, {xt, yt}) > rt - eps) {
        cout << sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
        return 0;
    }
    Circle fromA{x1, y1, sqrt((xt - x1) * (xt - x1) + (yt - y1) * (yt - y1) - rt * rt)};
    Circle fromB{x2, y2, sqrt((xt - x2) * (xt - x2) + (yt - y2) * (yt - y2) - rt * rt)};

    double minAns = 1e18;
    int i, j;
    vector<vec2> aInter = intersection(fromA, danger), bInter = intersection(fromB, danger);

    for (auto a : aInter) {
        for (auto b : bInter) {
            vec2 vecA{a.x - xt, a.y - yt}, vecB{b.x - xt, b.y - yt};
            double angle = atan2(abs(vecA.x * vecB.y - vecA.y * vecB.x), vecA.x * vecB.x + vecA.y * vecB.y);
            minAns = min(minAns, sqrt((a.x - x1) * (a.x - x1) + (a.y - y1) * (a.y - y1)) + angle * rt + sqrt((b.x - x2) * (b.x - x2) + (b.y - y2) * (b.y - y2)));
        }
    }

    cout << minAns;
}