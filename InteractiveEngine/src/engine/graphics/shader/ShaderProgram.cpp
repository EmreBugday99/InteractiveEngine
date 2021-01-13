#include <GL/glew.h>
#include <iostream>
#include <glm.hpp>
#include "ShaderProgram.h"
#include <gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram()
{
	// Creating a shader program.
	ProgramId = glCreateProgram();
	std::cout << "SHADER CONSTRUCTED: " << ProgramId << std::endl;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(ProgramId);
}

void ShaderProgram::LinkProgram()
{
	glLinkProgram(ProgramId);
	glValidateProgram(ProgramId);

	if (Shaders.empty() == true) return;
	for (unsigned int shader : Shaders)
	{
		glDeleteShader(shader);
	}
	Shaders.clear();
}

void ShaderProgram::UseProgram() { glUseProgram(ProgramId); }
void ShaderProgram::UnbindProgram() { glUseProgram(0); }

const int ShaderProgram::SetUniformData(std::string uniformName, glm::vec4& uniformData) const
{
	// Getting the uniform location via uniform's name from the specified shader program.
	const int location = glGetUniformLocation(ProgramId, uniformName.c_str());
	// Returning early so that we don't try to write to an invalid uniform location.
	if (location == -1)
		return location;

	// Updating the value of the specified uniform.
	glUniform4f(location, uniformData.x, uniformData.y, uniformData.z, uniformData.w);
	return location;
}

const int ShaderProgram::SetUniformData(std::string uniformName, glm::vec3& uniformData) const
{
	// Getting the uniform location via uniform's name from the specified shader program.
	const int location = glGetUniformLocation(ProgramId, uniformName.c_str());
	// Returning early so that we don't try to write to an invalid uniform location.
	if (location == -1)
		return location;

	// Updating the value of the specified uniform.
	glUniform3f(location, uniformData.x, uniformData.y, uniformData.z);
	return location;
}

const int ShaderProgram::SetUniformData(std::string uniformName, glm::vec2& uniformData) const
{
	// Getting the uniform location via uniform's name from the specified shader program.
	const int location = glGetUniformLocation(ProgramId, uniformName.c_str());
	// Returning early so that we don't try to write to an invalid uniform location.
	if (location == -1)
		return location;

	// Updating the value of the specified uniform.
	glUniform2f(location, uniformData.x, uniformData.y);
	return location;
}

const int ShaderProgram::SetUniformData(std::string uniformName, float& uniformData) const
{
	// Getting the uniform location via uniform's name from the specified shader program.
	const int location = glGetUniformLocation(ProgramId, uniformName.c_str());
	// Returning early so that we don't try to write to an invalid uniform location.
	if (location == -1)
		return location;

	// Updating the value of the specified uniform.
	glUniform1f(location, uniformData);
	return location;
}

const int ShaderProgram::SetUniformData(std::string uniformName, bool flip, glm::mat4 uniformMatrix) const
{
	// Getting the uniform location via uniform's name from the specified shader program.
	const int location = glGetUniformLocation(ProgramId, uniformName.c_str());
	// Returning early so that we don't try to write to an invalid uniform location.
	if (location == -1)
		return location;

	// Updating the value of the specified uniform.
	glUniformMatrix4fv(location, 1, flip, glm::value_ptr(uniformMatrix));
	return location;
}

unsigned ShaderProgram::GetProgramId() const { return ProgramId; }

void ShaderProgram::AttachShader(unsigned int type, std::string& shaderCode)
{
	const unsigned int shaderId = CompileShader(type, shaderCode);

	if (shaderId == 0)
	{
		std::cerr << "Error: Shader Failed To Compile!" << std::endl;
	}

	// Attaching this shader to this Shader Program.
	glAttachShader(ProgramId, shaderId);
	Shaders.emplace_back(shaderId);
}

const unsigned int ShaderProgram::CompileShader(unsigned int type, const std::string& shaderCode)
{
	// Creating a shader with the specified type.
	const unsigned int shaderId = glCreateShader(type);
	const char* code = shaderCode.c_str();

	// Setting the source code of the specified shader(shaderId).
	glShaderSource(shaderId, 1, &code, nullptr);
	// Compiling the source code stored in the shader(shaderId).
	glCompileShader(shaderId);

	// Error handling.
	if (CheckCompilationError(type, shaderId) == false)
		return 0;

	return shaderId;
}

const bool ShaderProgram::CheckCompilationError(unsigned int type, unsigned int shaderId)
{
	int result;
	// Returning the parameter(GL_COMPILE_STATUS) for the specified shader(shaderId).
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;

		// Returning the parameter(GL_INFO_LOG_LENGTH) for the specified shader(shaderId).
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(alloca(length * sizeof(char)));

		// Returning the information log for the specified shader.
		glGetShaderInfoLog(shaderId, length, &length, message);

		std::cerr << "Error: Shader Compile Error!" << std::endl;

		if (type == GL_VERTEX_SHADER)
			std::cerr << "Shader Type: Vertex Shader" << std::endl;
		else if (type == GL_FRAGMENT_SHADER)
			std::cerr << "Shader Type: Fragment Shader" << std::endl;

		std::cerr << message << std::endl;

		// If the shader failed to compile it is pointless to keep it in the GPU memory.
		glDeleteShader(shaderId);

		return false;
	}

	return true;
}