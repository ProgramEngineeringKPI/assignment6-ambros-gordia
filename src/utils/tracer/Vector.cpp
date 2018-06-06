#include "Tracer.hpp"

Vector::Vector() : x(0), y(0), z(0) {}

Vector::~Vector()
{
	// cout << "v destructed" << endl;
}

Vector::Vector(const float coordinates[3])
{
	x = coordinates[0];
	y = coordinates[1];
	z = coordinates[2];
}

Vector::Vector(vector<float> vector)
{
	x = vector[0];
	y = vector[1];
	z = vector[2];
}

Vector::Vector(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

Vector::operator bool()
{
	return intersects;
}

Vector Vector::operator+(Vector &v)
{
	return Vector(x + v.x, y + v.y, z + v.z);
}
Vector Vector::operator-(Vector &v)
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(float num)
{
	return Vector(x * num, y * num, z * num);
}

Vector Vector::operator/(float num)
{
	return Vector(x / num, y / num, z / num);
}

bool Vector::operator==(Vector &v)
{
	return (x == v.x) && (y == v.y) && (z == v.z);
}

float Vector::dot(Vector &v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector Vector::cross(Vector &v)
{
	return Vector(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}

Vector Vector::normalize()
{
	float l = sqrtf(x * x + y * y + z * z);
	return *new Vector(x / l, y / l, z / l);
}

float Vector::length()
{
	return sqrtf(x * x + y * y + z * z);
}

float Vector::angle(Vector &v)
{
	return acosf(dot(v) / (length() * v.length()));
}

void Vector::print()
{
	cout << "(" << x << ", " << y << ", " << z << ")\n";
}