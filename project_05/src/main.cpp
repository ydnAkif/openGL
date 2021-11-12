#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//vertex shader kaynak kodu
const char *vssource = "#version 330 core\nlayout(location = 0) in vec3 inPosition; void main() {gl_Position = vec4(inPosition, 1.0);}";
//fragment shader kaynak kodu
const char *fssource = "#version 330 core\nout vec4 fragColor;void main(){fragColor = vec4(0.7f, 0.7f, 0.0f, 1.0f);}";

//noktalara ait koordinat bilgileri.
float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f, -0.5f, 0.0f,  // right
    0.0f, 0.5f, 0.0f    // top
};

//OpenGL nesnelerinin id değerlerini tutacak olan değişkenler
unsigned int fragmentShader;
unsigned int vertexShader;
unsigned int shaderProgram;
unsigned int VBO;
unsigned int VAO;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //vertex shader oluşsturuluyor
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vssource, NULL);
    glCompileShader(vertexShader);

    //Fragment Shader Oluşturuluyor
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fssource, NULL);
    glCompileShader(fragmentShader);

    //Program nesnesi oluşturuluyor ve shader nesneleri yükleniyor
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //vertex array object oluşturuluyor
    glGenVertexArrays(1, &VAO);
    //vertex buffer object oluşuruluyor
    glGenBuffers(1, &VBO);

    //vertex array object aktif edildi.
    glBindVertexArray(VAO);
    //vertex buffer nesnesi aktif edildi.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //vertex buffer'a nokta bilgileri yollanıyor
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //gönderilen vertex'e ait özellikler etiketleniyor
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    //özellik  etiket i aktif ediliyor.
    glEnableVertexAttribArray(0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        //oluşturulacak resim başlangıç rengine boyanıyor
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        glUseProgram(shaderProgram);
        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}