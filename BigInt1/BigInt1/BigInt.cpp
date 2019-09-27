#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <exception>

using namespace std;

class BigInt
{
private:
	vector<int> storage;
public:
	BigInt();
	BigInt(int);
	BigInt(string);
	void operator++(int);
	bool operator<=(const BigInt)const;
	bool operator==(int) const;
	bool operator==(const BigInt)const;
	BigInt operator-(BigInt);
	BigInt operator-(int);
	BigInt operator+(BigInt);
	bool operator<(const BigInt &) const;
	bool operator<(int) const;
	friend ostream &operator<<(ostream &, BigInt &);
	BigInt& operator=(BigInt& c);
	BigInt stripLeadingZero();
};


BigInt GoldRabbits(BigInt bigN);
int fact(int n);
using std::overflow_error;
int main()
{
	BigInt bigX(28675), bigY("46368"), bigResult;

	bigResult = bigX + bigY;
	cout << bigX << "+" << bigY << "=" << bigResult;
	getchar(); // pause

	for (BigInt n = 0; n <= 1000; n++)
	{
		cout << (n<950 ? "\n" : "\n\n") << "The GoldRabbit of (" << n << ") is " << GoldRabbits(n);
		if (n == 30) // pause at 30
			getchar();

	}

	getchar();

	for (int i = 0; i<20; i++)
	{
		try
		{
			cout << "Fact(" << i << "):" << fact(i) << endl;
		}
		catch (overflow_error &e)
		{
			cout << "Fact(" << i << "):" << "Overflow" << endl;
		}
	}
	getchar();


	return 0;
}

int fact(int n)
{
	int a = n;

	if (n == 0)
		return 1;
	else
	{
		int b = fact(n - 1);
		int z = a * b;
		if (b != z / a) {
			throw overflow_error("notvalid");
		}
		else {
			return z;
		}
	}
}
BigInt GoldRabbits(BigInt bigN)
{
	static map<BigInt, BigInt> fMap;
	if (bigN == 0 || bigN == 1)
	{
		return BigInt(1);
	}
	if (fMap.find(bigN) != fMap.end()) 
	{
		return fMap.at(bigN);
	}
	else
	{
		BigInt a = GoldRabbits(bigN - 1);
		BigInt b = GoldRabbits(bigN - 2);
		BigInt c = a + b;
		fMap[bigN] = c;
		return c;
	}
}

BigInt::BigInt()
{
	storage.push_back(0);
}
BigInt BigInt::stripLeadingZero()
{
	BigInt temp;
	if (this->storage.size() > 1)
	{
		vector<int>::iterator it2;
		bool strip = true;
		for (it2 = this->storage.begin(); it2 != this->storage.end(); it2++)
		{
			int numb = *it2;
			if (strip)
			{
				if (numb == 0) {}
				else
				{
					strip = 0;
					temp.storage.at(0) = numb;
				}
			}
			else { temp.storage.push_back(numb); }
		}
		// std::reverse(temp.storage.begin(), temp.storage.end());

		*this = temp;

	}
	return temp;
}
BigInt::BigInt(int n)
{
	std::string num = std::to_string(n);

	if (n < 9) { storage.push_back(n); }
	else
		for (int i = 0; i < num.length(); i++)
		{
			int num0 = num.at(i) - '0';
			storage.push_back(num0);
		}
}

BigInt::BigInt(string bigS)
{
	for (int i = 0; i < bigS.length(); i++)
	{
		int num0 = bigS.at(i) - '0';
		storage.push_back(num0);
	}
}
BigInt& BigInt ::operator= (BigInt& c)
{
	if (this != &c) //test the address of both objects
	{
		vector<int>::iterator it;
		this->storage.clear();
		for (it = c.storage.begin(); it != c.storage.end(); it++)
		{
			this->storage.push_back(*it);
		}
	}
	return *this;
}

