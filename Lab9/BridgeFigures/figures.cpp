// modified bridge pattern with figures and fills
// Dan Fabian
// 3/22/2019

#include <iostream>

using std::cout; using std::endl; using std::cin;

// FILLS
/////////////////////////////////////////////////////////////////
// abstract body
class Fill{
public:
  Fill(char border, char internal)
    : borderChar_(border), internalChar_(internal) {}
  virtual char getBorder() { return borderChar_; } //=0;
  virtual char getInternal() { return internalChar_; } //=0;
  virtual ~Fill() {}
protected:
  char borderChar_;
  char internalChar_;
};

// concrete body
class Hollow: public Fill{
public:
  Hollow(char border) : Fill(border, ' ') {}
  //char getBorder() override { return borderChar_; }
  //char getInternal() override { return internalChar_; }
  ~Hollow(){}
};

// another concrete body
class Filled: public Fill{
public:
  Filled(char fillChar):Fill(fillChar, fillChar) {}
  //char getBorder() override { return borderChar_; }
  //char getInternal() override { return internalChar_; }
  ~Filled(){}
};

// yet another concrete body
class EnhancedFilled: public Fill{
public:
  EnhancedFilled(char border, char internal) : Fill(border, internal) {};
  //char getBorder() override { return borderChar_; }
  //char getInternal() override { return internalChar_; }
  ~EnhancedFilled(){}
};

// FIGURES
/////////////////////////////////////////////////////////////////
// abstract handle
class Figure {
public:
  Figure(int size, Fill* fill): size_(size), 
				fill_(fill){}
  void changeFill(const Fill* fill) { fill_ = const_cast<Fill *>(fill); }
  virtual void draw() =0;
  virtual ~Figure(){}
protected:
  int size_;
  Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
  Square(int size, Fill* fill): Figure(size, fill){}
  void draw() override;
};


void Square::draw(){
  for(int i=0; i < size_; ++i){
    for(int j=0; j < size_; ++j)
      if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	cout << fill_ -> getBorder();
      else
	cout << fill_ -> getInternal();
    cout << endl;
  }
}

// MAIN
/////////////////////////////////////////////////////////////////
int main(){

   Fill* hollowPaintY = new Hollow('Y');
   Fill* filledPaintY = new Filled('Y');
   
   // painting filled
   Figure *box = new Square(4, filledPaintY);
   box->draw();
   cout << endl;

   // painting hollow
   box->changeFill(hollowPaintY);
   box->draw();
   cout << endl;
  
   // demonstrating all 3 different fills
   Fill* hollowPaint = new Hollow('X');
   Fill* filledPaint = new Filled('#');
   Fill* enhancedPaint = new EnhancedFilled('&', 'M');

   // print hollow
   Figure *biggerBox = new Square(10, hollowPaint);
   biggerBox->draw();
   cout << endl;

   // print filled
   biggerBox->changeFill(filledPaint);
   biggerBox->draw();
   cout << endl;

   // print enhanced
   biggerBox->changeFill(enhancedPaint);
   biggerBox->draw();
   cout << endl;
}
