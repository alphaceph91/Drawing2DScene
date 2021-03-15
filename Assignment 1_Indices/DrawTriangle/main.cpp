#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

#define USE_INDEX_BUFFER 1

#define NUM_VERTICES 54
#define NUM_INDICES 72

const unsigned int WIDTH = 720;
const unsigned int HEIGHT = 480;

int shaderProgram;
int vertexShader, fragmentShader;
int positionID, colorID;

//#define USE_INDEX_BUFFER
GLfloat vertices[] = {
	//TREE 1
		-0.6f, -0.6f, 0.0f,//0
		-0.6f, -0.4f, 0.0f,//1
		-0.4f, -0.6f, 0.0f,//2
		-0.4f, -0.4f, 0.0f,//3

		-0.7f, -0.4f, 0.0f,//4
		-0.3f, -0.4f, 0.0f,//5
		-0.5f, -0.1f, 0.0f,//6

		-0.7f, -0.1f, 0.0f,//7
		-0.3f, -0.1f, 0.0f,//8
		-0.5f, 0.2f, 0.0f,//9

		-0.7f, 0.2f, 0.0f,//10
		-0.3f, 0.2f, 0.0f,//11
		-0.5f, 0.5f, 0.0f,//12

	//TREE 2
		0.1f, -0.3f, 0.0f,//13
		0.1f, -0.1f, 0.0f,//14
		0.3f, -0.3f, 0.0f,//15
		0.3f, -0.1f, 0.0f,//16

		0.0f, -0.1f, 0.0f,//17
		0.4f, -0.1f, 0.0f,//18
		0.2f, 0.2f, 0.0f,//19

		0.0f, 0.2f, 0.0f,//20
		0.4f, 0.2f, 0.0f,//21
		0.2f, 0.5f, 0.0f,//22

		0.0f, 0.5f, 0.0f,//23
		0.4f, 0.5f, 0.0f,//24
		0.2f, 0.8f, 0.0f,//25

	//House 1
		-0.2f, 0.3f, 0.0f,//26
		-0.3f, 0.2f, 0.0f,//27
		 0.1f, 0.3f, 0.0f,//28
		 0.2f, 0.2f, 0.0f,//29

		-0.2f, 0.2f, 0.0f,//30
		-0.2f, 0.0f, 0.0f,//31
		 0.1f, 0.2f, 0.0f,//32
		 0.1f, 0.0f, 0.0f,//33

		-0.1f, 0.1f, 0.0f,//34
		-0.1f, 0.0f, 0.0f,//35
		 0.0f, 0.1f, 0.0f,//36
		 0.0f, 0.0f, 0.0f,//37

	 //House 2
		-0.5f, -0.1f, 0.0f,//38
		-0.4f, -0.1f, 0.0f,//39
		-0.4f, -0.2f, 0.0f,//40
		-0.5f, -0.2f, 0.0f,//41

		-0.5f, -0.2f, 0.0f,//42
		-0.6f, -0.3f, 0.0f,//43
		-0.2f, -0.2f, 0.0f,//44
		-0.1f, -0.3f, 0.0f,//45


		-0.2f, -0.3f, 0.0f,//46
		-0.2f, -0.5f, 0.0f,//47
		-0.5f, -0.5f, 0.0f,//48
		-0.5f, -0.3f, 0.0f,//49

		-0.3f, -0.5f, 0.0f,//50
		-0.4f, -0.5f, 0.0f,//51
		-0.4f, -0.4f, 0.0f,//52
		-0.3f, -0.4f, 0.0f,//53

};


GLfloat colors[] = {
		//TREE 1
			//Brown
			0.5f, 0.35f, 0.05f, 1.0f,
			0.5f, 0.35f, 0.05f, 1.0f,
			0.5f, 0.35f, 0.05f, 1.0f,
			0.5f, 0.35f, 0.05f, 1.0f,

			////Green
			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,

			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,

			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,

		//TREE 2
			//Brown
			0.5f, 0.35f, 0.05f, 1.0f,
			0.5f, 0.35f, 0.05f, 1.0f,
			0.5f, 0.35f, 0.05f, 1.0f,
			0.5f, 0.35f, 0.05f, 1.0f,
			//Green
			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,

			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,

			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,
			0.0f, 1.7f, 0.0f, 1.0f,

		//House 1
			//yellow
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			//blue
			0.0f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.2f, 0.8f, 1.0f,
			//red
			0.8f, 0.0f, 0.0f, 1.0f,
			0.8f, 0.0f, 0.0f, 1.0f,
			0.8f, 0.0f, 0.0f, 1.0f,
			0.8f, 0.0f, 0.0f, 1.0f,

		//House 2
			//yellow
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,

			//yellow
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,

			//blue
			0.0f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.2f, 0.8f, 1.0f,

			//red
			0.8f, 0.0f, 0.0f, 1.0f,
			0.8f, 0.0f, 0.0f, 1.0f,
			0.8f, 0.0f, 0.0f, 1.0f,
			0.8f, 0.0f, 0.0f, 1.0f,

};

GLuint indices[] = {
	0, 1, 2,
	1, 3, 2,
	4, 5, 6,
	7, 8, 9,
	10, 11, 12,
	13, 14, 15,
	14, 15, 16,
	17, 18, 19,
	20, 21, 22,
	23, 24, 25,
	26, 27, 28,
	27, 28, 29,
	30, 31, 32,
	31, 32, 33,
	34, 35, 36,
	35, 36, 37,
	38, 39, 40,
	38, 40, 41,
	42, 43, 44,
	43, 44, 45,
	46, 47, 48,
	46, 48, 49,
	50, 51, 52,
	50, 52, 53,
};


unsigned int vbo;
unsigned int vao;
unsigned int indexBufferID;

// loadFile - loads text file into char* fname
std::string loadFile(const char* fname) {
	std::ifstream file(fname);
	if (!file.is_open()) {
		std::cout << "Unable to open file " << fname << std::endl;
		exit(1);
	}

	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();

	return fileData.str();
}

int loadShaders() {

	int vlength, flength;

	std::string vertexShaderString = loadFile("colorShader.vert");
	std::string fragmentShaderString = loadFile("colorShader.frag");
	vlength = vertexShaderString.length();
	flength = fragmentShaderString.length();

	if (vertexShaderString.empty() || fragmentShaderString.empty()) {
		return -1;
	}

	// vertex shader
	const char* vertexShaderCStr = vertexShaderString.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexShaderCStr, &vlength);
	glCompileShader(vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	const char* fragmentShaderCStr = fragmentShaderString.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentShaderCStr, &flength);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void initBuffers() {

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, 7 * NUM_VERTICES * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * NUM_VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * NUM_VERTICES * sizeof(GLfloat), 4 * NUM_VERTICES * sizeof(GLfloat), colors);

#ifdef USE_INDEX_BUFFER
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUM_INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);
#endif
	positionID = glGetAttribLocation(shaderProgram, "inVertex");
	colorID = glGetAttribLocation(shaderProgram, "inColor");

	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));

	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	// uncomment this call to draw in wireframe polygons.
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// initialize

void renderScene() {
	//USE_INDEX_BUFFER
	glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, NULL);
}


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW Window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment1Indices", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	if (!loadShaders()) {
		std::cout << "Failed to initialize shaders" << std::endl;
		return -1;
	}

	initBuffers();

	// Main Loop
	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		renderScene();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}