bool BigInt :: operator<(int x) const
{
	BigInt bigN(x);
	bool equal = false;
	vector<int>::const_iterator it2;
	vector<int>::const_iterator it3;
	vector<int>::const_iterator it4;
	if (this->storage.size() > bigN.storage.size())
	{
		equal = false;
	}
	else if (this->storage.size() < bigN.storage.size())
	{
		equal = true;
	}
	else
	{
		it2 = this->storage.begin();
		it3 = bigN.storage.begin();
		it4 = this->storage.end();
	}
	bool greater = false;
	for (it2; it2 < it4; it2++)
	{
		if (equal == false && greater != true)
		{
			if (*it2 < *it3)
			{
				equal = true;
			}
			else if (*it2 > *it3) { greater = true; }
		}
		it3++;
	}
	return equal;
}
bool BigInt :: operator<(const BigInt& bigN) const
{
	bool equal = false;
	vector<int>::const_iterator it2;
	vector<int>::const_iterator it3;
	vector<int>::const_iterator it4;
	if (this->storage.size() > bigN.storage.size())
	{
		equal = false;
	}
	else if (this->storage.size() < bigN.storage.size())
	{
		equal = true;
	}
	else
	{
		it2 = this->storage.begin();
		it3 = bigN.storage.begin();
		it4 = this->storage.end();
	}
	bool greater = false;
	for (it2; it2 < it4; it2++)
	{
		if (equal == false && greater != true)
		{
			if (*it2 < *it3)
			{
				equal = true;
			}
			else if (*it2 > *it3) { greater = true; }
		}
		it3++;
	}
	return equal;
}

bool BigInt :: operator==(int x) const
{
	BigInt bigN(x);
	bool equal0 = false;
	bool equal1 = true;
	vector<int>::const_iterator it2;
	vector<int>::const_iterator it3;
	vector<int>::const_iterator it4;
	if (this->storage.size() > bigN.storage.size())
	{

		equal1 = false;
	}
	else if (this->storage.size() < bigN.storage.size())
	{
		equal1 = false;
	}
	else
	{
		it2 = this->storage.begin();
		it3 = bigN.storage.begin();
		it4 = this->storage.end();
	}
	bool greater = false;
	for (it2; it2 < it4; it2++)
	{
		if (equal0 == false && greater != true)
		{
			if (*it2 < *it3)
			{
				equal1 = false;
			}
			else if (*it2 > *it3) { greater = true; equal1 = false; }
		}
		it3++;
	}
	if (equal1) { equal0 = true; }
	return equal0;
}

bool BigInt :: operator==(const BigInt bigN) const
{
	bool equal0 = false;
	bool equal1 = true;
	vector<int>::const_iterator it2;
	vector<int>::const_iterator it3;
	vector<int>::const_iterator it4;
	if (this->storage.size() > bigN.storage.size())
	{

		equal1 = false;
	}
	else if (this->storage.size() < bigN.storage.size())
	{
		equal1 = false;
	}
	else
	{
		it2 = this->storage.begin();
		it3 = bigN.storage.begin();
		it4 = this->storage.end();
	}
	bool greater = false;
	for (it2; it2 < it4; it2++)
	{
		if (equal0 == false && greater != true)
		{
			if (*it2 < *it3)
			{
				equal1 = false;
			}
			else if (*it2 > *it3) { greater = true; equal1 = false; }
		}
		it3++;
	}
	if (equal1) { equal0 = true; }
	return equal0;
}
bool BigInt :: operator<=(const BigInt bigN)const
{
	bool equal0 = false;
	bool equal1 = true;
	vector<int>::const_iterator it2;
	vector<int>::const_iterator it3;
	vector<int>::const_iterator it4;
	if (this->storage.size() > bigN.storage.size())
	{
		equal0 = false;
		equal1 = false;
	}
	else if (this->storage.size() < bigN.storage.size())
	{
		equal0 = true;
		equal1 = true;
	}
	else
	{
		it2 = this->storage.begin();
		it3 = bigN.storage.begin();
		it4 = this->storage.end();
	}
	bool greater = false;
	for (it2; it2 < it4; it2++)
	{
		if (equal0 == false && greater != true)
		{
			if (*it2 < *it3)
			{
				equal0 = true;
				equal1 = false;
			}
			else if (*it2 > *it3) { greater = true; equal1 = false; }
		}
		it3++;
	}
	if (equal1) { equal0 = true; }
	return equal0;
}

