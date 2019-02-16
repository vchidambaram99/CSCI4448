#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include "forward.h"

class Tool {
public:
	Tool();
	virtual ~Tool();
	void setName(std::string n);
	virtual double getCost() = 0;
	std::string getName();
protected:
	std::string name;
};

class PaintingTool : public Tool {
public:
	PaintingTool();
	~PaintingTool();
	PaintingTool(std::string n);
	double getCost();
};

class ConcreteTool : public Tool {
public:
	ConcreteTool();
	~ConcreteTool();
	ConcreteTool(std::string n);
	double getCost();
};

class PlumbingTool : public Tool {
public:
	PlumbingTool();
	~PlumbingTool();
	PlumbingTool(std::string n);
	double getCost();
};

class YardworkTool : public Tool {
public:
	YardworkTool();
	~YardworkTool();
	YardworkTool(std::string n);
	double getCost();
};

class WoodworkTool : public Tool {
public:
	WoodworkTool();
	~WoodworkTool();
	WoodworkTool(std::string n);
	double getCost();
};

class ToolFactory {
public:
	static Tool* randomTool(); //makes a random Tool subclass
	template <typename T> static T* makeTool(); //makes a Tool of type T
private:
	//these static members allow unique names for each tool
	static int numPainting;
	static int numConcrete;
	static int numPlumbing;
	static int numYardwork;
	static int numWoodwork;
};

#endif
