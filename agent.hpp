#ifndef AGENT_HPP
#define AGENT_HPP

class Agent {
public:
    Agent();
    Agent(float x, float y, float angle);
    ~Agent();
    float x;
    float y;
    float angle;
    float side;
    void update(double rand0, double rand1);
    void draw();
};

#endif