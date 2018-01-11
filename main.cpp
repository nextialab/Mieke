#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "world.hpp"
#include "master.hpp"
#include "agent.hpp"

static void error_callback(int error, const char* description) {
    std::cerr << error << " " << description;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main() {
    // setup window
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(World::width(), World::height(), "mieke", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    std::chrono::milliseconds cycle{World::fps()}; // 20 FPS
    Master master;
    master.generateAgents();
    while (!glfwWindowShouldClose(window)) {
        auto start = std::chrono::high_resolution_clock::now();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(0.0, World::width(), World::height(), 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        // Update elements
        master.update();
        // Draw elements
        master.draw();
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