#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include<glm/glm.hpp>
#include<SDL2/SDL_image.h>
#include<shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Triangle Vertices
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
//vector to translate a cube to get 10 cubes at different position in the scene
glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f), //room cube
  glm::vec3( -10.0f,  -12.0f, -10.0f),
  glm::vec3(10.0f, -12.0f, -10.0f),
  glm::vec3(10.0f, -12.0f, 10.0f),
  glm::vec3( -10.0f, -12.0f, 10.0f),
  glm::vec3( 10.0f,  10.0f, 10.0f),
  glm::vec3(-10.0f,  10.0f, -10.0f),
  glm::vec3( 10.0f, 10.0f, -10.0f),
  glm::vec3( -10.0f,  10.0f, 10.0f),

  //glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 cubeScale[] = {
	glm::vec3( 30.0f,  30.0f,  30.0f),
	glm::vec3( 5.0f,  5.0f,  5.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 4.0f,  4.0f,  4.0f),
	glm::vec3( 2.0f,  2.0f,  2.0f),
	glm::vec3( 3.0f,  3.0f,  3.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f)
};


// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  0.05f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;
float speed = 20.0f;


void initContext()
{    glfwInit();
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* createWindow(){
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

void processInput(GLFWwindow *window)
{
	//move with zqsd, but opengl handle qwerty
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	float cameraSpeed = speed * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	  cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	  cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	  cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	  cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void createCube(int VAO, Shader shader, int i, bool rotate)
{
	glBindVertexArray(VAO);
	glm::mat4 model;
	model = glm::translate(model, cubePositions[i]) * glm::scale(model, cubeScale[i]);
	if(rotate){
		float angle = 20.0f * i + 0.5f;
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	}

	shader.setMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void renderLoop(GLFWwindow* window, int VAO, Shader* shaders){
	while(!glfwWindowShouldClose(window))
	{
		 // per-frame time logic
		float currentFrame = glfwGetTime();
		 deltaTime = currentFrame - lastFrame;
		 lastFrame = currentFrame;
		 /**********************************************************************/


		// Input
		processInput(window);
		/**********************************************************************/

		// rendering input
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shaders[0].setMat4("view", view);

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
		// note: the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		shaders[0].setMat4("projection", projection);

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		 //load image, create texture and generate mipmaps
		SDL_Surface *tex = IMG_Load("./mur.jpg");

		if(tex == 0) {
			std::cout << "Erreur : " << SDL_GetError() << std::endl;
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->w, tex->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->pixels);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		 int vertexTexture = glGetUniformLocation(shaders[0].ID, "ourTexture");
		 glUniform1i(vertexTexture,0);

		 glEnable(GL_DEPTH_TEST);
		 glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		 glStencilMask(0x00);
		 shaders[0].use();

		// room
		createCube(VAO, shaders[0], 0, false);

		 //load image, create texture and generate mipmaps
		tex = IMG_Load("./cube.jpg");

		if(tex == 0) {
			std::cout << "Erreur : " << SDL_GetError() << std::endl;
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->w, tex->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->pixels);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		 vertexTexture = glGetUniformLocation(shaders[0].ID, "ourTexture");
		 glUniform1i(vertexTexture,0);

		 glActiveTexture(GL_TEXTURE0);
		 glBindTexture(GL_TEXTURE_2D, texture);

		// 3D
		// 2. use our shader program when we want to render an object

		shaders[0].use();
//		glStencilFunc(GL_ALWAYS, 1, 0xFF);
//		glStencilMask(0xFF);

		for(int i = 1; i < 6; i++) {
			createCube(VAO, shaders[0], i, true);
		}

//		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//		glStencilMask(0x00);
//		glDisable(GL_DEPTH_TEST);


//		shaders[1].use();
//		glm::mat4 model;
//		model = glm::mat4();
//		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//		model = glm::scale(model, cubeScale[2]);
//		shaders[1].setMat4("model", model);
//		shaders[1].setMat4("view", view);
//		shaders[1].setMat4("projection", projection);

//		for(int i = 1; i < 6; i++) {
//			createCube(VAO, shaders[1], i, true);
//		}

		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);

		// 3. now draw the object
		//glDrawArrays(GL_TRIANGLES, 0 , 36);

		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		/**********************************************************************/

		// check and call events and swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
		/**********************************************************************/
	}
}
int main(int argc, char **argv) {
/**
 * Creating window
 **/
	initContext();
	GLFWwindow* window = createWindow();
	// Load openGL adress
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
	}

	glViewport(0, 0, 800, 600);

	// Callback
	// handle resized window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// udpdate mouse position
	glfwSetCursorPosCallback(window, mouse_callback);
	/**********************************************************************/

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	/**
	 * Create and bind buffer and shader
	 */
	Shader shader("./vertexShaderCubeTex.vsl", "./fragmentShaderCubeTex.fsl");
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	// 0. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 1. then set the vertex attributes pointers
	/**
	 * @brief glad_glVertexAttribPointer
	 * @param 1 : location
	 * @param 2 : size of the vertex attribute
	 * @param 3 : data type
	 * @param 4 : boolean true = normalized data
	 * @param 5 : space between two attribute sets
	 * @param 6 : offset of the begining data in the buffer
	 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// gl location to the argument
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(2);

//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);




/**********************************************************************/

/** Render loop
 * glfwWindowShouldClose : check the closing
 * glfwSwapBuffers : swap the color buffer
 * glfwPollEvents : check events like input
 **/


	// load and create a texture
	   // -------------------------
	Shader shaderSingleColor("./shaderSingleColor.vsl", "./shaderSingleColor.fsl");


	Shader shaders[] = {shader, shaderSingleColor};

	renderLoop(window, VAO, shaders);

/**********************************************************************/

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

