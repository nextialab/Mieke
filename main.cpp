#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <random>
#include "agent.hpp"

static void error_callback(int error, const char* description) {
    std::cerr << error << " " << description;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

std::vector<Agent> agents;
std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);

void setupAgents() {
    agents.push_back(Agent(0.8f, 0.8f, 0.0f));
    agents.push_back(Agent(0.6f, 0.6f, 0.0f));
    agents.push_back(Agent(0.4f, 0.4f, 0.0f));
    agents.push_back(Agent(0.2f, 0.2f, 0.0f));
    agents.push_back(Agent(0.0f, 0.0f, 0.0f));
}

int main() {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(640, 480, "mieke", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    setupAgents();
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        // update elements
        for (auto it = agents.begin(); it != agents.end(); ++it) {
            it->update(distribution(generator), distribution(generator));
        }
        // Draw elements
        for (auto it = agents.begin(); it != agents.end(); ++it) {
            it->draw();
        }
        // End Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}