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