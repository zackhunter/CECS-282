#include <iostream>
#include <string>
#include "Warehouse.h"
using namespace std;
//Book books_[Warehouse::MAX_BOOKS];
//long bookCount_;
Warehouse::Warehouse()
{
	//books_[MAX_BOOKS] = new Book[MAX_BOOKS];
	bookCount_ = 0;
}
Warehouse::~Warehouse()
{
	delete[]books_;
	bookCount_ = 0;
}
//long Warehouse::bookCount_ = 0;
int Warehouse::getBookCount()
{
	//cout << sizeof(books_);
	cout << bookCount_;
	return bookCount_;
}
istream& operator >> (istream& input, Warehouse& warehouse) {
	for (int i = 0; i < 4; i++) {
		input >> warehouse.books_[i];
		bookCount_++;
	}
	return input;
}
ostream & operator << (ostream& output, const Warehouse& warehouse) {
	for (int i = 0; i<bookCount_; i++)
		output << warehouse.books_[i] << endl;
	return output;
}
bool Warehouse::find(string isbn, Book& book) const
{
	for (int i = 0; i < bookCount_; i++)
	{
		if (books_[i].getISBN().compare(isbn))
		{
			book = books_[i];
			return true;
		}
	}
	return false;
}
int Warehouse::find(short year, Book books[]) const
{
	int numOfOccurances = 0;
	for (int i = 0; i < bookCount_; i++)
	{
		if (books_[i].getYear() == year)
		{
			numOfOccurances++;
		}
	}
	return numOfOccurances;
}
void Warehouse::sort_()
{
	/*
	for (int i = 0; i < 3; ++i) {
		Book hold;
		if (books_[i] > books_[i + 1]) {
			hold = books_[i + 1];
			books_[i + 1] = books_[i];
			books_[i] = hold;
			cout << books_[i];
		}
	}
	*/
	for (int i = 1; i<3; ++i)
	{
		Book temp;
		for (int j = 0; j<(3 - i); ++j)
			if (books_[i] > books_[i + 1])
			{
				temp = books_[j];
				books_[j] = books_[j + 1];
				books_[j + 1] = temp;
			}
	}
}

void Warehouse::sort()
{
	sort_();
}