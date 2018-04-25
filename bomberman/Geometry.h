#pragma once

#include <cassert>
#include <ostream>

class Point;
class Rectangle;
class Square;
class Vector;

class Point {
public:
	int x;
	int y;
};

inline bool operator==(Point const &a, Point const &b) {
	return (a.x == b.x) && (a.y == b.y);
}

inline bool operator!=(Point const &a, Point const &b) {
	return !(a == b);
}

class Rectangle {
public:
	Point from; // topleft
	Point to; // bottomright

	Vector size() const;
};

class Square {
public:
	Point from; // topleft
	int size;
};

inline bool operator==(Square const &a, Square const &b) {
	return (a.from == b.from) && (a.size == b.size);
}

inline bool operator!=(Square const &a, Square const &b) {
	return !(a == b);
}

Square round_x(Square const &square);
Square round_y(Square const &square);
Square round(Square const &square);

inline bool isCentered(Square const &square) {
	return square == round(square);
}

/**
 * @returns true iff the two squares overlap at least partially
 */
bool overlap(Square const &a, Square const &b);

class Vector {
public:
	int x;
	int y;
};

Vector one(Vector const &vector);

inline bool operator==(Vector const &a, Vector const &b) {
	return a.x == b.x && a.y == b.y;
}

inline bool operator!=(Vector const &a, Vector const &b) {
	return !(a == b);
}

inline Vector &operator+=(Vector &vec1, Vector const &vec2) {
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	return vec1;
}

inline Vector operator+(Vector const &vec1, Vector const &vec2) {
	Vector vec = vec1;
	vec += vec2;
	return vec;
}

inline Vector &operator-=(Vector &vec1, Vector const &vec2) {
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	return vec1;
}

inline Vector operator-(Vector const &vec1, Vector const &vec2) {
	Vector vec = vec1;
	vec -= vec2;
	return vec;
}

inline Vector &operator*=(Vector &vec, int m) {
	vec.x *= m;
	vec.y *= m;
	return vec;
}

inline Vector operator*(Vector const &vec, int m) {
	Vector v = vec;
	v *= m;
	return v;
}

inline Vector operator*(int m, Vector const &vec) {
	return vec * m;
}

inline Vector &operator/=(Vector &vec, int m) {
	vec.x /= m;
	vec.y /= m;
	return vec;
}

inline Vector operator/(Vector const &vec, int m) {
	Vector v = vec;
	v /= m;
	return v;
}

// Does not make sense
// inline Vector operator/(int m, Vector const & vec);

inline Point &operator+=(Point &point, Vector const &vector) {
	point.x += vector.x;
	point.y += vector.y;
	return point;
}

inline Point operator+(Point const &point, Vector const &vector) {
	Point p = point;
	p += vector;
	return p;
}

inline Vector operator-(Point const &a, Point const &b) {
	return { a.x - b.x, a.y - b.y };
}

inline Square &operator+=(Square &square, Vector const &vector) {
	square.from += vector;
	return square;
}

inline Square operator+(Square const &square, Vector const &vector) {
	Square s = square;
	s += vector;
	return s;
}

enum class Direction {
	None,
	Up,
	Down,
	Left,
	Right
};

Direction other(Direction direction);

Vector toVector(Direction direction);

inline Vector Rectangle::size() const {
	return to - from;
}

// Printing
inline std::ostream &operator<<(std::ostream &o, Point const &point) {
	o << "[" << point.x << "," << point.y << "]";
	return o;
}

inline std::ostream &operator<<(std::ostream &o, Rectangle const &rect) {
	o << "{" << rect.from << " -> " << rect.to << "}";
	return o;
}

inline std::ostream &operator<<(std::ostream &o, Square const &square) {
	Rectangle rect{ square.from, square.from + Vector{ square.size, square.size } };
	o << rect;
	return o;
}
