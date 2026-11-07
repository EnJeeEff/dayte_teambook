/**
 * Author: dayte timofeyu finalku
 * Description: Точка или вектор. a * b --- скалярное произведение, a \% b --- косое: $>0$, если b левее a; $|a \% b|$ --- удвоенная площадь треугольника.
 * Input: T --- тип координат: long long для целочисленной геометрии, double для прямых и окружностей. cin >> p, cout << p.
 * Time: O(1)
 */
typedef long long T; // или double

struct vec2 {
    T x, y;

    vec2(T _x = 0, T _y = 0) : x(_x), y(_y) {}

    vec2 operator+(const vec2 &other) const {
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator*(const T scalar) const {
        return vec2(x * scalar, y * scalar);
    }

    T squareLength() const {
        return x * x + y * y;
    }

    double length() const {
        return sqrt((double)squareLength());
    }
};

vec2 operator-(const vec2 &a, const vec2 &b) {
    return a + b * -1;
}

T operator*(const vec2 &a, const vec2 &b) {
    return a.x * b.x + a.y * b.y;
}

T operator%(const vec2 &a, const vec2 &b) {
    return a.x * b.y - a.y * b.x;
}

vec2 &operator+=(vec2 &a, const vec2 &b) {
    a = a + b;
    return a;
}

vec2 &operator-=(vec2 &a, const vec2 &b) {
    a = a - b;
    return a;
}

istream& operator>>(istream &in, vec2 &p) {
    return in >> p.x >> p.y;
}

ostream& operator<<(ostream &out, const vec2 &p) {
    return out << p.x << ' ' << p.y;
}
