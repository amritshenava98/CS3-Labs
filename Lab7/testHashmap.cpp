// demoes modified hashmap implementation
// Dan Fabian
// 2/28/2019

#include "hashmap.h"
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;

int main() {
  hashmap<int, int> myHash;
  
  // INSERT TEST
  //===============================================
  auto pntBool = myHash.insert(pair<int,int>(4, 40));
  auto pntBool_2 = myHash.insert(make_pair(4, 40));

  cout << "first insert of 4, 40 success? " 
       << std::boolalpha << pntBool.second << "\n"

       << "second insert of 4, 40 success? " 
       << std::boolalpha << pntBool_2.second << "\n";

  pntBool_2.first->second = 45;
  cout << "Changed value of 4, 40 element to " <<  pntBool_2.first->second << "\n";

  // x will have type hashmap<int, int>::value_type*
  auto x = myHash.find(4);
  if (x != nullptr) 
    cout << "4 maps to " << x->second << endl;
  else 
    cout << "cannot find 4 in map" << endl;

  cout << "FINISHED TESTING INSERT\n\n";
   
  // ERASE TEST
  //===============================================
  // 4 is the only element in the map
  auto pntBool_3 = myHash.erase(4);
  cout << "deletion of 4 succesful? " << std::boolalpha << pntBool_3.second << "\n";

  if (pntBool_3.first == nullptr) 
    cout << "deleted the final element so pointer points to nullptr\n";

  myHash.insert(make_pair(1, 5));
  myHash.insert(make_pair(5, 20));
  myHash.insert(make_pair(6, 15));
  cout << "inserted elements with keys 1, 5, and 6\n";
  
  auto pntBool_4 = myHash.erase(1);
  auto z = myHash.find(1);
  if (z == nullptr)
    cout << "erased key 1 succesfully? " << std::boolalpha << pntBool_4.second << "\n";

  cout << "next elements key is " << pntBool_4.first->first << "\n"; 
  

  // erase element that doesn't exist
  auto pntBool_5 = myHash.erase(25);
  cout << "deleting element with key 20 was succesful? " 
       << std::boolalpha << pntBool_5.second << "\n";
  if (pntBool_5.first == nullptr)
    cout << "pointer points to nullptr\n";

  cout << "FINISHED TESTING ERASE\n\n";


  // [] OPERATOR TEST
  //===============================================
  hashmap<int, string> employees;

  // entering entries with indexing operator
  employees[123] = "Mike";
  employees[345] = "Charlie";
  employees[192] = "Joe";
  employees[752] = "Paul";
  employees[328] = "Peter";

  cout << "element at key 123 is " << employees[123] << "\n";
  cout << "Enter new employee name for key 123: "; string name; cin >> name;

  employees[123] = name; // "unsafe" insert

  cout << "element at key 123 is " << employees[123] << "\n";

  cout << "FINISHED TESTING [] OPERATOR\n\n";
  

  // REHASH TEST
  //===============================================
  // rehash employees with only one bucket 
  employees.rehash(131);
  
  cout << "employees map has been rehashed\n";
  
  cout << "element at key 123 is " << employees[123] << "\n"
       << "element at key 345 is " << employees[345] << "\n"
       << "element at key 192 is " << employees[192] << "\n"
       << "element at key 752 is " << employees[752] << "\n"
       << "element at key 328 is " << employees[328] << "\n";

  cout << "FINISHED TESTING REHASH\n";
}
