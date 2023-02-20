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

#include "glad.h"
#include <GLFW/glfw3.h>

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
int first_menu = 0, second_menu = 0;

using namespace std;

// Mockup UI data
struct GestureParameters {
    string param1;
    string param2;
    string param3;
};
map<string, GestureParameters> gestures;
GestureParameters peace_parameters, point_parameters;
const char* items[] = {
    "Item 1",
    "Item 2",
    "Item 3",
    "Item 4",
    "Item 5",
    "Item 6",
    "Item 7",
    "Item 8",
    "Item 9",
    "Item 10",
    "Item 11",
    "Item 12",
    "Item 13",
    "Item 14",
    "Item 15",
    "Item 16",
    "Item 17",
    "Item 18",
    "Item 19",
    "Item 20",
    "Item 21",
    "Item 22",
    "Item 23",
    "Item 24",
    "Item 25"
};
const char* settings[] = {
    "Setting 1",
    "Setting 2",
    "Setting 3",
    "Setting 4",
    "Setting 5",
    "Setting 6",
    "Setting 7",
    "Setting 8",
    "Setting 9",
    "Setting 10",
    "Setting 11",
    "Setting 12",
    "Setting 13",
    "Setting 14",
    "Setting 15",
    "Setting 16",
    "Setting 17",
    "Setting 18",
    "Setting 19",
    "Setting 20",
    "Setting 21",
    "Setting 22",
    "Setting 23",
    "Setting 24",
    "Setting 25"
};



// Draw call
static void draw() {
    // Begin new frame buffer for nuklear--store for now and draw later
    nk_glfw3_new_frame(&glfw);
    
    // Open config
    if (nk_begin(context, "HUD", nk_rect(0, 0, 300, 64), NK_WINDOW_NO_SCROLLBAR)) {
        nk_layout_row_dynamic(context, 32, 2);
        if(nk_button_label(context, "Gestures")) {
            if (first_menu == 1) {
                first_menu = 0;
            } else {
                first_menu = 1;
            }
            second_menu = 0;
        }
        if(nk_button_label(context, "Settings")) {
            if (first_menu == 2) {
                first_menu = 0;
            } else {
                first_menu = 2;
            }
            second_menu = 0;
        }
        nk_end(context);
    }
    
    // Gesture menu
    if (first_menu == 1 && nk_begin(context, "Gesture List", nk_rect(0, 64, 300, height - 64), NK_WINDOW_BORDER)) {
        nk_layout_row_dynamic(context, 700, 1);
        if (nk_group_begin(context, "column1", NK_WINDOW_BORDER)) {
            for (int i = 0; i < 25; i++) {
                nk_layout_row_dynamic(context, 30, 1);
                if(nk_button_label(context, items[i])) {
                    second_menu = i + 1;
                }
            }
            nk_group_end(context);
        }
        /*
        enum {EASY, HARD};
        static int op = EASY;
        static int property = 20;
        nk_layout_row_static(context, 30, 80, 1);
        if (nk_button_label(context, "button"))
            fprintf(stdout, "button pressed\n");

        nk_layout_row_dynamic(context, 30, 2);
        if (nk_option_label(context, "easy", op == EASY)) op = EASY;
        if (nk_option_label(context, "hard", op == HARD)) op = HARD;

        nk_layout_row_dynamic(context, 25, 1);
        nk_property_int(context, "Counter:", 0, &property, 100, 10, 1);*/
        nk_end(context);
    }
    
    // Settings menu
    if (first_menu == 2 && nk_begin(context, "Settings", nk_rect(0, 64, 300, height - 64), NK_WINDOW_BORDER)) {
        nk_layout_row_dynamic(context, 700, 1);
        if (nk_group_begin(context, "column1", NK_WINDOW_BORDER)) {
            for (int i = 0; i < 25; i++) {
                nk_layout_row_dynamic(context, 30, 1);
                nk_button_label(context, settings[i]);
            }
            nk_group_end(context);
        }
        nk_end(context);
    }
    
    // Gesture Inspector menu
    if (second_menu > 0 && nk_begin(context, "Gesture Inspector", nk_rect(300, 64, 300, height - 64), NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {
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
    // Initialize Mockup data
    peace_parameters.param1 = "value1";
    peace_parameters.param2 = "value2";
    peace_parameters.param3 = "value3";
    point_parameters.param1 = "value4";
    point_parameters.param2 = "value5";
    point_parameters.param3 = "value6";
    gestures["Peace"] = peace_parameters;
    gestures["Point"] = point_parameters;
    
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
    struct nk_font *regular = nk_font_atlas_add_from_file(atlas, "third_party/Roboto-Regular.ttf", 24, &config);
    nk_glfw3_font_stash_end(&glfw);
    if(!regular) {
        fprintf(stderr, "Failed to load font.\n");
    } else {
        nk_style_set_font(context, &regular->handle);
    }
    
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