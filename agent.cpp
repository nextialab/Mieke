#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "agent.hpp"

#define RAD 0.01745329

Agent::Agent() {
    id = 0;
    x = 0.0;
    y = 0.0;
    angle = 0.0;
    side = 0.1;
}

Agent::Agent(int id, float x, float y, float angle) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->angle = angle;
    side = 0.02;
}

Agent::~Agent() {

}

void Agent::update() {
    float dx = 0.01 * cos(angle * RAD);
    float dy = 0.01 * sin(angle * RAD);
    if ((x > 0.9f && dx > 0.0f) || (x < -0.9f && dx < 0.0f)) {
        dx = -1.0f * dx;
    }
    if ((y > 0.9f && dy > 0.0f) || (y < -0.9f && dy < 0.0f)) {
        dy = -1.0f * dy;
    }
    x += dx;
    y += dy;
    angle = atan2(dy, dx) / RAD;
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