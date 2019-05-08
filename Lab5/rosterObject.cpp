// prints out roster of students with enrolled courses using maps
// Dan Fabian
// 2/14/2019

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::map;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student{
public:
  Student(string firstName, string lastName): 
    firstName_(firstName), lastName_(lastName) {}
 
  // move constructor, not really needed, generated automatically
  Student(Student && org):
    firstName_(move(org.firstName_)),
    lastName_(move(org.lastName_))
  {}
  
  // force generation of default copy constructor
  Student(const Student & org) = default;
   
  string print() const {return firstName_ + ' ' + lastName_;}

  // needed for unique() and for remove()
  friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	left.firstName_ == right.firstName_;
  }

  // needed for sort()
  friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
			      (left.lastName_ == right.lastName_ && 
			       left.firstName_ < right.firstName_);
  }

private:
  string firstName_;
  string lastName_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

  if (argc <= 1){ cout << "usage: " << argv[0] 
		       << " list of courses, dropouts last" << endl; exit(1);}

  // vector of courses of students
  vector <list<Student>> courseStudents; 

  for(int i=1; i < argc-1; ++i){
    list<Student> roster;
    readRoster(roster, argv[i]);  
    courseStudents.push_back(move(roster)); 
  }


  // reading in dropouts
  list<Student> dropouts; 
  readRoster(dropouts, argv[argc-1]);

  list<Student> allStudents;  // master list of students
 
  for(auto lst : courseStudents) 
    allStudents.splice(allStudents.end(),lst);

  allStudents.sort(); // sorting master list

  allStudents.unique(); // eliminating duplicates
   
  for (const auto& str : dropouts)  // removing individual dropouts
    allStudents.remove(str);

  // CREATING MASTER ROSTER AND PRINTING
  //====================================================================

  map<Student, list<string>> masterRoster;

  // create student keys
  for (const auto &student: allStudents)
    masterRoster[student] = list<string>();

  // go through all course rosters
  for (int i = 0; i != courseStudents.size(); ++i)
    {
      // get name of class
      string className(argv[i + 1]); // form of %.txt
      className.erase(className.end() - 4, className.end()); // deletes .txt

      // search roster for students
      for (auto it = courseStudents[i].begin(); 
	   it != courseStudents[i].end(); ++it)
	{
	  auto studentLoc = masterRoster.find(*it);
	  
	  // check if student is in master roster
	  if (studentLoc != masterRoster.end())
	    studentLoc->second.push_back(className); // if so then add class to list
	}
    }

  // print header
  cout << "All Students\n"
       << "last name, first name: courses enrolled\n";

  // print out master roster
  for (auto student = masterRoster.begin(); 
       student != masterRoster.end(); ++student)
    {
      cout << student->first.print() << ": ";
      
      // print classes
      for (auto it = student->second.cbegin(); 
	   it != student->second.cend(); ++it)
	cout << *it << " ";
      
      cout << "\n";
    }
}

void readRoster(list<Student>& roster, string fileName){
  ifstream course(fileName);
    
  string first, last;
  while(course >> first >> last)
    roster.push_back(Student(first, last));
  course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
  for(const auto& student : roster)
    cout << student.print() << endl;
}
