#define _CRT_SECURE_NO_DEPRECATE
#include "functions.h"
#define SCREENSHOT_MAX_FILENAME 256

// GLubyte pixels[1920 * 1080 * 3];
static unsigned int nframes = 0;
// Function called when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// static unsigned int pixels[2073600];

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
    GLError(int program1 = glCreateProgram());
    GLError(int backgroundProgram = glCreateProgram());

    // Telling GLFW we want to call this function on every window resize by registering it
    unsigned int fragmentShaderID = createShader("fragment");
    unsigned int vertexShaderID = createShader("vertex");
    unsigned int vertexShaderID1 = createShader("vertex", "background");

    GLError(glAttachShader(program1, vertexShaderID));
    GLError(glAttachShader(program1, fragmentShaderID));
    GLError(glLinkProgram(program1));

    GLError(glAttachShader(backgroundProgram, vertexShaderID1));
    GLError(glAttachShader(backgroundProgram, fragmentShaderID));
    GLError(glLinkProgram(backgroundProgram));

    int success;
    char infoLog[512];

    GLError(glGetProgramiv(program1, GL_LINK_STATUS, &success));
    if (!success)
    {
        glGetProgramInfoLog(program1, 512, NULL, infoLog);
        std::cout << "[OpenGL Error]: linking compilation failed\n" << infoLog << std::endl;
    }
    
    GLError(glGetProgramiv(backgroundProgram, GL_LINK_STATUS, &success));
    if (!success)
    {
        glGetProgramInfoLog(backgroundProgram, 512, NULL, infoLog);
        std::cout << "[OpenGL Error]: linking compilation failed\n" << infoLog << std::endl;
    }

    // Clearing Shader memory
    GLError(glDeleteShader(vertexShaderID));
    GLError(glDeleteShader(fragmentShaderID));

    // Vertecies of shape
    float backVert[] = {
        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, -1.0f,
    };

    unsigned int backInd[] = {
        0, 1, 2,
        0, 2, 3
    };

    float Fvertices[] = {
     0.0f,      0.5f,       0.0f,           
     0.1875f,   0.5f,       0.0f,
     0.5f,      0.5f,       0.0f,
     0.5f,      0.3125f,    0.0f,
     0.1875f,   0.3125f,    0.0f,
     0.1875f,   0.0f,       0.0f,
     0.375f,    0.0f,       0.0f,
     0.375f,    -0.1875f,   0.0f,
     0.1875f,   -0.1875f,   0.0f,
     0.1875f,   -0.5f,      0.0f,
     0.0f,      -0.5f,      0.0f,
     
     0.0f,      0.5f,       0.1f,
     0.1875f,   0.5f,       0.1f,
     0.5f,      0.5f,       0.1f,
     0.5f,      0.3125f,    0.1f,
     0.1875f,   0.3125f,    0.1f,
     0.1875f,   0.0f,       0.1f,
     0.375f,    0.0f,       0.1f,
     0.375f,    -0.1875f,   0.1f,
     0.1875f,   -0.1875f,   0.1f,
     0.1875f,   -0.5f,      0.1f,
     0.0f,      -0.5f,      0.1f,
    };

    unsigned int Findices[] = {
        0, 1, 10,
        1, 2, 3,
        6, 7, 8,
        1, 3, 4,
        1, 9, 10,
        5, 6, 8,

        11, 12, 21,
        12, 13, 14,
        17, 18, 19,
        12, 14, 15,
        12, 20, 21,
        16, 17, 19,

        0, 11, 12,
        0, 12, 1,
        1, 12, 13,
        1, 13, 2,
        2, 13, 14,
        2, 14, 3,
        3, 14, 15,
        3, 15, 4,
        4, 15, 16,
        4, 16, 5,
        5, 16, 17,
        5, 17, 6,
        6, 17, 18,
        6, 18, 7,
        7, 18, 19,
        7, 19, 8,
        8, 19, 20,
        8, 20, 9,
        9, 20, 21,
        9, 21, 10,
    };

    // Create Vertex Buffer Object and Vertex Array Object
    unsigned int VBOs[2], VAOs[2], EBO[2];
    GLError(glGenVertexArrays(2, VAOs)); // we can also generate multiple VAOs or buffers at the same time
    GLError(glGenBuffers(2, VBOs));
    GLError(glGenBuffers(2, EBO));

    GLError(glBindVertexArray(VAOs[1]));                                                     // Selecting Vertex Array Object to modify.
    GLError(glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]));                                            // Selecting which Vertex Buffer Object to modify
    GLError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]));
    GLError(glBufferData(GL_ARRAY_BUFFER, sizeof(Fvertices), Fvertices, GL_STATIC_DRAW));      // Filling buffer with data.
    GLError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Findices), Findices, GL_STATIC_DRAW));
    GLError(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));   // Telling OpenGL how to read in the data.
    GLError(glEnableVertexAttribArray(0));

    GLError(glBindVertexArray(VAOs[0]));                                                     // Selecting Vertex Array Object to modify.
    GLError(glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]));                                            // Selecting which Vertex Buffer Object to modify
    GLError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]));
    GLError(glBufferData(GL_ARRAY_BUFFER, sizeof(backVert), backVert, GL_STATIC_DRAW));      // Filling buffer with data.    
    GLError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(backInd), backInd, GL_STATIC_DRAW));
    GLError(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));   // Telling OpenGL how to read in the data.  
    GLError(glEnableVertexAttribArray(0));                                                   // Will enable fetching by searching for attrib_index in VAO    

    // Unbinding the VBOs
    GLError(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLError(glBindVertexArray(0));

    // Main loop
    float i = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        // rendering here
        GLError(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLError(glClear(GL_COLOR_BUFFER_BIT));

        float iTime = (float) glfwGetTime();

        int gl_width, gl_height;
        glfwGetWindowSize(window, &gl_width, &gl_height);

        const float FPS = 60.0f;
        const int SECONDS = 5;

        i += 1 / FPS;

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, iTime, glm::vec3(1.0f, 0.0f, 1.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)gl_width / (float)gl_height, 0.1f, 100.0f);
        glm::mat4 PVM = projection * view * model;

        GLError(unsigned int res1 = glGetUniformLocation(program1, "res"));
        GLError(unsigned int iTime1 = glGetUniformLocation(program1, "iTime"));
        GLError(unsigned int mag1 = glGetUniformLocation(program1, "mag"));
        GLError(unsigned int PVM1 = glGetUniformLocation(program1, "PVM"));

        GLError(glUseProgram(program1));                                   

        GLError(glUniform2f(res1, (float)gl_width, (float)gl_height));
        GLError(glUniform1f(iTime1, iTime));
        GLError(glUniform1f(mag1, 0));
        GLError(glUniformMatrix4fv(PVM1, 1, GL_FALSE, &PVM[0][0]));

        GLError(glBindVertexArray(VAOs[1]));                                                            
        GLError(glDrawElements(GL_TRIANGLES, sizeof(Findices) / sizeof(Findices[0]), GL_UNSIGNED_INT, 0));

        //GLError(glReadBuffer(GL_FRONT));
        //GLError(glReadPixels(0, 0, gl_width, gl_height, GL_RGB, GL_UNSIGNED_BYTE, pixels));

        /*std::ofstream img("frames/frame" + std::to_string(nframes) + ".ppm");
        img << "P3" << std::endl;
        img << (int)gl_width << ' ' << (int)gl_height << std::endl;
        img << "255" << std::endl;*/

        //for (int y = gl_height; y >= 0; y--)
        //    for (int x = 0; x < gl_width; x++)
        //        img << (int)pixels[(x + y * gl_width) * 3] << " " << (int)pixels[(x + y * gl_width) * 3 + 1] << " " << (int)pixels[(x + y * gl_width) * 3 + 2] << std::endl;

        //// glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
        //img.close();
        //if (nframes == FPS * SECONDS)
        // break;
        //nframes++;
    }

    // Clearing memory
    GLError(glDeleteVertexArrays(2, VAOs));
    GLError(glDeleteBuffers(2, VBOs));
    GLError(glDeleteProgram(program1));
    GLError(glDeleteProgram(backgroundProgram));

    // Close window
    glfwTerminate();
    return 0;
}
