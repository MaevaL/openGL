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
  glm::vec3( 0.0f,  0.0f,  0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f,  2.0f, -2.5f),
  glm::vec3( 1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 cubeScale[] = {
	glm::vec3( 30.0f,  30.0f,  30.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f),
	glm::vec3( 1.0f,  1.0f,  1.0f)
};


// index vertices
//unsigned int indices[] = {
//	0,1,3,
//	1,2,3

//};

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
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

void createCube(int VAO, Shader shader)
{
	glBindVertexArray(VAO);
	for(unsigned int i = 0; i < 10; i++)
	{
	  glm::mat4 model;
	  model = glm::translate(model, cubePositions[i]) * glm::scale(model, cubeScale[i]);
	  float angle = 20.0f * i + 0.5f;
	  model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	  shader.setMat4("model", model);

	  glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void renderLoop(GLFWwindow* window, Shader shader, int VAO, GLuint texture){
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

		// texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		// 3D
		// 2. use our shader program when we want to render an object
		shader.use();


		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shader.setMat4("view", view);

		createCube(VAO, shader);

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
	Shader shader("./vertexShaderCubeTex.vsl", "fragmentShaderCubeTex.fsl");
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
	   GLuint texture;
	   glGenTextures(1, &texture);
	   glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
//	   // set the texture wrapping parameters
//	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		//set texture filtering parameters
//	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//load image, create texture and generate mipmaps

	   SDL_Surface *tex = IMG_Load("./container.jpg");

	   if(tex == 0)
		{
		   std::cout << "Erreur : " << SDL_GetError() << std::endl;
		   return false;
	   } else {
		   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->w, tex->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->pixels);
		   glGenerateMipmap(GL_TEXTURE_2D);
	   }

	shader.use();
	int vertexTexture = glGetUniformLocation(shader.ID, "ourTexture");
	glUniform1i(vertexTexture,0);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	// note: the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);

	renderLoop(window, shader, VAO, texture);

/**********************************************************************/

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

