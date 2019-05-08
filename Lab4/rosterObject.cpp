// prints out roster of students with enrolled courses with objects in containers
// Dan Fabian
// 2/7/2019

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
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

  // adds course to list
  void addCourse(const string& name) { courses.push_back(name); }

  // print out student in form "last name, first name:  courses enrolled"
  void printCourses() const
  { 
    // print classes
    for (auto it = courses.cbegin(); it != courses.cend(); ++it)
	cout << *it << " ";
      
    cout << "\n";
  }

private:
  string firstName_;
  string lastName_;
  list<string> courses;
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

  // ADDING CLASSES AND PRINTING
  //====================================================================

  // NOTE: courseStudents[0] holds the roster for class in argv[1] and so on
  // iterate through all classes
  for (int i = 0; i != courseStudents.size(); ++i) 
    {
      // sort roster
      courseStudents[i].sort();

      // get name of class
      string className(argv[i + 1]); // form of %.txt
      className.erase(className.end() - 4, className.end()); // deletes .txt

      // creating iterators 
      std::list<Student>::iterator studentsIndex = allStudents.begin();
      std::list<Student>::iterator rosterIndex = courseStudents[i].begin();

      // search for students name in class roster
      while (rosterIndex != courseStudents[i].end() &&
	     studentsIndex != allStudents.end())
	{
	  // if name exists in roster add class and iterate both indices
	  if (*rosterIndex == *studentsIndex)
	    {
	      studentsIndex->addCourse(className);
	            
	      ++studentsIndex;
	      ++rosterIndex;
	    }

	  else if (*studentsIndex < *rosterIndex)
	    ++studentsIndex;

	  else
	    ++rosterIndex;
	}
    }

  // print students and classes
  cout << "All Students\n"
       << "last name, first name: courses enrolled\n";

  for (const auto &student: allStudents)
    {
      cout << student.print()<< ": ";
      student.printCourses();
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
