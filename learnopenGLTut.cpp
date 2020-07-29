#include "functions.h"

// Function called when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Proccesses the input from window
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Makes the current window
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    GLError(int program_red = glCreateProgram());
    GLError(int program_white = glCreateProgram());

    // Telling GLFW we want to call this function on every window resize by registering it
    unsigned int fragmentShaderRedID = createShader("fragment", "dark_red");
    unsigned int fragmentShaderWhiteID = createShader("fragment");
    unsigned int vertexShaderID = createShader("vertex");

    GLError(glAttachShader(program_red, vertexShaderID));
    GLError(glAttachShader(program_red, fragmentShaderRedID));

    GLError(glAttachShader(program_white, vertexShaderID));
    GLError(glAttachShader(program_white, fragmentShaderWhiteID));

    GLError(glLinkProgram(program_red));
    int  success;
    char infoLog[512];
    GLError(glGetProgramiv(program_red, GL_LINK_STATUS, &success));
    if (!success)
    {
        glGetProgramInfoLog(program_red, 512, NULL, infoLog);
        std::cout << "[OpenGL Error]: linking compilation failed\n" << infoLog << std::endl;
    }

    GLError(glLinkProgram(program_white));
    GLError(glGetProgramiv(program_white, GL_LINK_STATUS, &success));
    if (!success)
    {
        glGetProgramInfoLog(program_white, 512, NULL, infoLog);
        std::cout << "[OpenGL Error]: linking compilation failed\n" << infoLog << std::endl;
    }

    // Clearing Shader memory
    GLError(glDeleteShader(vertexShaderID));
    GLError(glDeleteShader(fragmentShaderRedID));
    GLError(glDeleteShader(fragmentShaderWhiteID));

    // Vertecies of shape
    float vertices[] = {
     0.0f,      0.5f,
     0.1875f,   0.5f,
     0.5f,      0.5f,
     0.5f,      0.3125f,
     0.1875f,   0.3125f,
     0.1875f,   0.0f,
     0.375f,    0.0f,
     0.375f,    -0.1875f,
     0.1875f,   -0.1875f,
     0.1875f,   -0.5f,
     0.0f,      -0.5f,
    };

    unsigned int red_indices[] = {
        0, 1, 10,
        1, 2, 3,
        6, 7, 8
    };
    unsigned int white_indices[] = {
        1, 3, 4,
        1, 9, 10,
        5, 6, 8
    };

    // Create Vertex Buffer Object and Vertex Array Object
    unsigned int VBOs, VAOs[2], EBO[2];
    GLError(glGenVertexArrays(2, VAOs)); // we can also generate multiple VAOs or buffers at the same time
    GLError(glGenBuffers(1, &VBOs));
    GLError(glGenBuffers(2, EBO));

    GLError(glBindVertexArray(VAOs[0]));                                                     // Selecting Vertex Array Object to modify.
    GLError(glBindBuffer(GL_ARRAY_BUFFER, VBOs));                                            // Selecting which Vertex Buffer Object to modify
    GLError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]));
    GLError(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));      // Filling buffer with data.
    GLError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(red_indices), red_indices, GL_STATIC_DRAW));
    GLError(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));   // Telling OpenGL how to read in the data.
    GLError(glEnableVertexAttribArray(0));

    GLError(glBindVertexArray(VAOs[1]));                                                     // Selecting Vertex Array Object to modify.
    GLError(glBindBuffer(GL_ARRAY_BUFFER, VBOs));                                            // Selecting which Vertex Buffer Object to modify
    GLError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]));
    GLError(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));      // Filling buffer with data.    
    GLError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(white_indices), white_indices, GL_STATIC_DRAW));
    GLError(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));   // Telling OpenGL how to read in the data.  
    GLError(glEnableVertexAttribArray(0));                                                   // Will enable fetching by searching for attrib_index in VAO    

    // Unbinding the VBOs
    GLError(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLError(glBindVertexArray(0));

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        // rendering here
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float redValue = (sin(timeValue) / 2.0f) + 0.5f;

        int red_frag_color = glGetUniformLocation(program_red, "color");
        GLError(glUseProgram(program_red));                                                                      // What program to show
        glUniform4f(red_frag_color, redValue, 0.0f, 0.0f, 1.0f);
        GLError(glBindVertexArray(VAOs[0]));                                                                     // Choosing the setting to draw in.
        GLError(glDrawElements(GL_TRIANGLES, sizeof(red_indices) / sizeof(red_indices[0]), GL_UNSIGNED_INT, 0)); // Drawing triangle
        
        int white_frag_color = glGetUniformLocation(program_white, "color");
        GLError(glUseProgram(program_white));                                                                      // What program to show
        glUniform4f(white_frag_color, 1 - redValue, 0.0f, 0.0f, 1.0f);
        GLError(glUseProgram(program_white));
        GLError(glBindVertexArray(VAOs[1]));
        GLError(glDrawElements(GL_TRIANGLES, sizeof(white_indices) / sizeof(white_indices[0]), GL_UNSIGNED_INT, 0));

        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clearing memory
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, &VBOs);
    glDeleteProgram(program_red);
    glDeleteProgram(program_white);

    // Close window
    glfwTerminate();
    return 0;
}