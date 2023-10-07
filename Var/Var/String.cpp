#include <iostream>
#include "String.h"
#include "Consts.h"
using namespace std;

size_t String::CountStr = 0;

String::String() {
	str = new char[STRSIZE];
	CountStr++;
}

String::String(size_t size) {
	str = new char[size];
	CountStr++;
}

String::String(const char* str) {
	this->str = _strdup(str);
	CountStr++;
}

String::String(const String& OtherString) {
	if (OtherString.str) {
		str = _strdup(OtherString.str);
		CountStr++;
	}
}

String::~String() {
	delete[] str;
	CountStr--;
}

void String::SetStr(char* str) {
	delete[] this->str;
	this->str = _strdup(str);
}

char* String::GetStr() {
	return str;
}

size_t String::GetCountStr() {
	return CountStr;
}

void String::EnterStr() {
	cout << "Enter str: ";
	cin.getline(str, strlen(str));
}

void String::Show() const {
	cout << str << endl;
}

String& String::operator=(const String& OtherString) noexcept {
	if (this != &OtherString) {
		delete[] str;
		str = _strdup(OtherString.str);
	}
	return *this;
}

String String::operator+(const String& OtherString) noexcept {
	String result(strlen(str) + strlen(OtherString.str) + 1);
	int i = 0;
	for (; i < strlen(str); i++) 
		result.GetStr()[i] = str[i];
	for (int j = 0; j < strlen(OtherString.str); i++, j++)
		result.GetStr()[i] = OtherString.str[j];
	result.GetStr()[i] = '\0';
	return result;
}
String String::operator-(const String& OtherString) noexcept {
	String result(strlen(str) + strlen(OtherString.str) + 1);
	int i = 0;
	for (; i < strlen(str); i++)
		result.GetStr()[i] = str[i];
	for (int j = 0; j < strlen(OtherString.str); i++, j++)
		result.GetStr()[i] = OtherString.str[j];
	result.GetStr()[i] = '\0';
	return result;
}
String String::operator*(const String& OtherString) noexcept {
	String result;
	int n = 0;
	for (int i = 0; i < (strlen(str) <= strlen(OtherString.str) ? strlen(str) : strlen(OtherString.str)); i++) {
		for (int j = 0; j < (strlen(str) > strlen(OtherString.str) ? strlen(str) : strlen(OtherString.str)); j++) {
			if (str[i] == OtherString.str[j]) {
				result.str[n++] = str[i];
				break;
			}
		}
	}
	result.str[n] = '\0';
	return result;
}
String String::operator/(const String& OtherString) noexcept {
	String result;
	int n = 0;
	bool perevirka;
	for (int i = 0; i < strlen(str); i++) {
		perevirka = true;
		for (int j = 0; j <  strlen(OtherString.str); j++) {
			if (str[i] == OtherString.str[j]) {
				perevirka = false;
				break;
			}
		}
		if(perevirka)
			result.str[n++] = str[i];
	}
	result.str[n] = '\0';
	return result;
}

String& String::operator+=(const String& OtherString) noexcept {
	String result(strlen(str) + strlen(OtherString.str) + 1);
	int i = 0;
	for (; i < strlen(str); i++)
		result.GetStr()[i] = str[i];
	for (int j = 0; j < strlen(OtherString.str); i++, j++)
		result.GetStr()[i] = OtherString.str[j];
	result.GetStr()[i] = '\0';
	SetStr(result.GetStr());
	return *this;
}
String& String::operator-=(const String& OtherString) noexcept {
	String result(strlen(str) + strlen(OtherString.str) + 1);
	int i = 0;
	for (; i < strlen(str); i++)
		result.GetStr()[i] = str[i];
	for (int j = 0; j < strlen(OtherString.str); i++, j++)
		result.GetStr()[i] = OtherString.str[j];
	result.GetStr()[i] = '\0';
	SetStr(result.GetStr());
	return *this;
}
String& String::operator*=(const String& OtherString) noexcept {
	String result;
	int n = 0;
	for (int i = 0; i < (strlen(str) <= strlen(OtherString.str) ? strlen(str) : strlen(OtherString.str)); i++) {
		for (int j = 0; j < (strlen(str) > strlen(OtherString.str) ? strlen(str) : strlen(OtherString.str)); j++) {
			if (str[i] == OtherString.str[j]) {
				result.str[n++] = str[i];
				break;
			}
		}
	}
	result.str[n] = '\0';
	SetStr(result.GetStr());
	return *this;
}
String& String::operator/=(const String& OtherString) noexcept {
	String result;
	int n = 0;
	for (int i = 0; i < strlen(str); i++) {
		for (int j = 0; j < strlen(OtherString.str); j++) {
			if (str[i] != OtherString.str[j]) {
				result.str[n++] = str[i];
				break;
			}
			else
				break;
		}
	}
	result.str[n] = '\0';
	SetStr(result.GetStr());
	return *this;
}

bool String::operator==(const String& OtherString) noexcept {
	return strcmp(str, OtherString.str) == 0?true:false;
}
bool String::operator!=(const String& OtherString) noexcept {
	return strcmp(str, OtherString.str) != 0?true:false;
}
bool String::operator>(const String& OtherString) noexcept {
	return strcmp(str, OtherString.str) == 1?true:false;
}
bool String::operator<(const String& OtherString) noexcept {
	return strcmp(str, OtherString.str) == -1?true:false;
}
bool String::operator>=(const String& OtherString) noexcept {
	return strcmp(str, OtherString.str) >= 0?true:false;
}
bool String::operator<=(const String& OtherString) noexcept {
	return strcmp(str, OtherString.str) <= 0?true:false;
}

