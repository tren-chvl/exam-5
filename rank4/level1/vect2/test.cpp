#include "vect2.hpp"

vect2::vect2()
{
	this->x = 0;
	this->y = 0;
}

vect2::vect2(int n1, int n2)
{
	this->x = n1;
	this->y = n2;
}

vect2::vect2(const vect2 &other)
{
	*this = other;
}


vect2 &vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		this->x = other.x;
		this->y = other.y;
	}
	return	*this;
}

int vect2::operator[](int index) const
{
	if (index == 0)	
		return (this->x);
	return this->y;
}

int &vect2::operator[](int index)
{
	if (index == 0)	
		return (this->x);
	return this->y;
}


vect2 vect2::operator-() const
{
	vect2 tmp = *this;
	tmp[0] = -tmp[0];
	tmp[1] = -tmp[1];
	return tmp;
}

vect2 vect2::operator*(int num) const
{
	vect2 tmp;
	tmp.x = this->x * num;
	tmp.y = this->y * num;
	return tmp;
}

vect2 &vect2::operator*=(int num)
{
	this->x *= num;
	this->y *= num;
	return *this;
}

vect2 &vect2::operator+=(const vect2 &other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

vect2 &vect2::operator*=(const vect2 &other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

vect2 &vect2::operator-=(const vect2 &other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

vect2 vect2::operator+(const vect2 &other) const
{
	vect2 tmp = *this;
	tmp.x += other.x;
	tmp.y += other.y;
	return tmp;
}

vect2 vect2::operator*(const vect2 &other) const
{
	vect2 tmp = *this;
	tmp.x *= other.x;
	tmp.y *= other.y;
	return tmp;
}

vect2 vect2::operator-(const vect2 &other) const
{
	vect2 tmp = *this;
	tmp.x -= other.x;
	tmp.y -= other.y;
	return tmp;
}

vect2 &vect2::operator++()
{
	this->x += 1;
	this->y += 1;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2 tmp = *this;

	++(*this);
	return tmp;
}

vect2 &vect2::operator--()
{
	this->x -= 1;
	this->y -= 1;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2 tmp = *this;

	--(*this);
	return tmp;
}

bool vect2::operator==(const vect2 &other) const
{
	if ((this->x == other.x) && (this->y == other.y))
		return true;
	return false;
}

bool vect2::operator!=(const vect2 &other) const
{
	return (!(*this == other));
}


vect2::~vect2() {}


std::ostream &operator<<(std::ostream &os, const vect2 &other)
{
	os << "{" << other[0] << ", " << other[1] << "}";
	return os;
}

vect2 operator*(int num, const vect2 &other)
{
	vect2 tmp(other);
	tmp *= num;
	return tmp;
}