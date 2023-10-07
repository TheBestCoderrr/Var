#include <iostream>
#include "Var.h"
using namespace std;

Var::Var() { 
	inum = 0; 
	fnum = 0;
	string = nullptr;
}
Var::Var(const int num) { inum = num; }
Var::Var(const double num) { fnum = num; }
Var::Var(const char* str) { string = _strdup(str); }
Var::Var(const String string) { this->string = string; }

void Var::SetString(String string) { this->string = string;  }
String Var::GetString() { return string;  }
void Var::Setfnum(double num) { fnum = num;  }
double Var::Getfnum() { return fnum; }
void Var::Setinum(int num) { inum = num; }
int Var::Getinum() { return inum; }

Var::operator double() { 
	if(fnum) return fnum; 
	else {
		if (inum) {
			fnum = inum;
			inum = 0;
		}
		else {
			fnum = atof(string.GetStr());
			string = nullptr;
		}
		return fnum;
	}
}
Var::operator int() { 
	if (inum) return inum;
	else {
		if (fnum) {
			inum = fnum;
			fnum = 0;
		}
		else {
			inum = atoi(string.GetStr());
			string = nullptr;
		}
		return inum;
	}
}
Var::operator char*()  {
	if (string.GetStr()) return string.GetStr();
	else {
		if (inum) {
			snprintf(string.GetStr(), sizeof(string.GetStr()), "%d", inum);
			inum = 0;
		}
		else {
			snprintf(string.GetStr(), sizeof(string.GetStr()), "%lf", fnum);
			fnum = 0;
		}
		return string.GetStr();
	}
}
Var::operator String() {
	if (string.GetStr()) return string;
	else {
		if (inum) {
			snprintf(string.GetStr(), sizeof(string.GetStr()), "%d", inum);
			inum = 0;
		}
		else {
			snprintf(string.GetStr(), sizeof(string.GetStr()), "%lf", fnum);
			fnum = 0;
		}
		return string;
	}
}

Var& Var::operator=(const Var& R)noexcept {
	fnum = R.fnum;
	inum = R.inum;
	string = R.string;
	return *this;
}
Var& Var::operator=(const int num) noexcept {
	inum = num;
	fnum = 0;
	string = nullptr;
	return *this;
}
Var& Var::operator=(const double num) noexcept {
	fnum = num;
	inum = 0;
	string = nullptr;
	return *this;
}
Var& Var::operator=(const String str) noexcept {
	string = str;
	fnum = 0;
	inum = 0;
	return *this;
}
Var& Var::operator=(const char* str) noexcept {
	delete[] string.GetStr();
	string = _strdup(str);
	fnum = 0;
	inum = 0;
	return *this;
}

