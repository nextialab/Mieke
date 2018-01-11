#ifndef AGENT_HPP
#define AGENT_HPP

#include <vector>

class Agent {
public:
    Agent();
    Agent(float side, float x, float y);
    ~Agent();
    void setState(int state);
    int getState();
    void update(std::vector<int> sensor);
    void draw();
private:
    float x;
    float y;
    float side;
    int state;
    int next_state;
};

#endif