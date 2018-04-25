#include <cassert>

#include "Geometry.h"

namespace {
Vector onBoth(Vector const &vector, int (*f)(int)) {
	return { f(vector.x), f(vector.y) };
}
} // namespace

bool overlap(Square const &a, Square const &b) {
	if (a.from.x < b.from.x && a.from.y < b.from.y) {
		return (a.from.x + a.size > b.from.x) && (a.from.y + a.size > b.from.y);
	}

	if (a.from.x < b.from.x && a.from.y >= b.from.y) {
		return (a.from.x + a.size > b.from.x) && (b.from.y + b.size > a.from.y);
	}

	if (a.from.x >= b.from.x && a.from.y >= b.from.y) {
		return (b.from.x + b.size > a.from.x) && (b.from.y + b.size > a.from.y);
	}

	assert(a.from.x >= b.from.x && a.from.y < b.from.y);
	return (b.from.x + b.size > a.from.x) && (a.from.y + a.size > b.from.y);
}

Vector one(Vector const &vector) {
	return onBoth(vector, [](int x) {
		if (x > 0)
			return +1;
		if (x < 0)
			return -1;
		return 0;
	});
}

Square round_x(Square const &square) {
	int const rx = square.from.x % square.size;
	int const x = square.from.x / square.size * square.size + (rx > square.size / 2 ? square.size : 0);
	return { { x, square.from.y }, square.size };
}

Square round_y(Square const &square) {
	int const ry = square.from.y % square.size;
	int const y = square.from.y / square.size * square.size + (ry > square.size / 2 ? square.size : 0);
	return { { square.from.x, y }, square.size };
}

Square round(Square const &square) {
	return round_y(round_x(square));
}

Direction other(Direction direction) {
	switch (direction) {
	case Direction::Down:
		return Direction::Up;
	case Direction::Left:
		return Direction::Right;
	case Direction::Up:
		return Direction::Down;
	case Direction::Right:
		return Direction::Left;
	case Direction::None:
		return Direction::None;
	default:
		assert(false);
		return direction;
	}
}

Vector toVector(Direction direction) {
	switch (direction) {
	case Direction::Up:
		return { 0, -1 };
	case Direction::Down:
		return { 0, +1 };
	case Direction::Left:
		return { -1, 0 };
	case Direction::Right:
		return { +1, 0 };
	case Direction::None:
		return { 0, 0 };
	default:
		assert(false);
		return { 0, 0 };
	}
}
