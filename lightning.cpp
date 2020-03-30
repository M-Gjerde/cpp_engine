//
// Created by magnus on 3/27/20.
//

// Include standard headers
#include<iostream>

#define STB_IMAGE_IMPLEMENTATION

#include "common/stb_image.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "common/shader.h"
#include "common/Camera.h"
#include "common/Objects.h"

//Prottotypes
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

//Screen
int SCR_WIDTH = 1000;
int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//Steady time frame related
float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //register callback function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    //Load shaders
    Shader shader("../shaders/light_vertex.shader", "../shaders/light_fragment.shader");

    //LightCubeShader
    Shader light_shader("../shaders/light_vertex.shader", "../shaders/fragment.shader");

    //Load objects from helper file
    Objects objects;
    objects.generateCube();
    objects.cubeIndices();
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, objects.vertices.size() * sizeof(objects.vertices), &objects.vertices[0], GL_STATIC_DRAW);

    // 3. copy our index array in a element buffer for OpenGL to use

    //unsigned short indices[]={0, 1, 2, 2, 3, 0};
    std::vector<GLushort> indices;

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);

    std::cout << objects.vertices[0].x << std::endl;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(GLushort),
            &indices[0],
            GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    unsigned int lightVAO, lightVBO;
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, objects.vertices.size() * 3 * sizeof(float), &objects.vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Calculate normal vectors from cube vertices




    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);


        shader.use();
        glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
        shader.setVec3("objectColor", objectColor);
        shader.setVec3("lightColor", lightColor);
        shader.setMat4("model", glm::mat4(1.0f));
        shader.setMat4("view", camera.getViewMatrix());
        shader.setMat4("projection",
                       glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                        100.0f));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        light_shader.use();
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, glm::vec3(-5.0f, 0.0f, -5.0f));
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        light_shader.setMat4("model", lightModel);
        light_shader.setMat4("view", camera.getViewMatrix());
        light_shader.setMat4("projection",
                             glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                              100.0f));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, objects.vertices.size());

        shader.use();
        lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, glm::vec3(-3.5f, 0.0f, -3.5f));
        lightModel = glm::scale(lightModel, glm::vec3(0.1f));
        shader.setMat4("model", lightModel);
        shader.setMat4("view", camera.getViewMatrix());
        shader.setMat4("projection",
                       glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                        100.0f));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, objects.vertices.size());


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);

}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.processMouseScroll(yoffset);
}