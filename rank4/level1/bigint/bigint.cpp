#include "bigint.hpp"

std::string reverseStr(const std::string &s)
{
	std::string r;
	for (size_t i = s.size(); i > 0; i--)
		r.push_back(s[i - 1]);
	return r;
}

unsigned int stringToUInt(const std::string &s)
{
	std::stringstream ss(s);
	unsigned int n = 0;
	ss >> n;
	return n;
}

void normalize(std::string &s)
{
	size_t i = 0;
	while (i + 1 < s.size() && s[i] == '0')
		i++;
	s.erase(0, i);
}

std::string bigint::getStr() const {
	return str;
}


bigint::bigint() : str("0") {}

bigint::bigint(unsigned int n)
{
	std::stringstream ss;
	ss << n;
	str = ss.str();
}

bigint::bigint(const bigint &other)
{
	str = other.str;
}

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
		str = other.str;
	return *this;
}


bigint bigint::operator+(const bigint &other) const
{
	std::string a = reverseStr(str);
	std::string b = reverseStr(other.str);

	while (a.size() < b.size()) a.push_back('0');
	while (b.size() < a.size()) b.push_back('0');

	std::string res;
	int carry = 0;

	for (size_t i = 0; i < a.size(); i++)
	{
		int d1 = a[i] - '0';
		int d2 = b[i] - '0';
		int sum = d1 + d2 + carry;

		res.push_back(char((sum % 10) + '0'));
		carry = sum / 10;
	}

	if (carry)
		res.push_back(char(carry + '0'));

	res = reverseStr(res);
	normalize(res);

	bigint out;
	out.str = res;
	return out;
}

bigint &bigint::operator+=(const bigint &other)
{
	*this = *this + other;
	return *this;
}


bigint &bigint::operator++()
{
	*this += bigint(1);
	return *this;
}

bigint bigint::operator++(int)
{
	bigint tmp(*this);
	*this += bigint(1);
	return tmp;
}


bigint bigint::operator<<(unsigned int n) const
{
	if (str == "0")
		return *this;

	bigint out(*this);
	out.str.append(n, '0');
	return out;
}

bigint &bigint::operator<<=(unsigned int n)
{
	*this = *this << n;
	return *this;
}

bigint bigint::operator<<(const bigint &other) const
{
	return *this << stringToUInt(other.str);
}

bigint &bigint::operator<<=(const bigint &other)
{
	*this = *this << stringToUInt(other.str);
	return *this;
}


bigint bigint::operator>>(unsigned int n) const
{
	bigint out(*this);

	if (n >= out.str.size())
		out.str = "0";
	else
		out.str.erase(out.str.size() - n, n);

	normalize(out.str);
	return out;
}

bigint &bigint::operator>>=(unsigned int n)
{
	*this = *this >> n;
	return *this;
}

bigint bigint::operator>>(const bigint &other) const
{
	return *this >> stringToUInt(other.str);
}

bigint &bigint::operator>>=(const bigint &other)
{
	*this = *this >> stringToUInt(other.str);
	return *this;
}


bool bigint::operator==(const bigint &other) const
{
	return str == other.str;
}

bool bigint::operator!=(const bigint &other) const
{
	return !(*this == other);
}

bool bigint::operator<(const bigint &other) const
{
	if (str.size() != other.str.size())
		return str.size() < other.str.size();
	return str < other.str;
}

bool bigint::operator>(const bigint &other) const
{
	return (!(*this < other) && !(*this == other));
}

bool bigint::operator<=(const bigint &other) const
{
	return (*this < other || *this == other);
}

bool bigint::operator>=(const bigint &other) const
{
	return (*this > other || *this == other);
}


std::ostream &operator<<(std::ostream &os, const bigint &n)
{
	os << n.getStr();
	return os;
}
