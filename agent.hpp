#ifndef AGENT_HPP
#define AGENT_HPP

class Agent {
public:
    Agent();
    Agent(int id, float x, float y, float angle);
    ~Agent();
    int id;
    float x;
    float y;
    float angle;
    float side;
    void update();
    void draw();
};

#endif