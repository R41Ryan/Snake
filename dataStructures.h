#pragma once

struct Coordinates {
	int x;
	int y;

	Coordinates(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}

	bool operator ==(const Coordinates& c) {
		if (x == c.x && y == c.y)
			return true;
		return false;
	};
};

template
<typename T>
struct Vector2D {
	T a, b;

	Vector2D(int a = 0, int b = 0) {
		this->a = a;
		this->b = b;
	}

	bool operator ==(const Vector2D<int>& v) {
		if (a == v.a && b == v.b)
			return true;
		return false;
	};
};