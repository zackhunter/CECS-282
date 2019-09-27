#include <iostream>
#include <string>
#include "Book.h"
using namespace std;

class Warehouse {

public:
	friend istream& operator >> (istream&, Warehouse&);
	friend ostream& operator << (ostream&, const Warehouse&);
	static const long MAX_BOOKS = 512;
	Warehouse();
	~Warehouse();
	// Method to find a book from the list.
	// return false if not found. If the input ISBN is found,
	// the Book object is copied to the input book reference.
	bool find(string isbn, Book& book) const;
	/*
	** Extra Credit
	** Method to find a list of books published on a specific year.
	** return the number of matches and the list of books found.
	*/
	int find(short year, Book books[]) const;
	/*
	** Other user defined methods.
	*/
	void sort();
	int getBookCount();
private:
	// Method to sort the list of books.
	void sort_();
private:
	Book books_[MAX_BOOKS];
	long bookCount_;

};