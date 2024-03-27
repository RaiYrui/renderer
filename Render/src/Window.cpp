#include "Window.h"
namespace RR {
    Window* Window::window = nullptr;
    GLFWwindow* Window::glfw_window;
    Window::Window() {
        this->glfw_window = nullptr;
        this->width = 1200;
        this->height = 900;
        this->Resize();
    }
    Window* Window::getInstance() {
        if (window == nullptr)
            window = new Window();
        return window;
    }
    bool Window::Init() {
        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
            getchar();
            return -1;
        }
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfw_window = glfwCreateWindow(width, height, "Renderer", nullptr, nullptr); // ´´½¨´°¿Ú
        if (glfw_window == nullptr)
        {
            fprintf(stderr, "Failed to open GLFW window.  \n");
            getchar();
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(glfw_window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }
        glfwSwapInterval(1);

        glViewport(0, 0, width, height);
        return true;
    }
    void Window::Resize() {
        this->gl_width = this->width / 2;
        this->gl_height = this->height * 2 / 3;
        this->Ins_width = this->width / 4;
        this->Ins_height = this->height * 2 / 3;
        this->H_width = this->width / 4;
        this->H_height = this->height * 2 / 3;
        this->R_width = this->width;
        this->R_height = this->height / 3;
    }
    void Window::Close() {
        glfwTerminate();
    }
}