Var Var::operator+(Var& R) {
	Var result;
	if (inum) {
		if(R.inum)
			result.Setinum(inum + R.inum);
		else if(R.fnum)
			result.Setinum(inum + R.fnum);
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			result.Setinum(inum + num);
		}
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		if (R.inum)
			result.Setinum(fnum + R.inum);
		else if (R.fnum)
			result.Setinum(fnum + R.fnum);
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			result.Setinum(fnum + num);
		}
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			result.SetString(string + R.string);
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				result.SetString(string + strnum);
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				result.SetString(string + strnum);
			}
		}
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator+(const int num) { 
	Var result;
	if (inum) {
		result.Setinum(inum + num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		result.Setfnum(fnum + num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		result.SetString(string + strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator+(const double num) { 
	Var result;
	if (inum) {
		result.Setinum(inum + num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		result.Setfnum(fnum + num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		result.SetString(string + strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator+(const char* str){
	Var result;
	if (inum) {
		int num = atoi(str);
		result.Setinum(inum + num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		double num = atof(str);
		result.Setfnum(fnum + num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%s", str);
		result.SetString(string + strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator+(String str) {
	Var result;
	if (inum) {
		int num = atoi(str.GetStr());
		result.Setinum(inum + num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		result.Setfnum(fnum + num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%s", str.GetStr());
		result.SetString(string + strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}

Var Var::operator-(Var& R) {
	Var result;
	if (inum) {
		if (R.inum)
			result.Setinum(inum - R.inum);
		else if (R.fnum)
			result.Setinum(inum - R.fnum);
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			result.Setinum(inum - num);
		}
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		if (R.inum)
			result.Setinum(fnum - R.inum);
		else if (R.fnum)
			result.Setinum(fnum - R.fnum);
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			result.Setinum(fnum - num);
		}
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			result.SetString(string - R.string);
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				result.SetString(string - strnum);
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				result.SetString(string - strnum);
			}
		}
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator-(const int num) {
	Var result;
	if (inum) {
		result.Setinum(inum - num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		result.Setfnum(fnum - num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		result.SetString(string - strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator-(const double num) {
	Var result;
	if (inum) {
		result.Setinum(inum - num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		result.Setfnum(fnum - num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		result.SetString(string - strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator-(const char* str) {
	Var result;
	if (inum) {
		int num = atoi(str);
		result.Setinum(inum - num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		double num = atof(str);
		result.Setfnum(fnum - num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%s", str);
		result.SetString(string - strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator-(String str) {
	Var result;
	if (inum) {
		int num = atoi(str.GetStr());
		result.Setinum(inum - num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		result.Setfnum(fnum - num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%s", str.GetStr());
		result.SetString(string - strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}

Var Var::operator*(Var& R) {
	Var result;
	if (inum) {
		if (R.inum)
			result.Setinum(inum * R.inum);
		else if (R.fnum)
			result.Setinum(inum * R.fnum);
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			result.Setinum(inum * num);
		}
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		if (R.inum)
			result.Setinum(fnum * R.inum);
		else if (R.fnum)
			result.Setinum(fnum * R.fnum);
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			result.Setinum(fnum * num);
		}
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			result.SetString(string * R.string);
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				result.SetString(string * strnum);
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				result.SetString(string * strnum);
			}
		}
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator*(const int num) {
	Var result;
	if (inum) {
		result.Setinum(inum * num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		result.Setfnum(fnum * num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		result.SetString(string * strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator*(const double num) {
	Var result;
	if (inum) {
		result.Setinum(inum * num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		result.Setfnum(fnum * num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		result.SetString(string * strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator*(const char* str) {
	Var result;
	if (inum) {
		int num = atoi(str);
		result.Setinum(inum * num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		double num = atof(str);
		result.Setfnum(fnum * num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%s", str);
		result.SetString(string * strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator*(String str) {
	Var result;
	if (inum) {
		int num = atoi(str.GetStr());
		result.Setinum(inum * num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		result.Setfnum(fnum * num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%s", str.GetStr());
		result.SetString(string * strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}

Var Var::operator/(Var& R) {
	Var result;
	if (inum) {
		if (R.inum)
			result.Setinum(inum / R.inum);
		else if (R.fnum)
			result.Setinum(inum / R.fnum);
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			result.Setinum(fnum / num);
		}
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		if (R.inum)
			result.Setinum(fnum / R.inum);
		else if (R.fnum)
			result.Setinum(fnum / R.fnum);
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			result.Setinum(inum / num);
		}
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			result.SetString(string / R.string);
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				result.SetString(string / strnum);
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				result.SetString(string / strnum);
			}
		}
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator/(const int num) {
	Var result;
	if (inum) {
		result.Setinum(inum / num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		result.Setfnum(fnum / num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		result.SetString(string / strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator/(const double num) {
	Var result;
	if (inum) {
		result.Setinum(inum / num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		result.Setfnum(fnum / num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		result.SetString(string / strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator/(const char* str) {
	Var result;
	if (inum) {
		int num = atoi(str);
		result.Setinum(inum / num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		double num = atof(str);
		result.Setfnum(fnum / num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%s", str);
		result.SetString(string / strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}
Var Var::operator/(String str) {
	Var result;
	if (inum) {
		int num = atoi(str.GetStr());
		result.Setinum(inum / num);
		result.Setfnum(0);
		result.SetString(nullptr);
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		result.Setfnum(fnum / num);
		result.Setinum(0);
		result.SetString(nullptr);
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%s", str.GetStr());
		result.SetString(string / strnum);
		result.Setinum(0);
		result.Setfnum(0);
	}
	return result;
}

Var& Var::operator+=(Var& R) {
	if (inum) {
		if (R.inum)
			inum += R.inum;
		else if (R.fnum)
			inum += R.fnum;
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			inum += num;
		}
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		if (R.inum)
			fnum += R.inum;
		else if (R.fnum)
			fnum += R.fnum;
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			fnum += num;
		}
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			string += R.string;
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				string += strnum;
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				string += strnum;
			}
		}
		inum = 0;
		fnum = 0;
	}
	return *this;
}
Var& Var::operator+=(const int num) {
	if (inum) {
		inum += num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		fnum += num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		string += strnum;
		fnum = 0;
		inum = 0;
	}
	return *this;
}
Var& Var::operator+=(const double num) {
	if (inum) {
		inum += num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		fnum += num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		string += strnum;
		fnum = 0;
		inum = 0;
	}
	return *this;
}
Var& Var::operator+=(const char* str) {
	if (inum) {
		int num = atoi(str);
		inum += num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		double num = atof(str);
		fnum += num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		string += str;
		inum = 0;
		fnum = 0;
	}
	return *this;
}
Var& Var::operator+=(String str) {
	if (inum) {
		int num = atoi(str.GetStr());
		inum += num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		fnum += num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		string += str;
		inum = 0;
		fnum = 0;
	}
	return *this;
}

Var& Var::operator-=(Var& R) {
	if (inum) {
		if (R.inum)
			inum -= R.inum;
		else if (R.fnum)
			inum -= R.fnum;
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			inum -= num;
		}
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		if (R.inum)
			fnum -= R.inum;
		else if (R.fnum)
			fnum -= R.fnum;
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			fnum -= num;
		}
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			string -= R.string;
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				string -= strnum;
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				string -= strnum;
			}
		}
		inum = 0;
		fnum = 0;
	}
	return *this;
}
Var& Var::operator-=(const int num) {
	if (inum) {
		inum -= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		fnum -= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		string -= strnum;
		fnum = 0;
		inum = 0;
	}
	return *this;
}
Var& Var::operator-=(const double num) {
	if (inum) {
		inum -= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		fnum -= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		string -= strnum;
		fnum = 0;
		inum = 0;
	}
	return *this;
}
Var& Var::operator-=(const char* str) {
	if (inum) {
		int num = atoi(str);
		inum -= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		double num = atof(str);
		fnum -= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		string -= str;
		inum = 0;
		fnum = 0;
	}
	return *this;
}
Var& Var::operator-=(String str) {
	if (inum) {
		int num = atoi(str.GetStr());
		inum -= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		fnum -= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		string -= str;
		inum = 0;
		fnum = 0;
	}
	return *this;
}

Var& Var::operator*=(Var& R) {
	if (inum) {
		if (R.inum)
			inum *= R.inum;
		else if (R.fnum)
			inum *= R.fnum;
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			inum *= num;
		}
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		if (R.inum)
			fnum *= R.inum;
		else if (R.fnum)
			fnum *= R.fnum;
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			fnum *= num;
		}
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			string *= R.string;
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				string *= strnum;
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				string *= strnum;
			}
		}
		inum = 0;
		fnum = 0;
	}
	return *this;
}
Var& Var::operator*=(const int num) {
	if (inum) {
		inum *= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		fnum *= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		string *= strnum;
		fnum = 0;
		inum = 0;
	}
	return *this;
}
Var& Var::operator*=(const double num) {
	if (inum) {
		inum *= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		fnum *= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		string *= strnum;
		fnum = 0;
		inum = 0;
	}
	return *this;
}
Var& Var::operator*=(const char* str) {
	if (inum) {
		int num = atoi(str);
		inum *= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		double num = atof(str);
		fnum *= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		string *= str;
		inum = 0;
		fnum = 0;
	}
	return *this;
}
Var& Var::operator*=(String str) {
	if (inum) {
		int num = atoi(str.GetStr());
		inum *= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		fnum *= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		string *= str;
		inum = 0;
		fnum = 0;
	}
	return *this;
}

Var& Var::operator/=(Var& R) {
	if (inum) {
		if (R.inum)
			inum /= R.inum;
		else if (R.fnum)
			inum /= R.fnum;
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			inum /= num;
		}
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		if (R.inum)
			fnum /= R.inum;
		else if (R.fnum)
			fnum /= R.fnum;
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			fnum /= num;
		}
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			string /= R.string;
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				string /= strnum;
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				string /= strnum;
			}
		}
		inum = 0;
		fnum = 0;
	}
	return *this;
}
Var& Var::operator/=(const int num) {
	if (inum) {
		inum /= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		fnum *= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		string *= strnum;
		fnum = 0;
		inum = 0;
	}
	return *this;
}
Var& Var::operator/=(const double num) {
	if (inum) {
		inum *= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		fnum *= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		string /= strnum;
		fnum = 0;
		inum = 0;
	}
	return *this;
}
Var& Var::operator/=(const char* str) {
	if (inum) {
		int num = atoi(str);
		inum *= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		double num = atof(str);
		fnum *= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		string *= str;
		inum = 0;
		fnum = 0;
	}
	return *this;
}
Var& Var::operator/=(String str) {
	if (inum) {
		int num = atoi(str.GetStr());
		inum *= num;
		fnum = 0;
		string = nullptr;
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		fnum /= num;
		inum = 0;
		string = nullptr;
	}
	else if (string.GetStr()) {
		string /= str;
		inum = 0;
		fnum = 0;
	}
	return *this;
}

bool Var::operator==(Var& R) {
	if (inum) {
		if (R.inum)
			return inum == R.inum;
		else if (R.fnum)
			return inum == R.fnum;
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			return inum == num;
		}
	}
	else if (fnum) {
		if (R.inum)
			return fnum == R.inum;
		else if (R.fnum)
			return fnum == R.fnum;
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			return fnum == num;
		}
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			return string == R.string;
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				return string == strnum;
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				return string == strnum;
			}
		}
	}
}
bool Var::operator==(const int num) {
	if (inum) 
		return inum == num;
	else if (fnum) 
		return fnum == num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d",num);
		return string == strnum;
	};
}
bool Var::operator==(const double num) {
	if (inum) 
		return inum == num;
	else if (fnum) 
		return fnum == num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		return string == strnum;
	};
}
bool Var::operator==(const char* str) {
	if (inum) {
		int num = atoi(str);
		return inum == num;
	}
	else if (fnum) {
		double num = atof(str);
		return fnum == num;
	}
	else if (string.GetStr()) {
		return string == str;
	};
}
bool Var::operator==(String str) {
	if (inum) {
		int num = atoi(str.GetStr());
		return inum == num;
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		return fnum == num;
	}
	else if (string.GetStr()) {
		return string == str;
	};
}

bool Var::operator!=(Var& R) {
	if (inum) {
		if (R.inum)
			return inum != R.inum;
		else if (R.fnum)
			return inum != R.fnum;
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			return inum != num;
		}
	}
	else if (fnum) {
		if (R.inum)
			return fnum != R.inum;
		else if (R.fnum)
			return fnum != R.fnum;
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			return fnum != num;
		}
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			return string != R.string;
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				return string != strnum;
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				return string != strnum;
			}
		}
	}
}
bool Var::operator!=(const int num) {
	if (inum)
		return inum != num;
	else if (fnum)
		return fnum != num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		return string != strnum;
	};
}
bool Var::operator!=(const double num) {
	if (inum)
		return inum != num;
	else if (fnum)
		return fnum != num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		return string != strnum;
	};
}
bool Var::operator!=(const char* str) {
	if (inum) {
		int num = atoi(str);
		return inum != num;
	}
	else if (fnum) {
		double num = atof(str);
		return fnum != num;
	}
	else if (string.GetStr()) {
		return string != str;
	};
}
bool Var::operator!=(String str) {
	if (inum) {
		int num = atoi(str.GetStr());
		return inum != num;
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		return fnum != num;
	}
	else if (string.GetStr()) {
		return string != str;
	};
}

bool Var::operator>(Var& R) {
	if (inum) {
		if (R.inum)
			return inum > R.inum;
		else if (R.fnum)
			return inum > R.fnum;
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			return inum > num;
		}
	}
	else if (fnum) {
		if (R.inum)
			return fnum > R.inum;
		else if (R.fnum)
			return fnum > R.fnum;
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			return fnum > num;
		}
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			return string > R.string;
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				return string > strnum;
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				return string > strnum;
			}
		}
	}
}
bool Var::operator>(const int num) {
	if (inum)
		return inum > num;
	else if (fnum)
		return fnum > num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		return string > strnum;
	};
}
bool Var::operator>(const double num) {
	if (inum)
		return inum > num;
	else if (fnum)
		return fnum > num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		return string > strnum;
	};
}
bool Var::operator>(const char* str) {
	if (inum) {
		int num = atoi(str);
		return inum > num;
	}
	else if (fnum) {
		double num = atof(str);
		return fnum > num;
	}
	else if (string.GetStr()) {
		return string > str;
	};
}
bool Var::operator>(String str) {
	if (inum) {
		int num = atoi(str.GetStr());
		return inum > num;
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		return fnum > num;
	}
	else if (string.GetStr()) {
		return string > str;
	};
}

bool Var::operator<(Var& R) {
	if (inum) {
		if (R.inum)
			return inum < R.inum;
		else if (R.fnum)
			return inum < R.fnum;
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			return inum < num;
		}
	}
	else if (fnum) {
		if (R.inum)
			return fnum < R.inum;
		else if (R.fnum)
			return fnum < R.fnum;
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			return fnum < num;
		}
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			return string < R.string;
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				return string < strnum;
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				return string < strnum;
			}
		}
	}
}
bool Var::operator<(const int num) {
	if (inum)
		return inum < num;
	else if (fnum)
		return fnum < num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		return string < strnum;
	};
}
bool Var::operator<(const double num) {
	if (inum)
		return inum < num;
	else if (fnum)
		return fnum < num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		return string < strnum;
	};
}
bool Var::operator<(const char* str) {
	if (inum) {
		int num = atoi(str);
		return inum < num;
	}
	else if (fnum) {
		double num = atof(str);
		return fnum < num;
	}
	else if (string.GetStr()) {
		return string < str;
	};
}
bool Var::operator<(String str) {
	if (inum) {
		int num = atoi(str.GetStr());
		return inum < num;
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		return fnum < num;
	}
	else if (string.GetStr()) {
		return string < str;
	};
}

bool Var::operator>=(Var& R) {
	if (inum) {
		if (R.inum)
			return inum >= R.inum;
		else if (R.fnum)
			return inum >= R.fnum;
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			return inum >= num;
		}
	}
	else if (fnum) {
		if (R.inum)
			return fnum >= R.inum;
		else if (R.fnum)
			return fnum >= R.fnum;
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			return fnum >= num;
		}
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			return string >= R.string;
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				return string >= strnum;
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				return string >= strnum;
			}
		}
	}
}
bool Var::operator>=(const int num) {
	if (inum)
		return inum >= num;
	else if (fnum)
		return fnum >= num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		return string >= strnum;
	};
}
bool Var::operator>=(const double num) {
	if (inum)
		return inum >= num;
	else if (fnum)
		return fnum >= num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		return string >= strnum;
	};
}
bool Var::operator>=(const char* str) {
	if (inum) {
		int num = atoi(str);
		return inum >= num;
	}
	else if (fnum) {
		double num = atof(str);
		return fnum >= num;
	}
	else if (string.GetStr()) {
		return string > str;
	};
}
bool Var::operator>=(String str) {
	if (inum) {
		int num = atoi(str.GetStr());
		return inum >= num;
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		return fnum >= num;
	}
	else if (string.GetStr()) {
		return string >= str;
	};
}

bool Var::operator<=(Var& R) {
	if (inum) {
		if (R.inum)
			return inum <= R.inum;
		else if (R.fnum)
			return inum <= R.fnum;
		else if (R.string.GetStr()) {
			int num = atoi(R.string.GetStr());
			return inum <= num;
		}
	}
	else if (fnum) {
		if (R.inum)
			return fnum <= R.inum;
		else if (R.fnum)
			return fnum <= R.fnum;
		else if (R.string.GetStr()) {
			double num = atof(R.string.GetStr());
			return fnum <= num;
		}
	}
	else if (string.GetStr()) {
		if (R.string.GetStr())
			return string <= R.string;
		else {
			String strnum;
			if (R.inum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", R.inum);
				return string <= strnum;
			}
			else if (R.fnum) {
				snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", R.fnum);
				return string <= strnum;
			}
		}
	}
}
bool Var::operator<=(const int num) {
	if (inum)
		return inum <= num;
	else if (fnum)
		return fnum <= num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%d", num);
		return string <= strnum;
	};
}
bool Var::operator<=(const double num) {
	if (inum)
		return inum <= num;
	else if (fnum)
		return fnum <= num;
	else if (string.GetStr()) {
		String strnum;
		snprintf(strnum.GetStr(), sizeof(strnum.GetStr()), "%lf", num);
		return string <= strnum;
	};
}
bool Var::operator<=(const char* str) {
	if (inum) {
		int num = atoi(str);
		return inum <= num;
	}
	else if (fnum) {
		double num = atof(str);
		return fnum <= num;
	}
	else if (string.GetStr()) {
		return string <= str;
	};
}
bool Var::operator<=(String str) {
	if (inum) {
		int num = atoi(str.GetStr());
		return inum <= num;
	}
	else if (fnum) {
		double num = atof(str.GetStr());
		return fnum <= num;
	}
	else if (string.GetStr()) {
		return string <= str;
	};
}

void Var::Show() {
	if (Getinum())
		cout << Getinum() << endl;
	else if (Getfnum())
		cout << Getfnum() << endl;
	else if (GetString().GetStr())
		GetString().Show();
	else
		cout << 0;
}