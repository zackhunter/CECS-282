#include <iostream>
#include <fstream>
#include "Book.h"
#include "Warehouse.h"

int main()
{
	Warehouse hold;
	ifstream input;
	input.open("book.dat");
	cout << "---------------------- Sorted Inventory List by ISBN ---------------------" << endl;
	input >> hold;
	cout << " " + hold.getBookCount();
	//hold.sort();
	cout << hold;
	input.close();
	ifstream inputFile;
	inputFile.open("search.dat");
	Book b;
	//cout << hold.getBookCount();
	//string arrayOfFiles[3];
	
	/*
	for (int i = 0; i < hold.getBookCount(); i++)
	{
		cout << i;
		inputFile >> arrayOfFiles[i];
	}
	*/		

	
	inputFile.close();
	//cout << hold.getBookCount();
	/*
	for (int i = 0; i < hold.getBookCount(); i++) {
		bool idk = hold.find(arrayOfFiles[i], b);
		if (idk) {
			cout << arrayOfFiles[i];
		}
		else
			cout << "File not found";
	}
	*/
	//cout << hold;
	//cout << hold.getBookCount();
	getchar();
	return 0;
};