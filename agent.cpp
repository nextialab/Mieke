#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "agent.hpp"

#define RAD 0.01745329

Agent::Agent(float side, float x, float y) {
    this->side = side;
    this->x = x;
    this->y = y;
}

Agent::Agent() {

}

Agent::~Agent() {

}

void Agent::setState(int state) {
    this->state = state;
    this->next_state = state;
}

int Agent::getState() {
    return state;
}

void Agent::update(std::vector<int> sensor) {
    int neighbors = 0;
    for (auto neighbor = sensor.begin(); neighbor != sensor.end(); ++neighbor) {
        if (*neighbor == 1) {
            neighbors++;
        }
    }
    if (state == 1) {
        if (neighbors < 2 || neighbors > 3) {
            next_state = 0;
        }
    } else {
        if (neighbors == 3) {
            next_state = 1;
        }
    }
}

void Agent::draw() {
    state = next_state;
    glBegin(GL_QUADS);
    if (state == 1) {
        glColor3f(1.0f, 1.0f, 1.0f); // white
    } else {
        glColor3f(0.0f, 0.0f, 0.0f); // black
    }
    glVertex3f(x, y, 0); // x, y, z
    glVertex3f(x + side, y, 0);
    glVertex3f(x + side, y + side, 0);
    glVertex3f(x, y + side, 0);
    glEnd();
}