#include "Input.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_RELEASE)
		{
			glfwTerminate();
			return;
		}
	default:
		break;
	}
}

void MousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	glm::vec3 dir(cos(ypos / 120.f) * sin(xpos / 120.f), sin(ypos / 120.f), cos(ypos / 120.f) * cos(xpos / 120.f));
	glm::vec3 right(sin(xpos / 120.f - 3.14159f / 2.f), 0.f, cos(xpos / 120.f - 3.14159f / 2.f));
	glm::vec3 up = glm::cross(right, dir);
	extern glm::mat4 v;
	v = glm::lookAt(-5.f * dir, dir, up);
}