BigInt BigInt :: operator-(int n)
{
	BigInt temp(*this);
	return (temp - BigInt(n));
	//return (*this - BigInt(n)); //freebi
}
BigInt BigInt :: operator-(BigInt bigN)
{

	BigInt temp;
	if ((*this).storage.size() == 1 && bigN.storage.size() == 1)
	{
		temp = BigInt(this->storage.at(0) - bigN.storage.at(0));
	}
	else
	{
		if (bigN == *this) {}// do nothing to return temp which is zero
		else
		{
			vector<int>::reverse_iterator it2;
			vector<int>::reverse_iterator it3;
			vector<int>::reverse_iterator it4;

			int carry = 0;
			int x;

			if (this->storage.size() > bigN.storage.size())
			{
				it2 = this->storage.rbegin();

				it4 = this->storage.rend();
				std::reverse(bigN.storage.begin(), bigN.storage.end());
				int stop = this->storage.size() - bigN.storage.size();
				for (int i = 0; i < stop; i++)
				{
					bigN.storage.push_back(0);
				}
				std::reverse(bigN.storage.begin(), bigN.storage.end());
				it3 = bigN.storage.rbegin();
			}
			else if (this->storage.size() < bigN.storage.size())
			{

				it2 = bigN.storage.rbegin();
				it4 = bigN.storage.rend();
				std::reverse(this->storage.begin(), this->storage.end());
				int stop = bigN.storage.size() - this->storage.size();
				for (int i = 0; i < stop; i++)
				{
					this->storage.push_back(0);
				}
				std::reverse(this->storage.begin(), this->storage.end());
				it3 = this->storage.rbegin();
			}
			else
			{
				it2 = this->storage.rbegin();
				it3 = bigN.storage.rbegin();
				it4 = this->storage.rend();
			}
			bool is = false;
			for (it2; it2 != it4; it2++)
			{
				int y;

				if (is)
				{
					*it2 = *it2 - 1;
				}

				if (*it2 < *it3)
				{
					y = ((*it2 + 10) - *it3);
					is = true;
					if (it2 == this->storage.rbegin())
					{
						temp.storage.at(0) = y;
					}
					else
					{
						temp.storage.push_back(y);
					}
				}
				else
				{
					y = (*it2 - *it3);
					is = false;
					if (it2 == this->storage.rbegin())
					{
						temp.storage.at(0) = y;
					}
					else
					{
						temp.storage.push_back(y);
					}
				}

				it3++;

			}
			std::reverse(temp.storage.begin(), temp.storage.end());
			temp.stripLeadingZero();
		}
	}
	return temp;
}

void BigInt::operator++(int)
{

	*this = *this + BigInt(1);
}
BigInt BigInt:: operator+(BigInt bigN)
{
	BigInt temp;
	if ((*this).storage.size() == 1 && bigN.storage.size() == 1)
	{
		temp = BigInt(this->storage.at(0) + bigN.storage.at(0));
	}
	else
	{
		vector<int>::reverse_iterator rit2;
		vector<int>::reverse_iterator rit3;
		vector<int>::reverse_iterator rit4;
		int car = 0;
		int x;
		if (this->storage.size() > bigN.storage.size())
		{
			int stop = this->storage.size() - bigN.storage.size();
			std::reverse(bigN.storage.begin(), bigN.storage.end());
			for (int i = 0; i < stop; i++)
			{
				bigN.storage.push_back(0);
			}
			std::reverse(bigN.storage.begin(), bigN.storage.end());
			rit2 = this->storage.rbegin();
			rit4 = this->storage.rend();
			rit3 = bigN.storage.rbegin();
		}
		else if (this->storage.size() < bigN.storage.size())
		{
			int stop = bigN.storage.size() - this->storage.size();
			std::reverse(this->storage.begin(), this->storage.end());
			for (int i = 0; i < stop; i++)
			{
				this->storage.push_back(0);
			}
			std::reverse(this->storage.begin(), this->storage.end());
			rit2 = this->storage.rbegin();
			rit3 = bigN.storage.rbegin();
			rit4 = this->storage.rend();

		}
		else
		{

			rit2 = this->storage.rbegin();
			rit3 = bigN.storage.rbegin();
			rit4 = this->storage.rend();
		}
		bool carryd = false;
		for (rit2; rit2 != rit4; rit2++)
		{
			x = *rit2 + *rit3 + car;
			if (x > 9)
			{
				std::string num = std::to_string(x);
				int num0 = num.at(1) - '0';
				if (rit2 == this->storage.rbegin())
				{
					temp.storage.at(0) = num0;
				}
				else
				{
					temp.storage.push_back(num0);
				}
				int num1 = num.at(0) - '0';
				car = num1;
				carryd = true;
			}
			else
			{
				if (rit2 == this->storage.rbegin())
				{
					temp.storage.at(0) = x;
				}
				else
				{
					temp.storage.push_back(x);
					car = 0;
					carryd = false;
				}
			}
			rit3++;
		}
		if (car) { temp.storage.push_back(car); }

		std::reverse(temp.storage.begin(), temp.storage.end());
	}
	return temp;
}
ostream& operator<<(ostream& out, BigInt& bigN)
{
	vector<int>::iterator it;
	for (it = bigN.storage.begin(); it != bigN.storage.end(); it++)
	{
		out << *it;
	}
	return out;
}