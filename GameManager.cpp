#include "GameManager.h"

GameManager::GameManager()
{
	_window = NULL;
}

int GameManager::Initilise()
{
	if (!glfwInit())
		return -1;

	_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!_window || _window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(_window);

	if (glewInit() != GLEW_OK) {
		return -1;
	}

	return 1;
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// TODO: Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "failed to compile" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int _program = glCreateProgram();
	unsigned int _vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int _fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(_program, _vs);
	glAttachShader(_program, _fs);
	glLinkProgram(_program);
	glValidateProgram(_program);

	glDeleteShader(_vs);
	glDeleteShader(_fs);

	return _program;
}

void GameManager::Run()
{
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[6] = {
		-0.1f, -0.1f, 
		 0.0f, 0.1f, 
		 0.1f, -0.1f
	}; 

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	std::string vertexShader = 
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"}\n";

	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(_window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(_window);
		
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}
