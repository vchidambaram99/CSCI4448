#include <type_traits>
#include <cstdlib>
#include <sstream>
#include "tools.h"

Tool::Tool() : name("") {}
Tool::~Tool(){}
void Tool::setName(std::string n){ name = n; }
std::string Tool::getName() { return name; }

PaintingTool::PaintingTool(){}
PaintingTool::~PaintingTool(){}
PaintingTool::PaintingTool(std::string n){ name = n; }
double PaintingTool::getCost() { return 7.99; }

ConcreteTool::ConcreteTool(){}
ConcreteTool::~ConcreteTool(){}
ConcreteTool::ConcreteTool(std::string n){ name = n; }
double ConcreteTool::getCost() { return 10.99; }

PlumbingTool::PlumbingTool(){}
PlumbingTool::~PlumbingTool(){}
PlumbingTool::PlumbingTool(std::string n){ name = n; }
double PlumbingTool::getCost() { return 6.99; }

YardworkTool::YardworkTool(){}
YardworkTool::~YardworkTool(){}
YardworkTool::YardworkTool(std::string n){ name = n; }
double YardworkTool::getCost() { return 5.99; }

WoodworkTool::WoodworkTool(){}
WoodworkTool::~WoodworkTool(){}
WoodworkTool::WoodworkTool(std::string n){ name = n; }
double WoodworkTool::getCost() { return 8.99; }

Tool* ToolFactory::randomTool(){
	switch(std::rand()%5){
	case 0:
		return makeTool<PaintingTool>();
	case 1:
		return makeTool<ConcreteTool>();
	case 2:
		return makeTool<PlumbingTool>();
	case 3:
		return makeTool<YardworkTool>();
	case 4:
		return makeTool<WoodworkTool>();
	}
	return 0;
}
template<typename T> T* ToolFactory::makeTool(){
	std::stringstream name;
	//Determine tool type, create name, construct and return tool
	//Because of templating, these if statements are solved at compile-time
	if(std::is_same<T,PaintingTool>::value){
		name<<"Painting Tool "<<numPainting++;
	}else if(std::is_same<T,ConcreteTool>::value){
		name<<"Concrete Tool "<<numConcrete++;
	}else if(std::is_same<T,PlumbingTool>::value){
		name<<"Plumbing Tool "<<numPlumbing++;
	}else if(std::is_same<T,YardworkTool>::value){
		name<<"Yardwork Tool "<<numYardwork++;
	}else if(std::is_same<T,WoodworkTool>::value){
		name<<"Woodwork Tool "<<numWoodwork++;
	}
	return new T(name.str());
}
int ToolFactory::numPainting = 0;
int ToolFactory::numConcrete = 0;
int ToolFactory::numPlumbing = 0;
int ToolFactory::numYardwork = 0;
int ToolFactory::numWoodwork = 0;
