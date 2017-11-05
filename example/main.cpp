
#include<ShukiShader.h>
#include<ShukiModel.h>
#include<ShukiTexture.h>

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
using namespace std;
using namespace Assimp;
//#include "ogldev_util.h"
//#include "ogldev_math_3d.h"

struct Vector3f {
	float data[3];
	Vector3f() {
		data[0] = 0.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;

	}
	Vector3f(float a, float b, float c) {
		data[0] = a;
		data[1] = b;
		data[2] = c;
	}
};


GLuint VBO;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
	Vector3f Vertices[3];
	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}



int main(int argc, char** argv)
{
	string filenameg = "D://mimo.png";

	Magick::Image m_image;
	Magick::Blob m_blob;

	Magick::Image image;// image("100x100", "white");
	image.read(filenameg);
	image.pixelColor(50, 50, "blue");
	
	image.write("red_pixel.png");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 04");

	InitializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	printf("GL version: %s\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	CreateVertexBuffer();

	//CompileShaders();
	shuki::ShaderManger sm;
	sm.setVSFile("D:\\proj\\opengl\\shaders\\shader.vs");
	sm.setFSFile("D:\\proj\\opengl\\shaders\\shader.fs");
	sm.initialize();
	sm.init_program();
	sm.attach_shaders();
	sm.use();

	Assimp::Importer impoter;
	string Filename("D:\\proj\\opengl\\resources\\cat2\\cat2.obj");
	shuki::Model m(string("cat"));

	glutMainLoop();

	return 0;

}