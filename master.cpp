#include <iostream>
#include "master.hpp"

static int worldInit[10][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

Master::Master() {

}

Master::~Master() {

}

void Master::generateAgents() {
	for (int y = 0; y < 10; ++y) {
		std::vector<Agent> row;
		for (int x = 0; x < 10; ++x) {
			Agent agent(50.0f, 50.f * x, 50.f * y);
			agent.setState(worldInit[y][x]);
			row.push_back(agent);
		}
		agents.push_back(row);
	}
}

// BEGIN: helpers

int up(int current) {
	if (current > 0) {
		return current - 1;
	} else {
		return 9;
	}
}

int down(int current) {
	if (current < 9) {
		return current + 1;
	} else {
		return 0;
	}
}

int left(int current) {
	if (current > 0) {
		return current - 1;
	} else {
		return 9;
	}
}

int right(int current) {
	if (current < 9) {
		return current + 1;
	} else {
		return 0;
	}
}

// END: helpers

void Master::update() {
	int y = 0;
	for (auto row = agents.begin(); row != agents.end(); ++row) {
		int x = 0;
		for (auto agent = row->begin(); agent != row->end(); ++agent) {
			std::vector<int> sensor;
			sensor.push_back(agents[up(y)][left(x)].getState());
			sensor.push_back(agents[up(y)][x].getState());
			sensor.push_back(agents[up(y)][right(x)].getState());
			sensor.push_back(agents[y][left(x)].getState());
			sensor.push_back(agents[y][right(x)].getState());
			sensor.push_back(agents[down(y)][left(x)].getState());
			sensor.push_back(agents[down(y)][x].getState());
			sensor.push_back(agents[down(y)][right(x)].getState());
			agent->update(sensor);
			x++;
		}
		y++;
	}
}

void Master::draw() {
	for (auto row = agents.begin(); row != agents.end(); ++row) {
		for (auto agent = row->begin(); agent != row->end(); ++agent) {
			//std::cout << agent->getState() << " ";
			agent->draw();
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;
}