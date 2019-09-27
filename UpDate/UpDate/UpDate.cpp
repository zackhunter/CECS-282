#include <iostream>
#include "UpDate.h"
#include <string>
using namespace std;
UpDate::UpDate()
{
	dptr = new int[3];
	dptr[0] = 5;
	dptr[1] = 11;
	dptr[2] = 1959;
	count++;
}
UpDate::UpDate(int M, int D, int Y)
{
	dptr = new int[3];
	dptr[0] = M;	
	dptr[1] = D;	
	dptr[2] = Y;	
	int julian = Greg2Julian(dptr[0],dptr[1],dptr[2]);
	Julian2Greg(julian, dptr[0], dptr[1], dptr[2]);
	if (D != dptr[1] || M != dptr[0] || Y != dptr[2])
	{
		dptr[0] = 5;
		dptr[1] = 11;
		dptr[2] = 1959;
	}
	count++;
}
UpDate::UpDate(const UpDate& u)
{
	dptr = new int[3];
	dptr[0] = u.dptr[0];
	dptr[1] = u.dptr[1];
	dptr[2] = u.dptr[2];
	count++;
}
int UpDate::count = 0;
UpDate::~UpDate()
{
	delete[]dptr;
	count--;
	//dptr = NULL;
}

int UpDate::getMonth()
{
	return dptr[0];
}
int UpDate::getDay()
{
	return dptr[1];
}
int UpDate::getYear()
{
	return dptr[2];
}
int UpDate::GetDateCount()
{
	return count;
}
void UpDate::setDate(int M, int D, int Y)
{
	dptr[0] = M;
	dptr[1] = D;
	dptr[2] = Y;
}
string UpDate::getMonthName() {
	string sMonth;
	int iMonth = dptr[0];
	if (iMonth == 1)
		sMonth = "Jaunuary";
	else if (iMonth == 2)
		sMonth = "February";
	else if (iMonth == 3)
		sMonth = "March";
	else if (iMonth == 4)
		sMonth = "April";
	else if (iMonth == 5)
		sMonth = "May";
	else if (iMonth == 6)
		sMonth = "June";
	else if (iMonth == 7)
		sMonth = "July";
	else if (iMonth == 8)
		sMonth = "August";
	else if (iMonth == 9)
		sMonth = "September";
	else if (iMonth == 10)
		sMonth = "October";
	else if (iMonth == 11)
		sMonth = "November";
	else if (iMonth == 12)
		sMonth = "December";
	return sMonth;
}
UpDate UpDate::operator++()
{
	incrDate(1);
	return *this;
}
UpDate UpDate::operator++(int x)
{
	UpDate temp(*this);
	incrDate(1);
	return temp;
}

ostream &operator<<(ostream &out, const UpDate &D)
{
	out << D.dptr[0] << '/' << D.dptr[1] << '/' << D.dptr[2];
	return out;
}
bool UpDate::operator==(UpDate D) 
{
	return Greg2Julian(dptr[0], dptr[1], dptr[2]) == Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]);
}
int UpDate::operator-(UpDate D) 
{
	return Greg2Julian(dptr[0], dptr[1], dptr[2]) - Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]);
}
UpDate UpDate::operator--(int x)
{
	UpDate temp(*this);
	decrDate(1);
	return temp;
}

// --today
UpDate UpDate::operator--() 
{
	decrDate(1);
	return (*this);
}

// a = today + n
UpDate UpDate::operator+ (int x) 
{
	UpDate temp(*this);
	temp.incrDate(x);
	return temp;
}

// a = today - n
UpDate UpDate::operator-(int x)
{
	UpDate temp(*this);
	temp.decrDate(x);
	return temp;
}

// a = n + today
UpDate operator+ (int n, UpDate D) 
{
	return D + n;
}

bool UpDate::operator<(UpDate D) 
{
	return Greg2Julian(dptr[0], dptr[1], dptr[2]) < Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]);
}

bool UpDate::operator>(UpDate D) 
{
	return Greg2Julian(dptr[0], dptr[1], dptr[2]) > Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]);

}
UpDate UpDate::operator=(const UpDate &D) 
{
	dptr = new int[3];
	dptr[0] = D.dptr[0];
	dptr[1] = D.dptr[1];
	dptr[2] = D.dptr[2];
	return *this;
}
void UpDate::incrDate(int x)
{
	int y = Greg2Julian(dptr[0], dptr[1], dptr[2]);
	if (x < 0)
	{
		x = -x;
	}
	y += x;
	int a, b, c;
	Julian2Greg(y, a, b, c);
	dptr[0] = a;
	dptr[1] = b;
	dptr[2] = c;
}
void UpDate::decrDate(int x)
{
	int y = Greg2Julian(dptr[0],dptr[1],dptr[2]);
	if (x < 0)
	{
		x = -x;
	}
	y -= x;
	int a, b, c;
	Julian2Greg(y, a, b, c);
	dptr[0] = a;
	dptr[1] = b;
	dptr[2] = c;
}
int UpDate::Greg2Julian(int month, int day, int year)
{
	int j = day - 32075 + 1461 * (year + 4800 + (month - 14) / 12) / 4 + 367 * (month - 2 - (month - 14) / 12 * 12) / 12
		- 3 * ((year + 4900 + (month - 14) / 12) / 100) / 4;
	return j;
}
void UpDate::Julian2Greg(int JD, int &month, int &day, int &year)
{
	int y, m, d;
	int L, N;

	L = JD + 68569;
	N = 4 * L / 146097;
	L = L - (146097 * N + 3) / 4;
	y = 4000 * (L + 1) / 1461001;
	L = L - 1461 * y / 4 + 31;
	m = 80 * L / 2447;
	d = L - 2447 * m / 80;
	L = m / 11;
	m = m + 2 - 12 * L;
	y = 100 * (N - 49) + y + L;
	year = y;
	month = m;
	day = d;
}
int UpDate::julian() {
	return Greg2Julian(dptr[0], dptr[1], dptr[2]);
}

