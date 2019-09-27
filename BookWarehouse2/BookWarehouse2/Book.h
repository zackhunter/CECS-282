#ifndef Book_H_
#define Book_H_
#include <iostream>
#include <string>

using namespace std;

class Book {

public:
	static const int MAX_AUTHORS = 20;
	Book();
	~Book();
	// some useful operations. string getISBN() const; string
	string getISBN() const;
	string getTitle();
	short getYear() const;
	string getAuthors();
	short getAuthorCount();
	string getPublisher();
	bool hardCover();
	float getPrice();
	long getCopies();
	bool operator == (const Book&) const;
	Book operator= (const Book&);
	bool operator > (const Book&) const;

	friend istream& operator >> (istream&, Book&);
	friend ostream& operator << (ostream&, const Book&);
	/*
	** Other user defined member functions.
	*/
private:
	string title_;
	string authors_[Book::MAX_AUTHORS];
	short authorCount_;
	string publisher_;
	short yearPublish_;
	bool hardCover_;
	float price_;
	string isbn_;
	long copies_;
};
#endif