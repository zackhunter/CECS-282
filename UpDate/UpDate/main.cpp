// testUpDate.cpp
// Author: Steven H Gold
// Program #4 due date: 11/7/2017
// 
//

#include "UpDate.h"
#include <iostream>
using namespace std;

int main()
{
	UpDate Bday;
	UpDate duedate(11, 7, 2017);
	UpDate today(duedate);


	cout << endl;
	cout << "Today is " << today << endl;
	cout << "This program is due on " << duedate;
	cout << endl;

	cout << "(3)Right now there are " << UpDate::GetDateCount() << " UpDate objects\n";
	{
		UpDate d1, d2, d3;
		cout << "(6)Inside this block there are " << UpDate::GetDateCount() << " UpDate objects\n";
	}
	cout << "(3)Outside the block there are " << UpDate::GetDateCount() << " UpDate objects\n";

	UpDate dtemp(duedate);
	dtemp++;
	cout << "If you turn this assignment in on " << dtemp << " then is will be late.\n";
	cout << "It is due on " << --dtemp << " so don't be late.\n";
	cout << "One week from due date is " << duedate + 7 << endl;
	cout << "One week from due date is " << 7 + duedate << endl;
	cout << "One week earlier from due date is " << duedate - 7 << endl;

	cout << "Your professor was born on " << Bday << " : ";
	cout << "Master Goldis " << duedate - Bday << " days old today\n";

	cout << "Today is Julian date " << duedate.julian() << endl;;
	cout << "Tomorrrow is Julian date " << (++duedate).julian() << endl;;

	cout << "The very first Julian date was " << UpDate(11, 7, 2017) - UpDate(11, 7, 2017).julian() << endl;

	cout << "The very first Julian date was " << today - today.julian() << endl;


	UpDate yesterday, tomorrow;
	yesterday = today - 1;
	tomorrow = 1 + today;

	cout << "Yesterday was " << yesterday << endl;
	cout << "Today is " << today << endl;
	cout << "Tomorrow is " << tomorrow << endl;

	cout << "Today is ";
	cout << ((today>tomorrow) ? "greater than" : "not greater than");
	cout << " than tomorrow\n";

	cout << "Today is ";
	cout << ((today<tomorrow) ? "less than" : "not less than");
	cout << " than tomorrow\n";

	cout << "Today is ";
	cout << ((today == tomorrow) ? "equal to" : "not equal to");
	cout << " tomorrow\n";


	UpDate fallBreak(11, 20, 2017);

	cout << "Fall Break is on " << fallBreak << endl;
	fallBreak.~UpDate(); // deleting Fall Break


						 // consider what is happening in the line below
						 // you are using a variable that was destructed....
						 // what do you expect to happen????
	cout << "Fall Break is cancelled: " << fallBreak << endl;


	int dummy;
	cin >> dummy;
	return 0;
}



