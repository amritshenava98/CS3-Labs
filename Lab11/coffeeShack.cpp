// coffee shop main file
// Dan Fabian
// 4/11/2019

#include "coffeeShack.h"
#include <cstdlib>
#include <ctime>

int main()
{
  srand(time(nullptr));

  const int totalCustomers = 3; // how many customers are in the coffee shop

  JuniorBarista *peggy = new JuniorBarista(new SeniorBarista(new Manager));
  int customerNum = 0;
  do
    {
      int selection = rand() % 2;
      if (selection == 0 && customerNum != totalCustomers) // take order
	{
	  // begin making drink
	  char choice; list<Drink*> drink;
	  peggy->handleRequest(choice, drink);

	  // ask for name
	  cout << "Can I get your name? ";
	  string name; cin >> name;
  
	  // create customer
	  Customer *newCustomer = new Customer(name, peggy, drink.back());
	  ++customerNum;
	}
      else if (selection == 1 && !peggy->allCustomersServed()) // finish order
	peggy->finishOrder();
    } while (customerNum < totalCustomers || !peggy->allCustomersServed());

  return 0;
}
