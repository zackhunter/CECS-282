/*
Name:Zachary Hunter
Class: CECS 282
Instructor : Minhthong Nguyen
Purpose of the program : Find if a line is a haiku or not
Last updated : 9/13/19
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int numOfSylls(string);
bool isVowel(char);

//returns if a character is a vowel or not
bool isVowel(char c)
{
	if ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u') || (c == 'y'))
		return true;
	return false;
}
//returns the number of syllables in a string word
int numOfSylls(string word)
{
	string onlyLetters = "";
	for (int i = 0; i < word.length(); i++)
	{
		if (isalpha(word[i]))
		{
			onlyLetters += word[i];
		}
	}
	word = onlyLetters;
	int num = 0;
	//iterates through the string word
	for (int i = 0; i < word.length(); i++)
	{
		//if the letter is capitalized, then make it lower case
		if ((int)word[i] > 64 && (int)word[i] < 91)
		{
			int newAscii = (int)word[i] + 32;
			word[i] = (char)newAscii;
		}
		//if the word is lower case then continue
		else if (word[i] > 122 || word[i] < 97)
		{
			continue;
		}
		//if the word is a vowel
		if (isVowel(word[i]))
		{
			if (i == 0 && word[i] != 'y')//if the letter is a vowel that isn't a y at the beginning of the sentence
			{
				num++;
			}
			else if (i != 0)
			{
				//if the last letter is an e
				if ((i == word.length() - 1) && (word[i] == 'e'))
				{
					//if the letter before that is an 'l' and the letter before that isnt a vowel
					if ((word[i - 1] == 'l') && (!isVowel(word[i - 2])))
					{
						num++;
					}
				}
				//if the word ends in "es"
				else if ((i == word.length() - 2) && (word[i] == 'e') && word[i+1] == 's')
				{
					
					if (!isVowel(word[i - 1]) && !isVowel(word[i - 2]))
					{
						num++;
					}
					else if (word[i - 1] == 'g')
					{
						num++;
					}
				}
				//"qu" is considered a consonant
				else if (word[i] == 'u' && word[i - 1] == 'q')
				{
					continue;
				}
				//if the word has 2 vowels in a row that is one syllable
				else if (isVowel(word[i + 1]))
				{
					num++;
					i++;
				}
				else
				{
					num++;
				}
			}
		}
	}
	if (num == 0)
	{
		num = 1;
	}
	return num;
}
int main()
{
	ifstream input;
	input.open("sentences.txt");
	string singleWord = "";
	string sentence,haiku,line;
	ofstream out;
	out.open("haiku.txt");
	int sylls = 0;
	int ctr = 0;
	//the new haiku lines
	string line1 = "";
	string line2 = "";
	string line3 = "";
	//amount of syllables of each haiku line
	int sylls1 = 0;
	int sylls2 = 0;
	int sylls3 = 0;
	if (input)
	{
		
		//reads one line at a time
		while (getline(input, line))
		{
			sylls = 0;
			sentence = line;
			ctr = 0;
			//the new haiku lines
			line1 = "";
			singleWord = "";
			line2 = "";
			line3 = "";
			//amount of syllables of each haiku line
			sylls1 = 0;
			sylls2 = 0;
			sylls3 = 0;
			//iterates through the line a character at a time
			for (auto x: line)
			{
				//if the character is a space or we are at the end of the line
				if (((int)x == 32) || (ctr == line.length()-1))
				{
					//if we are at the end of the line
					if ((ctr == line.length() - 1))
					{
						singleWord = singleWord + x;
					}
					sylls += numOfSylls(singleWord);
					//if we are less than 6 syllables fill in line 1
					if(sylls1 < 5)
					{
						line1 += singleWord + " ";
						sylls1 += numOfSylls(singleWord);
					}
					//if less than 13 syllables fill in line 2
					else if (sylls2 < 7 && sylls1 == 5 )//&& !(ctr == line.length() - 1)
					{
						line2 += singleWord + " ";
						sylls2 += numOfSylls(singleWord);
						if ((ctr == line.length() - 1))
						{
							out << sentence << endl << endl;
							break;
						}
					}
					//if those are met than fill in line 3
					else if (sylls3 < 5 && sylls2 == 7)
					{
						line3 += singleWord + " ";
						sylls3 += numOfSylls(singleWord);
						if (sylls1 == 5 && sylls2 == 7 && sylls3 == 5 && (ctr == line.length()-1))
						{
							out << line1 << endl << line2 << endl << line3 << endl << endl;
						}
						else if ((ctr == line.length() - 1) || sylls3 > 5)
						{
							out << sentence << endl << endl;
							break;						
						}
					}
					//if it isn't a haiku output the straight line
					else
					{
						out << sentence << endl << endl;
						break;	
					}
					singleWord = "";
				}
				else
				{
					singleWord = singleWord + x;
				}
				ctr++;
			}
		}
	
		input.close();
	}
	out.close();
	getchar();
	return 0;
}