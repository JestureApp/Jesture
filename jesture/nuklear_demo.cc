#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include "glad.h"
#include <GLFW/glfw3.h>

#include "nuklear.h"
#include "nuklear_glfw_gl4.h"

int main(int argc, char** argv) {
    glfwInit();
    auto *window = glfwCreateWindow(1280, 720, "Test", nullptr, nullptr);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    
    glfwTerminate();
    return EXIT_SUCCESS;
}