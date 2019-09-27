#include <iostream>
#include <string>
#include "Book.h"
using namespace std;

Book::Book(): authors_(), authorCount_(), yearPublish_(), hardCover_(), price_(), copies_() {}

Book::~Book()
{

}
bool Book::operator == (const Book&b) const
{
	return (isbn_ == b.getISBN());
}
Book Book::operator= (const Book& b)
{
	title_ = b.title_;
	authors_[Book::MAX_AUTHORS] = b.authors_[Book::MAX_AUTHORS];
	publisher_ = b.publisher_;
	yearPublish_ = b.yearPublish_;
	price_ = b.price_;
	isbn_ = b.isbn_;
	copies_ = b.copies_;
	return *this;
}
//still trying to figure out which items i actually compare
//i just copied and pasted shit from == over but pretty sure i shouldn't
//do that
bool Book::operator > (const Book&b) const
{

	return isbn_.compare(b.isbn_) > 0;
}
ostream &operator<<(ostream& out, const Book& B)
{
	//authors_[0] = "";
	out << "Title: " << B.title_ << endl;
	for (int i = 0; i < B.authorCount_; i++)
	{
		out << "Author: " << B.authors_[i] << endl;
	}
	out << "Publisher: " << B.publisher_ << endl;
	out << "Year: " << B.yearPublish_ << endl;
	if (B.hardCover_)
	{
		out << "Cover: Hardcover" << endl;
	}
	else {
		out << "Cover: Paperback" << endl;
	}
	out << "Price: " << B.price_ << endl;
	out << "ISBN: " << B.isbn_ << endl;
	out << "Copies: " << B.copies_ << endl;
	return out;
}
istream &operator >>(istream& in, Book& b)
{
	getline(in, b.title_);
	in >> b.authorCount_;
	//string s;
	//getline(in, s);
	//b.authorCount_ = stoi(s);
	in.ignore();
	for (int i = 0; i < b.authorCount_; i++) {
		getline(in, b.authors_[i]);
	}
	getline(in, b.publisher_);
	in >> b.yearPublish_;
	in >> b.hardCover_;
	in >> b.price_;
	in >> b.isbn_;
	in >> b.copies_;
	in.ignore();
	return in;
} /* ** Other user defined member functions. */
string Book::getISBN()  const {
	return isbn_;
}
string Book::getTitle()
{
	return title_;
}
short Book::getYear() const {
	return yearPublish_;
}
string Book::getAuthors() {
	return authors_[Book::MAX_AUTHORS];
}
short Book::getAuthorCount() {
	return authorCount_;
}
string Book::getPublisher()
{
	return publisher_;
}
bool Book::hardCover() {
	return hardCover_;
}
float Book::getPrice() {
	return price_;
}
long Book::getCopies() {
	return copies_;
}