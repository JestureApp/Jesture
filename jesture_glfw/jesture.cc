#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "glad.h"
#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>
#include "platform_folders.h"

// Nuklear feature flags
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

// Nuklear rendering limits
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

// OpenGL Version
#define OPENGL_MAJOR 3
#define OPENGL_MINOR 3

// Global state
struct nk_glfw glfw = {0};
struct nk_context* context;
int width, height;
int first_menu = -1, second_menu = -1;

using namespace std;

// Mockup UI data
auto config_string = R"(
{
    "gestures": [
        {
            "name": "Peace",
            "finger1": false,
            "finger2": true,
            "finger3": true,
            "finger4": false,
            "finger5": false
        },
        {
            "name": "Point",
            "finger1": true,
            "finger2": true,
            "finger3": false,
            "finger4": false,
            "finger5": false
        },
        {
            "name": "Stop",
            "finger1": true,
            "finger2": true,
            "finger3": true,
            "finger4": true,
            "finger5": true
        }
    ],
    "preferences": {
        "recognizer_accuracy": 1,
        "camera": 0
    }
}
)";

struct GestureParameters {
    string name;
    bool finger1;
    bool finger2;
    bool finger3;
    bool finger4;
    bool finger5;
};
vector<GestureParameters> gestures;
map<string, int> preferences;

// Draw call
static void draw() {
    // Begin new frame buffer for nuklear--store for now and draw later
    nk_glfw3_new_frame(&glfw);
    
    // Open config
    if (nk_begin(context, "HUD", nk_rect(0, 0, 300, 64), NK_WINDOW_NO_SCROLLBAR)) {
        nk_layout_row_dynamic(context, 32, 2);
        if(nk_button_label(context, "Gestures")) {
            if (first_menu == 0) {
                first_menu = -1;
            } else {
                first_menu = 0;
            }
            second_menu = -1;
        }
        if(nk_button_label(context, "Settings")) {
            if (first_menu == 1) {
                first_menu = -1;
            } else {
                first_menu = 1;
            }
            second_menu = -1;
        }
        nk_end(context);
    }
    
    // Gesture menu
    if (first_menu == 0 && nk_begin(context, "Gesture List", nk_rect(0, 64, 300, height - 64), NK_WINDOW_BORDER)) {
        nk_layout_row_dynamic(context, 600, 1);
        if (nk_group_begin(context, "column1", NK_WINDOW_BORDER)) {
            for (int i = 0; i < gestures.size(); i++) {
                nk_layout_row_dynamic(context, 30, 1);
                if(nk_button_label(context, gestures[i].name.c_str())) {
                    if (second_menu == i) {
                        second_menu = -1;
                    } else {
                        second_menu = i;
                    }
                }
            }
            nk_group_end(context);
        }
        nk_layout_row_dynamic(context, 30, 1);
        if (nk_button_label(context, "Save")) {
            
        }
        nk_end(context);
    }
    
    // Settings menu
    if (first_menu == 1 && nk_begin(context, "Settings", nk_rect(0, 64, 300, height - 64), NK_WINDOW_BORDER)) {
        nk_layout_row_dynamic(context, 700, 1);
        if (nk_group_begin(context, "column1", NK_WINDOW_BORDER)) {
            nk_layout_row_dynamic(context, 30, 1);
            nk_label(context, "Accuracy", NK_TEXT_LEFT);
            nk_layout_row_dynamic(context, 30, 1);
            nk_label(context, "Camera", NK_TEXT_LEFT);
            nk_group_end(context);
        }
        nk_end(context);
    }
    
    // Gesture Inspector menu
    if (second_menu > -1 && nk_begin(context, "Gesture Inspector", nk_rect(300, 64, 300, height - 64), NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {
        nk_layout_row_dynamic(context, 30, 2);
        nk_label(context, "Name:", NK_TEXT_LEFT);
        nk_label(context, gestures[second_menu].name.c_str(), NK_TEXT_RIGHT);
        nk_end(context);
    }
    
    // Draw step
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
        * with blending, scissor, face culling, depth test and viewport and
        * defaults everything back into a default state.
        * Make sure to either a.) save and restore or b.) reset your own state after
        * rendering the UI. */
    // Draw Nuklear UI
    nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}



// Find config JSON file and load into global state
static void read_config() {
    auto config = nlohmann::json::parse(config_string);
    // Initialize Mockup data
    for (auto& gesture : config["gestures"]) {
        GestureParameters parameters;
        parameters.name = gesture["name"];
        parameters.finger1 = gesture["finger1"];
        parameters.finger2 = gesture["finger2"];
        parameters.finger3 = gesture["finger3"];
        parameters.finger4 = gesture["finger4"];
        parameters.finger5 = gesture["finger5"];
        gestures.push_back(parameters);
    }
    
    for (auto& [preference, value]: config["preferences"].items()) {
        preferences[preference] = value;
    }
}



// GLFW Callbacks
static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

static void resize_callback(GLFWwindow* window, int new_width, int new_height) {
    // Keep refreshing even while resizing the window
    width = new_width; height = new_height;
    glViewport(0, 0, width, height);
    draw();
    glfwSwapBuffers(window);
}
static void scroll_input(GLFWwindow* window, double _, double yoff) {
    nk_input_scroll((struct nk_context*) glfwGetWindowUserPointer(window), nk_vec2(0, (float) yoff));
}


int main(int argc, char** argv) {
    // Initialize GLFW
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) return EXIT_FAILURE;
    
    // Tell GLFW what we want for the OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    // Create window
    static GLFWwindow* window = glfwCreateWindow(1280, 720, "Jesture", nullptr, nullptr);
    if (!window) return EXIT_FAILURE;
    
    // Load OpenGL extensions with glad
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) return EXIT_FAILURE;
    
    // Set window width and height
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    
    // Minimum window size and aspect ratio constraint
    glfwSetWindowSizeLimits(window, 640, 360, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowAspectRatio(window, width, height);
    
    glfwSetScrollCallback(window, scroll_input);
    
    // Set OpenGL clear color
    glClearColor(0, 0, 0, 0);
    
    // Initialize nuklear context
    context = nk_glfw3_init(&glfw, window, NK_GLFW3_INSTALL_CALLBACKS);
    
    // Oversample font to reduce blurriness
    struct nk_font_config config = nk_font_config(0);
    config.oversample_h = 6;
    config.oversample_v = 6;
    
    // Create font atlas, load into context
    nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);
    struct nk_font *regular = nk_font_atlas_add_from_file(atlas, "third_party/Roboto-Regular.ttf", 20, &config);
    nk_glfw3_font_stash_end(&glfw);
    if(!regular) {
        fprintf(stderr, "Failed to load font.\n");
    } else {
        nk_style_set_font(context, &regular->handle);
    }
    
    // Read app config from file
    read_config();
    
    // Event loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        draw();
        glfwSwapBuffers(window);
    }
    
    // Clean up and exit
    nk_glfw3_shutdown(&glfw);
    glfwTerminate();
    return EXIT_SUCCESS;
}