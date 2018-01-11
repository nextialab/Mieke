#ifndef MASTER_HPP
#define MASTER_HPP

#include <vector>
#include "agent.hpp"

class Master {
public:
	Master();
	~Master();
	void generateAgents();
	void update();
	void draw();
private:
	std::vector<std::vector<Agent>> agents;
};

#endif