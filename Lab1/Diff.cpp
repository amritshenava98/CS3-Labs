// Reads in two files and finds differences
// Dan Fabian
// 1/17/2019

#include <iostream>
#include <fstream>
#include <string>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::to_string;

int main(int argc, char* argv[])
{
  // check amount of arguments
  if (argc != 3)
    {
      cout << "Not enough arguments.\n";
      return 1;
    }
  
  // creating strings
  string file1(argv[1]);
  string file2(argv[2]);

  // opening file streams
  ifstream inFile1(file1);
  ifstream inFile2(file2);

  // checking if files opened
  if (!inFile1.is_open() || !inFile2.is_open())
    {
      cout << "File couldn't be opened.\n";
      return 1;
    }

  string line1;
  string line2;
  int lineNumber = 1;
  while (!inFile1.eof() || !inFile2.eof())
    {
      // get line from file 1
      if (!inFile1.eof())
	getline(inFile1, line1);
      else
	line1 = ' '; // if the file ended then consider it as an empty line

      // same for file 2
      if (!inFile2.eof())
	getline(inFile2, line2);
      else
	line2 = ' ';

      if (line1 != line2)
	{
	  string carrot(file1.length(), ' '); // adding spaces for file name
	  string lineNumberStr;

	  lineNumberStr = lineNumberStr + ": " + to_string(lineNumber) + ": ";

	  for (int j = 0; j < lineNumberStr.length(); ++j)
	    carrot += ' '; // adding spaces for line number and colons

	  int i = 0;
	  while (line1[i] == line2[i])
	    {
	      ++i;
	      carrot += ' '; // adding space to move carrot to position where they differ
	    }

	  carrot += '^';

	  cout << file1 << lineNumberStr << line1 << "\n"
	       << file2 << lineNumberStr << line2 << "\n"
	       << carrot << "\n\n";
	}

      ++lineNumber;
    }

  // closing streams
  inFile1.close();
  inFile2.close();
}

