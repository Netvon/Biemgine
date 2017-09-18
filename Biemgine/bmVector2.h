#pragma once

class bmVector2 {
public:
	bmVector2();
	bmVector2(float x_, float y_) : x(x_), y(y_) { };

	float getX();
	float getY();

	void setX(float x_) { x = x_; }
	void setY(float y_) { y = y_; }

	float distance(const bmVector2& other);
	float normalize();
	float length();

	void operator+=(const bmVector2& other);
	void operator-=(const bmVector2& other);
	void operator*=(float value);
	
private:
	float x, y;
};