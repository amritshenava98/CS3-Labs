// modified figure adapter pattern
// Dan Fabian
// 4/4/2019

#include <iostream>

using std::cout; using std::endl;

// base interface
////////////////////////////////////////////////////////
class Figure {
public:
  virtual void draw()=0;
  virtual ~Figure(){}
};

// adaptee/implementer
////////////////////////////////////////////////////////
class LegacyRectangle{
public:
  LegacyRectangle(int topLeftX, 
		  int topLeftY, 
		  int bottomRightX, 
		  int bottomRightY): 
    topLeftX_(topLeftX), 
    topLeftY_(topLeftY), 
    bottomRightX_(bottomRightX), 
    bottomRightY_(bottomRightY){}

  void oldDraw();
  void move(int, int, int, int); // generic repositioning and resizing of the figure

  int getTopLeftX()     const { return topLeftX_; }
  int getTopLeftY()     const { return topLeftY_; }
  int getBottomRightX() const { return bottomRightX_; }
  int getBottomRightY() const { return bottomRightY_; }

private: // defining top/left and bottom/right coordinates 
  int topLeftX_;
  int topLeftY_;
  int bottomRightX_;
  int bottomRightY_;
};

void LegacyRectangle::oldDraw()
{
  for(int i=0; i < bottomRightY_; ++i)
    {
      for(int j=0; j < bottomRightX_; ++j)
	if(i >= topLeftY_  && j >= topLeftX_ )
	  cout << '*';
	else
	  cout << ' ';
      cout << endl;
    }
}

void LegacyRectangle::move(int topLeftX, int topLeftY, 
			   int bottomRightX, int bottomRightY)
{
  topLeftX_ = topLeftX;
  topLeftY_ = topLeftY;
  bottomRightX_ = bottomRightX;
  bottomRightY_ = bottomRightY;
}

// adapter uses multiple inheritance to inherit
// interface and implementation
////////////////////////////////////////////////////////
class SquareAdapter: public Figure, 
		     private LegacyRectangle {
public:
  SquareAdapter(int size): 
    LegacyRectangle(0,0,size,size){};

  void draw() override { oldDraw(); }
  void resize(int newSize) { this->move(0, 0, newSize, newSize); }
  int size() const { return getBottomRightX(); }
};


// main
////////////////////////////////////////////////////////
int main(){
  // original
  cout << "Size of square? ";
  int size; std::cin >> size;

  SquareAdapter square(size);
  cout << "Size is " << square.size() << '\n';
  square.draw();

  // resizing
  cout << "New size of square? ";
  int newSize; std::cin >> newSize;

  square.resize(newSize);
  cout << "Size is " << square.size() << '\n';
  square.draw();
}
