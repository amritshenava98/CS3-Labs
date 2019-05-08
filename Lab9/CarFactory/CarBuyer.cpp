// modified car lot class and buyer
// Dan Fabian
// 3/21/2019

#include <iostream>
#include <vector>
#include <cstdlib>
#include <array>
#include "CarFactory.h"

using std::vector;
using std::cout; using std::endl;

// CARLOT CLASS
//////////////////////////////////////////////////////////////////
class CarLot{
public:
  CarLot();
  Car* nextCar();
  int lotSize() { return maxCars4Sale_; }

  // if a car is bought, requests a new one
  Car* buyCar(){
    Car *bought = cars4sale_[carNum_];
    cars4sale_.erase(cars4sale_.begin() + carNum_); // sold car
    cars4sale_.push_back(factories_[rand()%factories_.size()]->requestCar());
    return bought;
  }
private:
  vector<Car *> cars4sale_; // cars for sale on lot
  vector<CarFactory *> factories_;
  static const int maxCars4Sale_ = 10;
  static int carNum_; // car being looked at right now
};

// CARLOT MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////
int CarLot::carNum_ = -1;

CarLot::CarLot(){
  // creates 2 Ford factories and 2 Toyota factories 
  factories_.push_back(new FordFactory());   
  factories_.push_back(new ToyotaFactory());
  factories_.push_back(new FordFactory());
  factories_.push_back(new ToyotaFactory());

  // fills lot with random cars
  for (int i = 0; i != maxCars4Sale_; ++i)
    cars4sale_.push_back(factories_[rand() % factories_.size()] -> requestCar());
}

Car* CarLot::nextCar()
{
  carNum_ = (++carNum_) % maxCars4Sale_;
  return cars4sale_[carNum_];
}

CarLot *carLotPtr = nullptr; // global pointer instantiation

// CAR BUYER FUNCTION
//////////////////////////////////////////////////////////////////
void carBuyer(int id) 
{
  if (carLotPtr == nullptr)
    carLotPtr = new CarLot();
  
  std::string requestedMake = rand() % 2 == 0 ? "Ford" : "Toyota";

  // make arrays of possible models
  static const std::array<std::string, 4>
    fordModels = {"Focus", "Mustang", "Explorer", "F-150"};
  static const std::array<std::string, 5>
    toyotaModels = {"Corolla", "Camry", "Prius", "4Runner", "Yaris"};

  // selecting random model
  std::string requestedModel = requestedMake == "Ford" ?
    fordModels[rand() % fordModels.size()] :
    toyotaModels[rand() % toyotaModels.size()];

  cout << "Buyer " << id << " wants a " 
       << requestedMake << ' ' << requestedModel << '\n';

  Car *toBuy;
  bool foundCarTheyLike = false;
  // go through each car until they find one they like
  for (int i = 0; i != carLotPtr->lotSize() && !foundCarTheyLike; ++i)
    {
      // test out car
      toBuy = carLotPtr->nextCar();
      cout << "Car being looked at is a "
	   << toBuy->getMake() << ' ' << toBuy->getModel() << endl;
      // check if they like it
      if (toBuy->getMake() == requestedMake &&
	  toBuy->getModel() == requestedModel)
	foundCarTheyLike = true;
    }

  if (foundCarTheyLike)
    {
      cout << "Found what they want! They are buying it!\n\n";
      carLotPtr -> buyCar();
    }
  else
    cout << "Couldn't find what they wanted. They are leaving.\n\n";
}

// MAIN
//////////////////////////////////////////////////////////////////
int main() {
  srand(time(nullptr));

  const int numBuyers=10;
  for(int i=0; i < numBuyers; ++i)
    carBuyer(i);
}
