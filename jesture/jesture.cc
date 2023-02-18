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

// Nuklear feature flags
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
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
float aspect_ratio;



// GLFW Callbacks
static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

static void resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    aspect_ratio = width / (float) height;
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
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    aspect_ratio = width / (float) height;
    glfwSetFramebufferSizeCallback(window, resize_callback);
    
    // Initialize nuklear context
    struct nk_glfw nuklear_glfw = {0};
    struct nk_context* context = nk_glfw3_init(&nuklear_glfw, window, NK_GLFW3_INSTALL_CALLBACKS);
    
    // Create font atlas
    {
        struct nk_font_atlas *atlas;
        nk_glfw3_font_stash_begin(&nuklear_glfw, &atlas);
        struct nk_font *regular = nk_font_atlas_add_from_file(atlas, "./regular.ttf", 14, 0);
        nk_glfw3_font_stash_end(&nuklear_glfw);
        if(!regular) {
            fprintf(stderr, "Failed to load font.\n");
        } else {
            nk_style_set_font(context, &regular->handle);
        }
    }
    
    /*#ifdef INCLUDE_STYLE
    #ifdef STYLE_WHITE
    set_style(context, THEME_WHITE);
    #elif defined(STYLE_RED)
    set_style(context, THEME_RED);
    #elif defined(STYLE_BLUE)
    set_style(context, THEME_BLUE);
    #elif defined(STYLE_DARK)
    set_style(context, THEME_DARK);
    #endif*/
    
    nk_colorf bg;
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        nk_glfw3_new_frame(&nuklear_glfw);
        
        if (nk_begin(context, "Demo", nk_rect(50, 50, 230, 250),
            NK_WINDOW_BORDER|NK_WINDOW_TITLE))
        {
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
            nk_property_int(context, "Compression:", 0, &property, 100, 10, 1);

            nk_layout_row_dynamic(context, 20, 1);
            nk_label(context, "background:", NK_TEXT_LEFT);
            nk_layout_row_dynamic(context, 25, 1);
            if (nk_combo_begin_color(context, nk_rgb_cf(bg), nk_vec2(nk_widget_width(context),400))) {
                nk_layout_row_dynamic(context, 120, 1);
                bg = nk_color_picker(context, bg, NK_RGBA);
                nk_layout_row_dynamic(context, 25, 1);
                bg.r = nk_propertyf(context, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
                bg.g = nk_propertyf(context, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
                bg.b = nk_propertyf(context, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
                bg.a = nk_propertyf(context, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
                nk_combo_end(context);
            }
        }
        nk_end(context);
        
        
        /* Draw */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_glfw3_render(&nuklear_glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(window);
    }
    
    nk_glfw3_shutdown(&nuklear_glfw);
    glfwTerminate();
    return EXIT_SUCCESS;
}