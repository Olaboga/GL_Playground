#define GLEW_STATIC

#include "GLEW\glew.h"
#include "GLFW\GLFW_Helper.h"
#include <iostream>
#include "GLSLShader.h"
#include "Mesh.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

auto v = glm::mat4(1);
auto m = glm::mat4(1);
glm::mat4 p;

void APIENTRY DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParams)
{
	std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		std::cerr << "---    ERROR!    ---" << std::endl;
		break;
		
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "--- DEPRECATED!  ---" << std::endl;
		break;

	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "---  UNDEFINED!  ---" << std::endl;
		break;

	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "--- PORTABILITY! ---" << std::endl;
		break;

	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "--- PERFORMANCE! ---" << std::endl;
		break;

	case GL_DEBUG_TYPE_OTHER:
		std::cout << "---    OTHER!    ---" << std::endl;					 
		break;
	}
	std::cout << message << std::endl << "--------------------" << std::endl;
}

void InitShaders(GLSLShader* shader)
{
	shader->LoadFromFile(GL_VERTEX_SHADER, "shaders/shader.vert");
	shader->LoadFromFile(GL_FRAGMENT_SHADER, "shaders/shader.frag");
	shader->CreateAndLinkProgram();
	shader->Use();
	shader->AddAttribute("pos");
	shader->AddAttribute("col");
	shader->AddAttribute("nor");
	shader->AddUniform("mvp");
	shader->UnUse();
}

int main()
{
	GLFWwindow* window = InitGLFW();
	GLSLShader shader;

	glewExperimental = GL_TRUE;
	auto err = glewInit();
	if(err)
		std::cerr << err << " " << glewGetErrorString(err) << std::endl;

	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		std::cout << "Debug output avalaible." << std::endl;

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(DebugOutputCallback, nullptr);

	GLuint unusedIds = 0;
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);

	InitShaders(&shader);

	GLuint vao_id, vbo_id;
	Mesh mesh("meshes/star_nrm.obj");

	glGenVertexArrays(1, &vao_id);
	glGenBuffers(1, &vbo_id);

	glBindVertexArray(vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

	glBufferData(GL_ARRAY_BUFFER, mesh.vertCount * sizeof(Vertex), &mesh.verts[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(shader["pos"]);
	glVertexAttribPointer(shader["pos"], 3, GL_FLOAT, false, (GLsizei)sizeof(Vertex), (const GLubyte*)NULL + offsetof(Vertex, pos));

	glEnableVertexAttribArray(shader["col"]);
	glVertexAttribPointer(shader["col"], 4, GL_FLOAT, false, (GLsizei)sizeof(Vertex), (const GLubyte*)NULL + offsetof(Vertex, col));

	glEnableVertexAttribArray(shader["nor"]);
	glVertexAttribPointer(shader["nor"], 3, GL_FLOAT, false, (GLsizei)sizeof(Vertex), (const GLubyte*)NULL + offsetof(Vertex, nrm));

	glClearColor(.3f, .3f, .3f, 1.f);

	p = glm::perspective(30.f, 800.f / 600.f, .1f, 1000.f);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.Use();
		glUniformMatrix4fv(shader["mvp"], 1, GL_FALSE, glm::value_ptr(p * v * m));
		glDrawArrays(GL_TRIANGLES, 0, mesh.vertCount);
		glfwSwapBuffers(window);
		glfwPollEvents();
		shader.UnUse();
	} 

	glfwTerminate();
	return 0;
}