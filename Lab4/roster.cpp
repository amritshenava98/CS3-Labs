// prints out roster of students with enrolled courses
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

// reading a list from a fileName
void readRoster(list<string>& roster, string fileName);  

// printing a list out
void printRoster(const list<string>& roster); 

int main(int argc, char* argv[]){

  if (argc <= 1){ 
    cout << "usage: " << argv[0] 
	 << " list of courses, dropouts last" 
	 << endl; exit(1);
  }

  // vector of courses of students
  vector<list<string>> courseStudents; 

  for(int i=1; i < argc-1; ++i){
    list<string> roster;
    readRoster(roster, argv[i]);  
    courseStudents.push_back(move(roster)); 
  }

  // reading in dropouts
  list<string> dropouts; 
  readRoster(dropouts, argv[argc-1]); 

  // master list of students
  list<string> allStudents;  
 
  for(auto lst : courseStudents) 
    allStudents.splice(allStudents.end(),
		       lst);
  
  // sorting master list
  allStudents.sort();

  // eliminating duplicates
  allStudents.unique(); 

  // removing individual dropouts
  for (const auto& str : dropouts)  
    allStudents.remove(str);

  // CREATING MASTER ROSTER AND PRINTING
  //====================================================================

  // master roster
  vector<list<string>> masterRoster;

  // adding students names to roster
  for (std::list<string>::iterator it = allStudents.begin(); 
       it != allStudents.end(); ++it)
    {
      // make list for each student
      list<string> student;
      student.push_back(*it);
      
      // add each new list to masterRoster
      masterRoster.push_back(student);
    }

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
      int studentsIndex = 0;
      std::list<string>::iterator rosterIndex = courseStudents[i].begin();
      
      // search for students name in class roster
      while (rosterIndex != courseStudents[i].end() &&
	     studentsIndex != masterRoster.size())
	{
	  // NOTE: index 0 of each master roster list contains name
	  // if name exists in roster add class and iterate both indices
	  if (*rosterIndex == masterRoster[studentsIndex].front())
	    {
	      masterRoster[studentsIndex].push_back(className);
	      
	      ++studentsIndex;
	      ++rosterIndex;
	    }

	  else if (*rosterIndex > masterRoster[studentsIndex].front())
	    ++studentsIndex;

	  else
	    ++rosterIndex;
	}
    }

  // print students and classes
  cout << "All Students\n"
       << "last name, first name: courses enrolled\n";

  for (auto &student: masterRoster)
    {
      // print name
      cout << student.front() << ": ";
      
      // delete name
      student.pop_front();

      // print classes
      for (auto it = student.begin(); it != student.end(); ++it)
	  cout << *it << " ";
      
      cout << "\n";
    }

}


void readRoster(list<string>& roster, string fileName){
  //   ifstream course(fileName.c_str());
  ifstream course(fileName); // I am trying it
    
  string first, last;
  while(course >> first >> last)
    roster.push_back(
		     move(first + ' ' + last));
  course.close();
}

// printing a list out
void printRoster(const list<string>& roster){
  for(const auto& str : roster)
    cout << str << endl;
}
