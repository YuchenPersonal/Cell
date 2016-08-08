#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <math/math.h>
#include <cell/ProjectLinkTest.h>
#include <cell/shading/shader.h>
#include <cell/mesh/quad.h>
#include <cell/mesh/line_strip.h>
#include <utility/logging/log.h>

/* NOTE(Joey):

  This is a demo program set up to demonstrate the graphic fidelity
  of Cell and demonstrates one way of configuring and using Cell
  from a developer's perspective.

  The demo program also uses Dear IMGUI to add a basic layer of 
  user input interaction.

*/
int main(int argc, char *argv[])
{
    /* NOTE(Joey): 

      Initialize the windowing library.

      Cell is a graphics engine independent of a windowing system. 
      This is to keep Cell cross-platform and independent of any
      windowing system developers prefer to use. Cell does expect
      an OpenGL context set up before initializing Cell.

      Here we use GLFW(3) to initialize a window, initialize an
      OpenGL context and in this case also initialize all OpenGL
      function pointers. Note that loading function pointers is
      something we want Cell to manage in the future as well.

    */
    Log::Message("Initializing GLFW");
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, true);
    
        GLFWwindow *window = glfwCreateWindow(1280, 720, "Cell", nullptr, nullptr);
        if (window == nullptr)
        {
            // TODO(Joey): logging/diagnostics
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
    Log::Message("GLFW initialized");

    // TODO(Joey): initialize Cell here

    // NOTE(Joey): load OpenGL function pointers
    Log::Message("Initializing GLEW");
        glewExperimental = true;
        if (glewInit() != GLEW_OK)
        {
            // TODO(Joey): logging/diagnostics
            return -1;
        }
    Log::Message("GLEW initialized");

    // NOTE(Joey): configure default OpenGL state
    Log::Message("Configuring OpenGL");
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.4f, 0.1f, 0.1f, 1.0f);
    Log::Message("OpenGL configured");


    // NOTE(Joey): custom test code
    math::mat3 test;
    math::vec3 test2;
    // NOTE(Joey): check if linking Cell static library worked properly
    int linktest = SuperCalcFunc(1337);
    Log::Message("Testing Cell Linkage: " + std::to_string(linktest), LOG_DEBUG);

    Cell::Shader testShader("shaders/test.vs", "shaders/test.fs");
    Cell::Quad quad;
    Cell::LineStrip lineStrip(0.5f, 32);

    Log::Display();
    Log::Clear();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);


        // TODO(Joey): do we need to pass input to Cell?
        // TODO(Joey): fill the renderer's command buffer with interesting polygons
        // TODO(Joey): call Cell's renderer

        // NOTE(Joey): simple quad test code to run shader tests on
        testShader.Use();
        glBindVertexArray(quad.m_VAO); // NOTE(Joey): placeholder for now; will be managed by renderer eventually
            glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.Positions.size());
        glBindVertexArray(0);

        glBindVertexArray(lineStrip.m_VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, lineStrip.Positions.size());
        glBindVertexArray(0);

        // NOTE(Joey): display log messages / diagnostics
        Log::Display();
        Log::Clear();

        glfwSwapBuffers(window);
    }

    // TODO(Joey): clean up Cell

    glfwTerminate();

    return 0;
}