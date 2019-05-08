// Implements logging into a file using Singleton design pattern
// Dan Fabian
// 3/14/2019

#include <fstream>
#include <iostream>
#include <string>

using std::fstream;
using std::cout; using std::endl;
using std::string;

// LOGGER
//////////////////////////////////////////
class Logger {
public:
  static Logger& instance();
  void report(const string&);
  ~Logger();

  // prohibit these functions
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

private:
  Logger();
  fstream fout;
};
//////////////////////////////////////////

Logger& Logger::instance() 
{
  static Logger l;
  return l;
}

void Logger::report(const string& str)
{
  cout << "Logging: " << str << " to file\n";
  fout << str << endl;
}

Logger::Logger() 
{ 
  fout.open("log.txt", fstream::out | fstream::app); 

  if (!fout.is_open())
    cout << "File couldn't be opened.\n";
  else
    cout << "File opened!\n";
}

Logger::~Logger() 
{ 
  fout.close(); 
  cout << "File closed.\n";
}

// MAIN
//////////////////////////////////////////////////
int main() {

  Logger::instance().report("boom boom");
  Logger::instance().report("pow");
}
