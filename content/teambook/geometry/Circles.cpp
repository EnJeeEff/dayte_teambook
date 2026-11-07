/**
 * Author: dayte timofeyu finalku
 * Description: Окружности: пересечения, касательные, дуги, обход круга. Пересечения возвращают 0, 1 или 2 точки.
 * Input: Требует Vectors.cpp с typedef double T и Lines.cpp. Circle(o, r).
 * Time: O(1)
 */
struct Circle {
    vec2 o;
    double r;

    Circle(vec2 _o = {}, double _r = 0) : o(_o), r(_r) {}

    bool onBorder(vec2 p) const { return fabs((p - o).length() - r) < eps; }
    bool inside(vec2 p) const { return (p - o).length() < r + eps; } // внутри или на границе
};

// ab --- диаметр
Circle circleByDiameter(vec2 a, vec2 b) {
    vec2 o = (a + b) * 0.5;
    return Circle(o, (a - o).length());
}

// описанная; точки не коллинеарны
Circle circumcircle(vec2 a, vec2 b, vec2 c) {
    vec2 o;
    lineIntersection(bisector(a, b), bisector(a, c), o);
    return Circle(o, (a - o).length());
}

vector<vec2> intersect(const Circle &c, const Line &l) {
    vec2 h = projection(c.o, l);
    double d2 = (h - c.o).squareLength(), r2 = c.r * c.r;
    if (d2 > r2 + eps) return {};
    vec2 dir = l.dir() * (1 / l.dir().length());
    double len = sqrt(max(0.0, r2 - d2));
    if (len < eps) return {h};
    return {h + dir * len, h - dir * len};
}

// совпадающие и концентрические: {}
vector<vec2> intersect(const Circle &c1, const Circle &c2) {
    if ((c1.o - c2.o).squareLength() < eps) return {};
    Line radical(2 * (c2.o.x - c1.o.x), 2 * (c2.o.y - c1.o.y),
                 c1.o.squareLength() - c2.o.squareLength() - c1.r * c1.r + c2.r * c2.r);
    return intersect(c1, radical);
}

// p внутри: {}, на окружности: {p}
vector<vec2> tangentPoints(vec2 p, const Circle &c) {
    double d2 = (p - c.o).squareLength(), r2 = c.r * c.r;
    if (d2 < r2 - eps) return {};
    if (d2 < r2 + eps) return {p};
    return intersect(c, Circle(p, sqrt(d2 - r2)));
}

// меньшая дуга, a и b на окружности
double arcLength(const Circle &c, vec2 a, vec2 b) {
    return angle(a - c.o, b - c.o) * c.r;
}

// путь из a в b в обход круга
double shortestPathAroundCircle(vec2 a, vec2 b, const Circle &c) {
    if (distToSegment(c.o, a, b) > c.r - eps) return (a - b).length();
    double best = 1e18;
    for (vec2 ta : tangentPoints(a, c))
        for (vec2 tb : tangentPoints(b, c))
            best = min(best, (a - ta).length() + arcLength(c, ta, tb) + (b - tb).length());
    return best;
}
