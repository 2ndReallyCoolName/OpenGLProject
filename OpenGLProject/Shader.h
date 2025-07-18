#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void setFloat4(const std::string& name, float r, float g, float b, float a) const;
	void setFloat4(const std::string& name, std::vector<float>& v) const;
	void setFloat3(const std::string& name, std::vector<float>& v) const;
	void setFloat3(const std::string& name, float r, float g, float b) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec3(const std::string& name, float r, float g, float b) const;
};