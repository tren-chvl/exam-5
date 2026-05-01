#ifndef BIGINT
#define BIGINT

#include <string>
#include <iostream>
#include <sstream>

class bigint
{
	private:
		std::string str;
	public:
		bigint();
		bigint(unsigned int n);
		bigint(const bigint &source);
		std::string getStr() const;

		bigint &operator=(const bigint &source);
		bigint &operator+=(const bigint &other);
		bigint &operator++();
		bigint &operator<<=(const bigint &other);
		bigint &operator>>=(const bigint &other);
		bigint &operator<<=(unsigned int n);
		bigint &operator>>=(unsigned int n);

		bigint operator++(int);
		bigint operator+(const bigint &other) const;
		bigint operator<<(unsigned int n) const;
		bigint operator>>(unsigned int n) const;
		bigint operator<<(const bigint &other) const;
		bigint operator>>(const bigint &other) const;
		
		bool operator==(const bigint &other) const;
		bool operator!=(const bigint &other) const;
		bool operator>(const bigint &other) const;
		bool operator<(const bigint &other) const;
		bool operator<=(const bigint &other) const;
		bool operator>=(const bigint &other) const;
		
};

std::ostream& operator<<(std::ostream &output, const bigint &obj);

#endif








// #ifndef BIGINT_HPP
// #define BIGINT_HPP


// #include <string>
// #include <iostream>

// class bigint
// {
// 	private:
// 		std::string str;
// 	public:
// 		bigint();
// 		bigint(unsigned int n);
// 		bigint(const bigint &other);
// 		std::string getStr() const;

// 		bigint &operator+=(const bigint &other);
// 		bigint &operator=(const bigint &other);
// 		bigint &operator++();
// 		bigint &operator<<=(unsigned int n);
// 		bigint &operator<<=(const bigint &&other);
// 		bigint &operator>>=(unsigned int n);
// 		bigint &operator>>=(const bigint &other);

// 		bigint operator+(const bigint &other) const;
// 		bigint operator++(int);
// 		bigint operator<<(unsigned int n) const;
// 		bigint operator<<(const bigint &other) const;
// 		bigint operator>>(unsigned int n) const;
// 		bigint operator>>(const bigint &other) const;

// 		bool operator!=(const bigint &other) const;
// 		bool operator==(const bigint &other) const;
// 		bool operator>=(const bigint &other) const;
// 		bool operator<=(const bigint &other) const;
// 		bool operator<(const bigint &other) const;
// 		bool operator>(const bigint &other) const;
// };

// std::ostream &operator<<(std::ostream &os, const bigint &n);

// #endif