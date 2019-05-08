// Reads in a file then counts occurence of each word
// Dan Fabian
// 1/24/2019

#include "WordList.h"

int main(int argc, char* argv[])
{  
  // check input
  if (argc != 2)
    {
      cout << "Not enough inputs.\n";
      return 1;
    }
  
  // open file
  string fileName = argv[1];
  ifstream input(fileName);
  
  // check if open
  if (!input.is_open())
    {
      cout << "File couldn't be opened.\n";
      return 1;
    }
  
  WordList wordList;
  string word;
  while (!input.eof())
    {
      input >> word;
      
      // check if there is punctuation at end of word
      if (!isalnum(word.back()))
	word.pop_back();
      
      // check if there is punc at the begining of the word
      if (!isalnum(word.front()))
	word.erase(0);

      // check if word is now empty after deleting chars
      if (word != "")
	wordList.addWord(word);
    }
  
  wordList.print();
}
