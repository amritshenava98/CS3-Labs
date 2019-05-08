// sorting apples using algorithms
// Dan Fabian
// 2/21/2019


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using namespace std::placeholders;

struct Apples{
  double weight; // oz
  string color;  // red or green
  bool operator<(const Apples& rhs) const { return weight < rhs.weight; }
  void print() const { cout << color << ", " <<  weight << endl; }
};

bool isLessThan(const Apples& a, const double& maxWeight) { return a.weight < maxWeight; }

int main(){
  srand(time(nullptr));
  const double minWeight = 8.;
  const double maxWeight = 3.;

  cout << "Input crate size: ";
  int size;
  cin >> size;

  vector <Apples> crate(size);

  // assign random weight and color to apples in the crate
  // replace with generate()
  std::generate(crate.begin(), crate.end(),
		[=]{ Apples a; 
		     a.weight =  minWeight + 
		         static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
		     a.color = rand() % 2 == 1 ? "green" : "red";
		     return a; });
 
  cout << "Enter weight to find: ";
  double toFind;
  cin >> toFind;


  // count_if()
  int cnt = std::count_if(crate.begin(), crate.end(), 
			  [=](Apples a){ return a.weight > toFind; });

  cout << "There are " << cnt << " apples heavier than " 
       << toFind << " oz" <<  endl;


  // find_if()
  cout << "at positions ";
  auto applePos = std::find_if(crate.begin(),crate.end(),
			       [=](Apples a){ return a.weight > toFind; });
  int pos;
  while(applePos != crate.end())
    {
      pos = std::distance(crate.begin(), applePos);

      if (applePos != crate.end()) 
	cout << pos << ", ";

      applePos = std::find_if(++applePos, crate.end(),
			      [=](Apples a){ return a.weight > toFind; });
    } while(applePos != crate.end());
  cout << endl;


  // max_element()
  auto heaviest =  std::max_element(crate.begin(), crate.end());
  cout << "Heaviest apple weighs: " << heaviest->weight << " oz" << endl;


  // for_each() or accumulate()
  double sum = std::accumulate(crate.begin(), crate.end(), 0,
			       [](double num, Apples a){ return num + a.weight; });
  cout << "Total apple weight is: " << sum << " oz" << endl;


  // transform();
  cout << "How much should they grow: ";
  double toGrow;
  cin >> toGrow;
  
  std::transform(crate.begin(), crate.end(), crate.begin(),
		 [=](Apples a){ a.weight += toGrow; return a; });


  // remove_if()
  cout << "Input minimum acceptable weight: ";
  double minAccept;
  cin >> minAccept;
 
  auto removeIt = std::remove_if(crate.begin(), crate.end(),
				 [=](Apples a){return a.weight < minAccept;});
  crate.erase(removeIt, crate.end());
  cout << "removed " << size - crate.size() << " elements" << endl;


  // bubble sort, replace with sort()
  std::sort(crate.begin(), crate.end());


  // moving all red apples from crate to peck
  // remove_copy_if() with back_inserter()/front_inserter() or equivalents
  deque<Apples> peck;
  std::remove_copy_if(crate.begin(), crate.end(), std::front_inserter(peck),
		      [](Apples a){ return a.color != "red"; });
  auto removeIt2 = std::remove_if(crate.begin(), crate.end(),
  				  [](Apples a){ return a.color == "red"; });
  crate.erase(removeIt2, crate.end());


  // for_each() possibly
  std::for_each(crate.begin(), crate.end(), 
		[](Apples a){ a.print(); });
  cout << endl;


  // for_each() possibly
  std::for_each(peck.begin(), peck.end(),
		[](Apples a){ a.print(); });


   // prints every "space" apple in the peck
   const int space=3; 
   cout << "\nevery " << space << "\'d apple in the peck"<< endl;


   // replace with advance()/next()/distance()
   // no pointer arithmetic
   auto it=peck.cbegin();   
   while(it != peck.cend()){
     if((std::distance(peck.cbegin(), it) + 1) % space == 0)
	it->print();

      ++it;
   }

   // putting all small green apples in a jam
   // use a binder to create a functor with configurable max weight
   // count_if() then remove_if()
   const double weightToJam = 10.0;
   double jamWeight = 0;

   auto lessThanBind = bind(isLessThan, _1, weightToJam);

   int cntApples = 0;
   auto iterator = crate.begin();
   while (std::count_if(crate.begin(), crate.end(), lessThanBind) != cntApples)
       if (iterator->weight < weightToJam)
	 {
	   jamWeight += iterator->weight;
	   ++cntApples;
	 }

   auto removeIt3 = std::remove_if(crate.begin(), crate.end(), lessThanBind);
   crate.erase(removeIt3, crate.end());

   cout << "Weight of jam is: " << jamWeight << endl;

}

