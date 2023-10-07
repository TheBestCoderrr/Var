#include <iostream>
#include "String.h"
#include  "Var.h"
#include "Consts.h"

using namespace std;

int main() {
	Var a = 10, b = 120, c;
	c = b + a;
	c.Show();

	Var str1 = "Microsoft", str2 = "Windows";
	c = str1 * str2;
	c.Show();
	
	c = str1 / str2;
	c.Show();
}