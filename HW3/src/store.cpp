#include <cassert>
#include "store.h"

Store::Store(int numTools){
	assert(numTools>=5 && "Store must have 5 or more tools");
	profit = 0;
	tools = std::vector<Tool*>(numTools); // 1 tool of each type, rest are random
	tools[0] = ToolFactory::makeTool<PaintingTool>();
	tools[1] = ToolFactory::makeTool<ConcreteTool>();
	tools[2] = ToolFactory::makeTool<PlumbingTool>();
	tools[3] = ToolFactory::makeTool<YardworkTool>();
	tools[4] = ToolFactory::makeTool<WoodworkTool>();
	for(int i = 5;i<tools.size();++i) tools[i] = ToolFactory::randomTool();
	numAvailable = tools.size();
}

Store::~Store(){
	//pretty much everything is dynamically allocated, so the store handles deleting everything
	for(int i = 0;i<tools.size();++i) delete tools[i];
	for(auto it = activeRentals.begin();it!=activeRentals.end();++it) delete *it;
	for(int i = 0;i<completedRentals.size();++i) delete completedRentals[i];
}

int Store::getNumAvailable() { return numAvailable; }

Rental* Store::rentTools(Customer* customer, int numTools, int numDays){
	std::vector<Tool*> toRent(numTools);
	double p = 0; //cost of rental
	for(int i = 0;i<numTools;++i){
		int a = std::rand()%numAvailable; //randomly select which tool to rent
		toRent[i] = tools[a];
		p += toRent[i]->getCost(); //update cost of rental
		giveToolAway(a); //update partition
	}
	p *= numDays; //calculate rental cost
	profit += p;
	Rental* r = new Rental(this,customer,toRent,numDays,p);
	activeRentals.insert(r);
	return r;
}

void Store::returnTools(Rental* r){
	for(int i = 0;i<r->tools.size();++i){
		for(int j = numAvailable;j<tools.size();++j){
			if(r->tools[i]==tools[j]){ //if tools[j] is the tool being returned
				getToolBack(j); //update partition
				break;
			}
		}
	}
	activeRentals.erase(r);
	completedRentals.push_back(r);
}

void Store::updateRentals(){
	for(auto it = activeRentals.begin();it!=activeRentals.end();++it){
		(*it)->decrementDays();
	}
}

void Store::getToolBack(int i){ //helper method to maintain partition
	Tool* tmp = tools[i];
	tools[i] = tools[numAvailable];
	tools[numAvailable++] = tmp;
}

void Store::giveToolAway(int i){ //helper method to maintain partition
	Tool* tmp = tools[i];
	tools[i] = tools[--numAvailable];
	tools[numAvailable] = tmp;
}
