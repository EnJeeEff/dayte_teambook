/**
 * Author: dayte timofeyu finalku
 * Description: Прямая $ax + by + c = 0$: (a, b) --- нормаль, (-b, a) --- направление, знак value(p) --- сторона прямой. Сравнивать прямые только через sameLine и parallel.
 * Input: Требует Vectors.cpp с typedef double T. Line(a, b, c) или Line(p, q) по двум точкам.
 * Time: O(1)
 */
const double eps = 1e-9;

struct Line {
    double a, b, c;

    Line(double _a = 0, double _b = 0, double _c = 0) : a(_a), b(_b), c(_c) {}

    // через точки p != q
    Line(vec2 p, vec2 q) : a(q.y - p.y), b(p.x - q.x), c(-(a * p.x + b * p.y)) {}

    vec2 normal() const { return {a, b}; }
    vec2 dir() const { return {-b, a}; }
    double value(vec2 p) const { return a * p.x + b * p.y + c; }
};

bool collinear(vec2 a, vec2 b, vec2 c) {
    return fabs((b - a) % (c - a)) < eps;
}

bool parallel(const Line &l1, const Line &l2) {
    return fabs(l1.normal() % l2.normal()) < eps;
}

bool sameLine(const Line &l1, const Line &l2) {
    return parallel(l1, l2) && fabs(l1.a * l2.c - l2.a * l1.c) < eps && fabs(l1.b * l2.c - l2.b * l1.c) < eps;
}

// false, если параллельны
bool lineIntersection(const Line &l1, const Line &l2, vec2 &res) {
    double det = l1.a * l2.b - l2.a * l1.b;
    if (fabs(det) < eps) return false;
    res = vec2((l1.b * l2.c - l2.b * l1.c) / det, (l2.a * l1.c - l1.a * l2.c) / det);
    return true;
}

double distToLine(vec2 p, const Line &l) {
    return fabs(l.value(p)) / l.normal().length();
}

vec2 projection(vec2 p, const Line &l) {
    return p - l.normal() * (l.value(p) / l.normal().squareLength());
}

// серединный перпендикуляр
Line bisector(vec2 a, vec2 b) {
    return Line(2 * (b.x - a.x), 2 * (b.y - a.y), a.squareLength() - b.squareLength());
}

double distToSegment(vec2 p, vec2 a, vec2 b) {
    if ((a - b).squareLength() < eps) return (p - a).length(); // вырожденный отрезок
    if ((p - a) * (b - a) > 0 && (p - b) * (a - b) > 0)
        return fabs((p - a) % (p - b)) / (a - b).length();
    return min((p - a).length(), (p - b).length());
}

// угол в [0, pi]
double angle(vec2 a, vec2 b) {
    return atan2(fabs(a % b), a * b);
}
