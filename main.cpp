#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <chrono>
#include <thread>
#include "agent.hpp"

const int width = 640;
const int height = 640;

static void error_callback(int error, const char* description) {
    std::cerr << error << " " << description;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

std::vector<Agent> agents;
std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<float> distribution(0.0, 1.0);
std::chrono::milliseconds cycle{50}; // 20 FPS

void generateAgent(int id) {
    float x, y;
    bool again = true;
    while (again) {
        again = false;
        x = -0.8f + 1.6f * distribution(generator);
        y = -0.8f + 1.6f * distribution(generator);
        for (int i = 0; i < agents.size(); i++) {
            if (pow(agents[i].x - x, 2.0f) + pow(agents[i].y - y, 2.0f) < 0.04f) {
                again = true;
                break;
            }
        }
    }
    float angle = -180.0f + 360.f * distribution(generator);
    std::cout << id << " " << x << " " << y << " " << angle << std::endl;
    agents.push_back(Agent(id, x, y, angle));
}

void setupAgents() {
    for (int i = 0; i < 5; i++) {
        generateAgent(i);
    }
}

int main() {
    // setup agents
    setupAgents();
    // setup window
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(width, height, "mieke", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    //gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    while (!glfwWindowShouldClose(window)) {
        auto start = std::chrono::high_resolution_clock::now();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(-5.0, 5.0, -5.0, 5.0, 0.0, 1.0);
        // here we should compute the matrix in function of the viewport dimensions
        // glTranslatef(0.0f, 0.0f, -2.0f);
        // glScalef(0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Update elements
        for (auto it = agents.begin(); it != agents.end(); ++it) {
            it->update();
        }
        // Draw elements
        for (auto it = agents.begin(); it != agents.end(); ++it) {
            it->draw();
        }
        // End Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
        // Sleep
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::this_thread::sleep_for(cycle - duration);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}