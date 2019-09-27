//Zack Hunter
//CECS 282-05
//Project 4 - Overloading Operators
//Nov 11, 2017
#include <iostream>
using namespace std;
#ifndef _UpDate
#define _UpDate
class UpDate
{
private:
	int *dptr;
	static int count;
public:
	UpDate();
	UpDate(int,int,int);
	UpDate(const UpDate& u);
	~UpDate();
	void setDate(int M, int D, int Y);
	int getMonth();
	int getDay();
	int getYear();
	string getMonthName();
	static int GetDateCount();
	UpDate operator++(int);
	int julian();
	UpDate operator++();
	friend ostream &operator<<(ostream&, const UpDate&);
	bool operator<(UpDate);
	bool operator>(UpDate);
	bool operator==(UpDate);
	UpDate operator=(const UpDate &);
	UpDate operator+ (int);
	friend UpDate operator+ (int, UpDate);
	UpDate operator--();
	UpDate operator--(int);
	UpDate operator-(int);
	int operator-(UpDate);
	void incrDate(int);
	void decrDate(int);
	int Greg2Julian(int month, int day, int year);
	void Julian2Greg(int JD, int &month, int &day, int &year);
};
#endif