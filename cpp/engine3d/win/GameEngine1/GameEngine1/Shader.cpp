#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Shader {
private:
	string filename;
	string source;
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
public:
	Shader(string fn) {
		filename = fn;
		//ifstream in;
	}

	void ReadShaderFile() {
		ifstream in(filename);
		//char a[100];
		//in >> a;
		//cout << a << endl;
		string line;
		while (getline(in, line)) {
			cout << line << endl;
		}
	}

	~Shader() {

	}
};