// contains WordOccurrence and WordList classes
// Dan Fabian
// 1/24/2019

#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cctype>

using std::cout; using std::string; using std::sort; using std::ifstream; using std::isalnum;
using std::endl;

class WordOccurrence {
 public:
  // constructors
  WordOccurrence();
  WordOccurrence(const string& word_);
  
  // methods
  bool matchWord(const string &); // returns true if word matches stored
  void increment(); // increments number of occurrences
  string getWord() const;
  int getNum() const;

  // operator
  WordOccurrence& operator=(const WordOccurrence&);
  bool operator<(const WordOccurrence&) const;

 private:
  string word;
  int num;
};

WordOccurrence::WordOccurrence()
{
  word = "";
  num = 0;
}

WordOccurrence::WordOccurrence(const string& word_)
{
  word = word_;
  num = 0;
}

bool WordOccurrence::matchWord(const string& str)
{
  return str == word;
}

void WordOccurrence::increment()
{
  ++num;
}

string WordOccurrence::getWord() const
{
  return word;
}

int WordOccurrence::getNum() const
{
  return num;
}

WordOccurrence& WordOccurrence::operator=(const WordOccurrence& rhs)
{
  if (this == &rhs)
    return *this;

  word = rhs.word;
  num = rhs.num;
  return *this;
}

bool WordOccurrence::operator<(const WordOccurrence& rhs) const
{
  return num < rhs.num;
}

////////////////////////////////////////////////////////////////////////////////////////////

class WordList {
 public:
  // constructor
  WordList();

  // copy constructor, destructor, overloaded assignment
  WordList(const WordList&);
  ~WordList();
  WordList& operator=(const WordList&);
  
  // methods
  void addWord(const string &);
  void print();
  
  // implement comparison as friend
  friend bool equal(const WordList&, const WordList&);
  
 private:
  WordOccurrence *wordArray; // a dynamically allocated array of WordOccurrences
  // may or may not be sorted
  int size;
};

WordList::WordList()
{
  wordArray = nullptr;
  size = 0;
}

WordList::WordList(const WordList& wordList)
{
  size = wordList.size;
  wordArray = new WordOccurrence[wordList.size];

  for (int i = 0; i < size; ++i)
    wordArray[i] = wordList.wordArray[i];
}

WordList::~WordList()
{
  delete[] wordArray;
}

WordList& WordList::operator=(const WordList& rhs)
{
  if (this == &rhs)
    return *this;

  // deleting old wordArray and making a new one
  delete[] wordArray;
  wordArray = new WordOccurrence[rhs.size];

  for (int i = 0; i < rhs.size; ++i)
    wordArray[i] = rhs.wordArray[i];
  size = rhs.size;

  return *this;
}

void WordList::addWord(const string& word)
{
  // check if word is already in list
  for (int i = 0; i < size; ++i)
    if (wordArray[i].matchWord(word)) //if word found then increment and leave function
      {
	wordArray[i].increment();
	return;
      }
  
  // copy old wordArray to tmp
  WordOccurrence *tmp = new WordOccurrence[size];
  for (int i = 0; i < size; ++i)
    tmp[i] = wordArray[i];
  
  // increase size and create new array
  ++size;
  delete[] wordArray;
  wordArray = new WordOccurrence[size];
  
  // re-copy tmp back to newly sized array
  for (int i = 0; i < size - 1; ++i)
    wordArray[i] = tmp[i];
  
  // add new word to final element in array
  WordOccurrence newWord(word);
  newWord.increment();
  wordArray[size - 1] = newWord;
}

void WordList::print()
{
  sort(wordArray, wordArray + size);

  cout << "WORD OCCURRENCES\n\n";
  for (int i = 0; i < size; ++i)
    cout << wordArray[i].getWord() << "\ncount: " << wordArray[i].getNum() << "\n\n";
}

bool equal(const WordList& lhs, const WordList& rhs)
{
  // check size first
  if (lhs.size != rhs.size)
    return false;

  // then check element by element
  for (int i = 0; i < lhs.size; ++i)
    if (lhs.wordArray[i].getWord() != rhs.wordArray[i].getWord())
      return false;

  return true;
}
#endif // WORD_LIST_H
