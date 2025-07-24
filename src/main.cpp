#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include "include/camera3d.h"
#include "render.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;
static float lastX = 1280.0f / 2.0f;
static float lastY = 720.0f / 2.0f;
static bool firstMouse = true;
static bool showCursor = true;
float speed = 10.0f;

//Cube
static glm::vec3 cubePosition = {0.0f, 0.0f, 0.0f};
static glm::vec3 cubeScale = {1.0f, 1.0f, 1.0f};
static glm::vec3 cubeRotation = {0.0f, 0.0f, 0.0f};
static glm::vec3 cubeColor = {0.6f, 0.6f, 0.1f};

Camera camera;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (showCursor) return;
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;
    
    camera.processMouse(xoffset, yoffset);
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main()
{

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "example", nullptr, nullptr);
    if (window == nullptr)
        return 1;

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glfwSwapInterval(1);
    glfwSetCursorPosCallback(window, mouse_callback);

    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /*****************************GlfwPollEvents**********************************************/

        glfwPollEvents();

        static bool escPressedLastFrame = false;
        bool escPressedNow = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

        if (escPressedNow && !escPressedLastFrame)
        {
            showCursor = !showCursor;
            if (showCursor)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);
                lastX = xpos;
                lastY = ypos;
                firstMouse = true;
            }
        }

        escPressedLastFrame = escPressedNow;

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
        /*********************************CameraUpdate******************************************/

       camera.processInput(window, deltaTime, speed);

        /******************************ImGui_Frame*********************************************/

         ImGui_ImplOpenGL2_NewFrame();
         ImGui_ImplGlfw_NewFrame();
         ImGui::NewFrame();
        /*********************************ImGui_WindowDraw******************************************/

        if (1)
        {
            ImGui::Begin("Debug Info");
            ImGui::Text("Position: (%.2f, %.2f, %.2f)", camera.position.x, camera.position.y, camera.position.z);
            ImGui::Text("Yaw: %.2f", camera.yaw);
            ImGui::Text("Pitch: %2.f", camera.pitch);
            ImGui::End();
            
            ImGui::Begin("Stats");                               
            ImGui::ColorEdit3("clear color", (float*)&clear_color);

            ImGui::ColorEdit3("cube color", (float*)&cubeColor); 

            ImGui::SliderFloat3("cube position", (float*)&cubePosition, -10.0f, 10.0f);
            ImGui::SliderFloat3("cube rotation", (float*)&cubeRotation, -180.0f, 180.0f);
            ImGui::SliderFloat3("cube scale", (float*)&cubeScale, 0.1f, 5.0f);
            ImGui::SliderFloat("Camera Speed", &speed, 0.1f, 50.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();

            
        }
        /******************************Opengl_Config*********************************************/

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        
        

        /******************************Opengl_Matrix*********************************************/

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)display_w / display_h, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);


        /***************************OpenGl_DrawSection************************************************/

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePosition);
        model = glm::rotate(model, glm::radians(cubeRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(cubeRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(cubeRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, cubeScale);
        glm::mat4 mvp = projection * view * model; 

        drawCube(mvp, cubeColor);
        drawSpaceMesh();

        /******************************End_ImGuiDraw*********************************************/

        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        /********************************ShowFrame*******************************************/

        glfwSwapBuffers(window);

    }

    /******************************Clear_ImGui*********************************************/

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}