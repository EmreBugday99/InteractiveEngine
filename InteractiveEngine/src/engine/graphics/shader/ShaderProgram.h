#pragma once
#include <string>
#include <vector>

class ShaderProgram
{
private:
	std::vector<unsigned int> Shaders;
	unsigned int ProgramId;

public:
	ShaderProgram();
	~ShaderProgram();

	void LinkProgram();
	void AttachShader(unsigned int type, std::string& shaderCode);
	void UseProgram();
	static void UnbindProgram();
	/// <summary>
	/// Sets the uniform data of the specified uniform.
	/// </summary>
	/// <returns>Uniform location.</returns>
	const int SetUniformData(std::string uniformName, glm::vec4& uniformData) const;
	/// <summary>
	/// Sets the uniform data of the specified uniform.
	/// </summary>
	/// <returns>Uniform location.</returns>
	const int SetUniformData(std::string uniformName, glm::vec3& uniformData) const;
	/// <summary>
	/// Sets the uniform data of the specified uniform.
	/// </summary>
	/// <returns>Uniform location.</returns>
	const int SetUniformData(std::string uniformName, glm::vec2& uniformData) const;
	/// <summary>
	/// Sets the uniform data of the specified uniform.
	/// </summary>
	/// <returns>Uniform location.</returns>
	const int SetUniformData(std::string uniformName, float& uniformData) const;
	/// <summary>
	/// Sets the uniform data of the specified uniform.
	/// </summary>
	/// <returns>Uniform location.</returns>
	const int SetUniformData(std::string uniformName, bool flip, glm::mat4 uniformMatrix) const;

	unsigned int GetProgramId() const;

private:
	const unsigned int CompileShader(unsigned int type, const std::string& shaderCode);
	const bool CheckCompilationError(unsigned int type, unsigned int shaderId);
};
