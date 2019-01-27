/*
Valliappan Chidambaram
1/26/19
CSCI4448 HW1
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

struct Pos{
	Pos(int x1, int y1){
		x = x1, y = y1;
	}
	Pos(std::vector<int> p){
		x = p[0], y = p[1];
	}
	int x,y;
	friend std::ostream& operator<<(std::ostream& out, const Pos p){
		out<<"("<<p.x<<","<<p.y<<")";
		return out;
	}
};

class Shape{
public:
	Shape(int z1){
		z = z1;
	}
	virtual ~Shape(){}
	virtual void display(){
		std::cout<<"z: "<<std::setw(2)<<z<<", Shape"<<std::endl;
	}
	void setZ(int z1){ z = z1; }
	int getZ() const { return z; }
protected:
	int z;
};

class Circle : public Shape{
public:
	Circle(Pos p, int r1, int z1 = 0) : Shape(z1), center(p) {
		r = r1;
	}
	void setR(int r1){ r = r1; }
	void setCenter(Pos p){ center = p; }
	int getR() const { return r; }
	Pos getCenter() const { return center; }
	void display(){
		std::cout<<"z: "<<std::setw(2)<<z<<", Circle with radius "<<r<<" and center "<<center<<std::endl;
	}
private:
	Pos center;
	int r;
};

class Triangle : public Shape{
public:
	Triangle(Pos p1, Pos p2, Pos p3, int z1 = 0) : Shape(z1), a(p1), b(p2), c(p3) {}
	void setPoints(Pos p1, Pos p2, Pos p3){ a = p1, b = p2, c = p3; }
	std::vector<Pos> getPoints() const { return {a,b,c}; }
	void display(){
		std::cout<<"z: "<<std::setw(2)<<z<<", Triangle with points at "<<a<<", "<<b<<", and "<<c<<std::endl;
	}
private:
	Pos a,b,c;
};

class Rectangle : public Shape{
public:
	Rectangle(Pos ul1, Pos lr1, int z1 = 0) : Shape(z1), ul(ul1), lr(lr1) {}
	void setPoints(Pos ul1, Pos lr1){ ul = ul1, lr = lr1; }
	std::vector<Pos> getPoints() const { return {ul,lr}; }
	void display(){
		std::cout<<"z: "<<std::setw(2)<<z<<", Rectangle with upper left corner at "<<ul<<", and lower right corner at "<<lr<<std::endl;
	}
private:
	Pos ul, lr;
};

class ShapeList{
public:
	ShapeList(){}
	ShapeList(std::vector<Shape*> s){
		shapes = s;
	}
	~ShapeList(){
		for(int i = 0;i<shapes.size();i++){
			delete shapes[i];
		}
	}
	void displayAll(){
		zSort();
		for(int i = 0;i<shapes.size();i++){
			shapes[i]->display();
		}
	}
	void addShape(Shape* shape){
		shapes.push_back(shape);
	}
private:
	void zSort(){
		struct {
        	bool operator()(const Shape* a, const Shape* b) const {
            	return a->getZ() < b->getZ();
        	}
    	} customLess;
		std::sort(shapes.begin(),shapes.end(),customLess);
	}
	std::vector<Shape*> shapes;
};

int main(int argc, char* argv[]){
	std::vector<Shape*> shapes(5);
	shapes[0] = new Circle({0,0},5,3);
	shapes[1] = new Rectangle({-1,1},{1,-1});
	shapes[2] = new Triangle({0,0},{1,1},{0,2},4);
	shapes[3] = new Circle({2,2},1,2);
	shapes[4] = new Triangle({10,10},{15,15},{10,15},1);
	ShapeList list(shapes);
	list.displayAll();
}
