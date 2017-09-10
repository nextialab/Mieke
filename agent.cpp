#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "agent.hpp"

#define RAD 0.01745329

Agent::Agent() {
    x = 0.0;
    y = 0.0;
    angle = 0.0;
    side = 0.1;
}

Agent::Agent(float x, float y, float angle) {
    this->x = x;
    this->y = y;
    this->angle = angle;
    side = 0.02;
}

Agent::~Agent() {

}

void Agent::update(double rand0, double rand1) {
    if (rand0 > 0.5) {
        // move forward
        x += 0.01 * cos(angle * RAD);
        y += 0.01 * sin(angle * RAD);
    } else {
        // turn
        if (rand1 > 0.5) {
            angle += 5.0;
            if (angle > 180.0) {
                angle -= 360.0;
            }
        } else {
            angle -= 5.0;
            if (angle < -180.0) {
                angle += 360.0;
            }
        }
    }   
}

void Agent::draw() {
    float x0 = x + side * cos(angle * RAD);
    float y0 = y + side * sin(angle * RAD);
    float x1 = x + side * cos((angle + 135.0) * RAD);
    float y1 = y + side * sin((angle + 135.0) * RAD);
    float x2 = x + side * cos((angle - 135.0) * RAD);
    float y2 = y + side * sin((angle - 135.0) * RAD);
    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.2, 0.3);
    glVertex3f(x0, y0, 0); // x, y, z
    glVertex3f(x1, y1, 0);
    glVertex3f(x2, y2, 0);
    glEnd();
}