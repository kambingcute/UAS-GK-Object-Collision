// Ball_Collision.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// GL_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/* Libraries */

/* Header Files */
#include "Shader_Loading.h"
#include "Shape.h"
#include "Window_Setting.h"
#include "Window_Setting.h"
#include "pch.h"

/* Function Declaration */
static unsigned int CompileShader(unsigned int type, const std::string& source);
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "UAS GK Pinkie Pie", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewInit(); //must be after glfwMakeContextCurrent(window);
				//need opengl context

	/* Shader Program */
	std::string vertexShader = Load_Shader("vertex_Shader");
	std::string fragmentShader = Load_Shader("fragment_Shader");
	/* Use the Shader */
	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);


	unsigned int buffer;
	glGenBuffers(1, &buffer); // generate 1 buffer 
							  // memory error if you don't have glewInit()
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //select the buffer for the GPU to work on

	double cxpos, cypos;
	double cxpos_o, cypos_o;
	double r, g, b;
	double new_ball_size = 20;
	double ball_increace_rate = 0.7;
	double new_triangle_size = 50;
	double triangle_increace_rate = 0.7;
	bool object_created = false;
	bool triangle_created = false;

	std::vector<Polygon*> balls;
	std::vector<Triangle*> triangles;


	Polygon b1(200, 35.355339, 50, 360);
	b1.init_velocity(0.5, 0.5);

	Polygon b2(-100, -35.355339, 100, 360);
	b2.init_velocity(0.5, 0.5);

	// Square r1(-277, 14, 50, 100, 80); // x, y, widht, height, angle

	Triangle t1(120, 30, 50);
	t1.init_velocity(-0.5, 0);

	Triangle t2(-120, 160, 80);
	t2.init_velocity(0.5, 0.5);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		glClear(GL_COLOR_BUFFER_BIT);

		Square temp_square_2(0, 0, 6, 800, 00);
		temp_square_2.show();

		glfwGetCursorPos(window, &cxpos, &cypos);

		cxpos -= HALF_WIDTH;
		cypos -= HALF_HEIGHT;
		cypos = -cypos;

		int state1 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		int state2 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);



		/* Release Mouse And Create New Object */
		if (object_created == true && state1 == GLFW_RELEASE) {

			float dx = cxpos - cxpos_o;
			float dy = cypos - cypos_o;

			dx /= 20;
			dy /= 20;

			cout << dx << " " << dy << endl;

			Polygon* newball = new Polygon(cxpos_o, cypos_o, new_ball_size, 360);
			newball->init_velocity(-dx, -dy);
			newball->set_acclr_norm(-0.01);
			newball->change_color(r, g, b);
			balls.push_back(newball);

			new_ball_size = 20;
			object_created = false;
		}

		else if (triangle_created == true && state2 == GLFW_RELEASE) {

			float dx = cxpos - (cxpos_o / 4);
			float dy = cypos - (cypos_o / 4);

			dx /= 200;
			dy /= 200;

			cout << dx << " " << dy << endl;
			Triangle* newtriangle = new Triangle(cxpos_o, cypos_o, new_triangle_size);
			newtriangle->init_velocity(-dx, -dy);
			newtriangle->change_color(r, g, b);
			triangles.push_back(newtriangle);

			new_triangle_size = 50;
			triangle_created = false;
		}


		/* Click to choose Circle */
		if (state1 == GLFW_PRESS) {
			srand(time(NULL));
			if (object_created == false) {
				cxpos_o = cxpos;
				cypos_o = cypos;

				r = rand() / float(RAND_MAX + 1);
				g = rand() / float(RAND_MAX + 1);
				b = rand() / float(RAND_MAX + 1);
				object_created = true;
			}
			// cout << cxpos << " " << cypos << endl;

			Polygon tempball(cxpos_o, cypos_o, new_ball_size, 360);
			tempball.change_color(r, g, b);

			float dx = cxpos - cxpos_o;
			float dy = cypos - cypos_o;

			Polygon aimball(cxpos_o - dx, cypos_o - dy, 3, 360);
			aimball.change_color(1, 0, 0);


			new_ball_size += ball_increace_rate;
			if (new_ball_size > 100) ball_increace_rate = -ball_increace_rate;
			if (new_ball_size < 20) ball_increace_rate = -ball_increace_rate;

			tempball.show();
			aimball.show();

		}

		else if (state2 == GLFW_PRESS) {
			srand(time(NULL));
			if (object_created == false) {
				cxpos_o = cxpos;
				cypos_o = cypos;

				r = rand() / float(RAND_MAX + 1);
				g = rand() / float(RAND_MAX + 1);
				b = rand() / float(RAND_MAX + 1);
				triangle_created = true;
			}
			// cout << cxpos << " " << cypos << endl;

			Triangle temptriangle(cxpos_o, cypos_o, new_triangle_size);
			temptriangle.change_color(r, g, b);

			float dx = cxpos - cxpos_o;
			float dy = cypos - cypos_o;

			Triangle aimtriangle(cxpos_o - dx, cypos_o - dy, 3);
			aimtriangle.change_color(1, 1, 1);

			new_triangle_size += triangle_increace_rate;
			if (new_triangle_size > 100) triangle_increace_rate = -triangle_increace_rate;
			if (new_triangle_size < 20) triangle_increace_rate = -triangle_increace_rate;

			temptriangle.show();
			aimtriangle.show();
		}

		// update all balls
		int number_of_balls = balls.size();
		for (int i = 0; i < number_of_balls; i++) {
			balls[i]->update_position();
			balls[i]->show();
		}

		int number_of_triangles = triangles.size();
		for (int i = 0; i < number_of_triangles; i++) {
			triangles[i]->update_position();
			triangles[i]->show();
		}


		b1.update_position();
		b1.show();
		b2.update_position();
		b2.show();

		t1.update_position();
		t1.show();

		t2.update_position();
		t2.show();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glDeleteProgram(shader);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}



/* Function Implementation */

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::cout << "under construction" << std::endl;
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Fail to compile shader "
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	else {
		std::cout << "Compile Success!" << std::endl;
	}
	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


