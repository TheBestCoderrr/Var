#pragma once
#include "String.h"

class Var
{
private:
	String string;
	double fnum;
	int inum;
public:
	Var();
	Var(const int num);
	Var(const double num);
	Var(const char* str);
	Var(const String string);

	void SetString(String string);
	String GetString();
	void Setfnum(double num);
	double Getfnum();
	void Setinum(int num);
	int Getinum();

	Var& operator=(const Var& R) noexcept;
	Var& operator=(const int num) noexcept;
	Var& operator=(const double num) noexcept;
	Var& operator=(const String str) noexcept;
	Var& operator=(const char* str) noexcept;

	Var operator+(Var& R);
	Var operator+(const int num);
	Var operator+(const double num);
	Var operator+(String str);
	Var operator+(const char* str);
	
	Var operator-(Var& R);
	Var operator-(const int num);
	Var operator-(const double num);
	Var operator-(String str);
	Var operator-(const char* str);
	
	Var operator*(Var& R);
	Var operator*(const int num);
	Var operator*(const double num);
	Var operator*(String str);
	Var operator*(const char* str);
	
	Var operator/(Var& R);
	Var operator/(const int num);
	Var operator/(const double num);
	Var operator/(String str);
	Var operator/(const char* str);

	Var& operator+=(const int num);
	Var& operator+=(Var& R);
	Var& operator+=(const double num);
	Var& operator+=(String str);
	Var& operator+=(const char* str);
	
	Var& operator-=(const int num);
	Var& operator-=(Var& R);
	Var& operator-=(const double num);
	Var& operator-=(String str);
	Var& operator-=(const char* str);
	
	Var& operator*=(const int num);
	Var& operator*=(Var& R);
	Var& operator*=(const double num);
	Var& operator*=(String str);
	Var& operator*=(const char* str);
	
	Var& operator/=(const int num);
	Var& operator/=(Var& R);
	Var& operator/=(const double num);
	Var& operator/=(String str);
	Var& operator/=(const char* str);

	bool operator==(Var& R);
	bool operator==(const int num);
	bool operator==(const double num);
	bool operator==(String str);
	bool operator==(const char* str);
	
	bool operator!=(Var& R);
	bool operator!=(const int num);
	bool operator!=(const double num);
	bool operator!=(String str);
	bool operator!=(const char* str);
	
	bool operator>(Var& R);
	bool operator>(const int num);
	bool operator>(const double num);
	bool operator>(String str);
	bool operator>(const char* str);
	
	bool operator<(Var& R);
	bool operator<(const int num);
	bool operator<(const double num);
	bool operator<(String str);
	bool operator<(const char* str);

	bool operator>=(Var& R);
	bool operator>=(const int num);
	bool operator>=(const double num);
	bool operator>=(String str);
	bool operator>=(const char* str);

	bool operator<=(Var& R);
	bool operator<=(const int num);
	bool operator<=(const double num);
	bool operator<=(String str);
	bool operator<=(const char* str);

	explicit operator double();
	explicit operator int();
	explicit operator char*();
	explicit operator String();

	void Show();
};

