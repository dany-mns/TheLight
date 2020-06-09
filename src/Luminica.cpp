﻿#include "Vertex.h"
#include "Primitives.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "EntryPoint.hpp"

const char* vfile = "res\\shaders\\vertex.glsl";
const char* ffile = "res\\shaders\\fragment.glsl";

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
int framebufferWidth, framebufferHeight;


void updateInput(GLFWwindow* window, Mesh& mesh, Mesh& second, Mesh &sun) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.0f, 0.0f, +0.02f));
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.0f, 0.0f, -0.02f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.02f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		mesh.move(glm::vec3(-0.02f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(0.0f, 2.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(0.0f, -2.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(-2.0f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(2.0f, 0.0f, 0.0f));
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		second.move(glm::vec3(0.0f, 0.0f, +0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		second.move(glm::vec3(0.0f, 0.0f, -0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		second.move(glm::vec3(0.01f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		second.move(glm::vec3(-0.01f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		second.rotate(glm::vec3(0.0f, 2.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		second.rotate(glm::vec3(0.0f, -2.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		sun.rotate(glm::vec3(0.0f, 2.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		sun.rotate(glm::vec3(0.0f, -2.0f, 0.0f));
	}
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error %d: %s\n", error, description);
}


GLFWwindow* createWindow(const char* winName, const int width, const int height, int& frameBufferWidht, int& frameBufferHeight, const int glMin, const int glMaj) {
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMaj);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMin);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, winName, NULL, NULL);
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window);

	return window;
}

entry_point{


	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = createWindow("TheLight", WINDOW_WIDTH, WINDOW_HEIGHT, framebufferWidth, framebufferHeight, 4, 4);

	GLint err;
	if ((err = glewInit()) != GLEW_OK) {
		std::cerr << glewGetErrorString(err);
		glfwTerminate();
		return -1;
	}

	//Some stuff who doens't work momentary
	glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// IDK
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Shader init
	Shader mainShader(vfile, ffile);

	// Model mesh init
	Primitive complexObj = ComplexObject(Pyramid);
	Mesh pyramidMesh(&complexObj);
	pyramidMesh.scaleUp(glm::vec3(-0.9, -0.9, -0.9));
	pyramidMesh.setPosition(glm::vec3(0.4f, -0.15f, 0.3f));

	Primitive lightSource = ComplexObject(Sun);
	Mesh lightMesh(&lightSource);
	lightMesh.scaleUp(glm::vec3(-0.95, -0.95, -0.95));

	// Porsche Mesh
	Primitive porsche = ComplexObject(Porsche);
	Mesh porscheMesh(&porsche);
	porscheMesh.scaleUp(glm::vec3(-0.75, -0.75, -0.75));
	//porscheMesh.setPosition(glm::vec3(-0.4f, 0.35f, 0.3f));

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);



	Texture sunTexture("res\\shaders\\sun\\texture.jpg", GL_TEXTURE_2D, 0);
	Texture sunTextureNormal("res\\shaders\\sun\\normal.jpg", GL_TEXTURE_2D, 1);
	Material materialSun(glm::vec3(0.1f), glm::vec3(0.75f), glm::vec3(1.0f), sunTexture.getUnit(), sunTextureNormal.getUnit());


	Texture porscheTexture("res\\shaders\\porsche\\texture.jpg", GL_TEXTURE_2D, 2);
	Texture porscheTextureNormal("res\\shaders\\porsche\\normal.jpg", GL_TEXTURE_2D, 3);
	Material materialPorsche(glm::vec3(0.1f), glm::vec3(0.75f), glm::vec3(1.0f), porscheTexture.getUnit(), porscheTextureNormal.getUnit());

	Texture wallTexture("res\\shaders\\pyramid\\brickwall.jpg", GL_TEXTURE_2D, 4);
	Texture wallTextureNormal("res\\shaders\\pyramid\\brickwall_normal.jpg", GL_TEXTURE_2D, 5);
	Material materialBrick(glm::vec3(0.1f), glm::vec3(0.75f), glm::vec3(1.0f), wallTexture.getUnit(), wallTextureNormal.getUnit());

	//view position
	glm::vec3 lightPosition(-0.4f, 0.35f, 0.2f);
	lightMesh.setPosition(lightPosition);
	glm::vec3 viewPosition(glm::vec3(0, 0, 1));



	glm::mat4 viewMatrix = glm::lookAt(
		viewPosition, // Camera is at (x, x, x), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);


	float FoV = 55.0f;
	// Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless
	glm::mat4 projectionMatrix = glm::perspective(
		glm::radians(FoV),									// The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,			// Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		0.1f,												// Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f												// Far clipping plane. Keep as little as possible.
	);


	mainShader.use();

	mainShader.setMat4fv(viewMatrix, "viewMatrix");
	mainShader.setMat4fv(projectionMatrix, "projectionMatrix");
	mainShader.setVec3f(lightPosition, "lightPosition");
	mainShader.setVec3f(viewPosition, "viewPosition");


	mainShader.disable();

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();
		updateInput(window, porscheMesh, pyramidMesh, lightMesh);


		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		mainShader.use();
		
		// Render light source

		materialSun.sendToShader(mainShader);


		// draw lightsource
		sunTexture.bind();
		sunTextureNormal.bind();
		lightMesh.render(&mainShader);


		// draw obj Pyramid + texture
		materialBrick.sendToShader(mainShader);
		wallTexture.bind();
		wallTextureNormal.bind();
		pyramidMesh.render(&mainShader);


		// draw obj Porsche + texture
		materialPorsche.sendToShader(mainShader);
		porscheTexture.bind();
		porscheTextureNormal.bind();
		porscheMesh.render(&mainShader);


		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		mainShader.disable();
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//End of program
	glfwDestroyWindow(window);
	glfwTerminate();
	glDeleteProgram(mainShader.getMainProgram());
	mainShader.~Shader();

	return 0;
}
