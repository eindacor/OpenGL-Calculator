#include "display.h"

display_handler::display_handler(string title, string vert_file, string frag_file)
{
	errors = false;
	window_title = title;

	//initialize GLFW
	if (!glfwInit())
	{
		display_errors.push_back("glfw failed to initialize");
		errors = true;
	}

	//version control/create window
	else
	{
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(800, 800, &window_title[0], NULL, NULL);
	}

	//test window
	if (errors == false && window == NULL)
	{
		display_errors.push_back("window returned NULL");
		errors = true;
	}

	//make context current/initialize glew
	if (errors == false)
	{
		glfwMakeContextCurrent(window);

		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			display_errors.push_back("glew failed to initialize");
			errors = true;
		}
	}

	//create vertex array object (after glew is initialized, before any other OpenGL functions are used
	if (errors == false)
	{
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}

	//create shaders/program
	if (errors == false && createProgram(frag_file, vert_file) == 0)
	{
		errors = true;
	}

	//create vertex buffer object, set clear color
	if (errors == false)
	{
		glGenBuffers(1, &vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		//set scaling and translation matrix handles
		translation_matrix_ID = glGetUniformLocation(program_ID, "translation_matrix");
		scaling_matrix_ID = glGetUniformLocation(program_ID, "scaling_matrix");
		text_color_ID = glGetUniformLocation(program_ID, "text_color");

		text_color[0] = 1.0f;
		text_color[1] = 1.0f;
		text_color[2] = 1.0f;
		text_color[3] = 1.0f;

		text_color_index = 3;
		background_color_index = 7;
	}
}

int display_handler::createShader(GLenum type, string file)
{
	GLuint* target_ID;

	//set target shader ID based on GLenum passed
	switch (type)
	{
	case GL_FRAGMENT_SHADER: target_ID = &fragment_shader_ID; break;
	case GL_VERTEX_SHADER: target_ID = &vertex_shader_ID; break;
	default: display_errors.push_back("GLenum type not identified"); return 0;
	}

	//create shader with ID handle
	*target_ID = glCreateShader(type);

	string code_string;

	//convert glsl file into a string
	std::ifstream shader_file;
	shader_file.open(file, std::ifstream::in);
	while (shader_file.good())
	{
		string line;
		std::getline(shader_file, line);
		code_string += line + '\n';
	}

	//create const char* from string of code
	const char* code_char = code_string.c_str();

	//compile shader
	glShaderSource(*target_ID, 1, &code_char, NULL);
	glCompileShader(*target_ID);

	//test compilation, return success/failure
	GLint status;
	glGetShaderiv(*target_ID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		string error;

		switch (type)
		{
		case GL_FRAGMENT_SHADER: error = "fragment shader "; break;
		case GL_VERTEX_SHADER: error = "vertex shader "; break;
		}

		error += "failed to compile: ";

		GLint log_length;
		glGetShaderiv(*target_ID, GL_INFO_LOG_LENGTH, &log_length);
		vector<char> info_log(log_length + 1);

		glGetShaderInfoLog(*target_ID, log_length, NULL, &info_log[0]);

		for (vector<char>::iterator i = info_log.begin(); i != info_log.end(); i++)
		{
			error += *i;
		}

		display_errors.push_back(error);
		errors = true;
		return 0;
	}

	return 1;
}

int display_handler::createProgram(string vert_file, string frag_file)
{
	//create program handle
	program_ID = glCreateProgram();

	//create shaders
	if (createShader(GL_FRAGMENT_SHADER, frag_file) == 0)
		return 0;
	
	if (createShader(GL_VERTEX_SHADER, vert_file) == 0)
		return 0;

	//attach shaders, link program
	glAttachShader(program_ID, fragment_shader_ID);
	glAttachShader(program_ID, vertex_shader_ID);
	glLinkProgram(program_ID);

	//check link, return success/failure
	GLint status;
	glGetProgramiv(program_ID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		string error = "program failed to link: ";

		GLint log_length;
		glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &log_length);
		vector<char> info_log(log_length + 1);
		glGetProgramInfoLog(program_ID, log_length, NULL, &info_log[0]);

		for (vector<char>::iterator i = info_log.begin(); i != info_log.end(); i++)
		{
			error += *i;
		}

		display_errors.push_back(error);
		errors = true;
		return 0;
	}

	//detach shaders when complete
	glDetachShader(program_ID, fragment_shader_ID);
	glDetachShader(program_ID, vertex_shader_ID);

	return 1;
}

display_handler::~display_handler()
{
	//cleanup OpenGL/GLFW
	glDeleteProgram(program_ID);
	glDeleteShader(fragment_shader_ID);
	glDeleteShader(vertex_shader_ID);

	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteBuffers(1, &vertex_buffer_object);

	glfwDestroyWindow(window);
	glfwTerminate();
}

void display_handler::render(line_group lines)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program_ID);

	//creates a range based on desired character padding
	int margains = MARGAINS * 2;
	int range = margains + lines.getCurrentRange();

	float min_scale = 35 + (4 * LINE_PADDING);
	min_scale = 1 / min_scale;

	float x_offset = float(range) / -2;
	float y_offset = -5.0f;
	float scale = 2.0f / float(range);
	scale = (scale > min_scale ? min_scale : scale);

	//translate/scale the world coordinates to clip space
	glm::mat4 translation_matrix = glm::translate(mat4(1.0f), vec3(x_offset, y_offset, 0.0f));
	glm::mat4 scaling_matrix = glm::scale(mat4(1.0f), vec3(scale, scale, scale));
	glUniformMatrix4fv(translation_matrix_ID, 1, GL_FALSE, &translation_matrix[0][0]);
	glUniformMatrix4fv(scaling_matrix_ID, 1, GL_FALSE, &scaling_matrix[0][0]);

	//set text color
	glUniform4f(text_color_ID, text_color[0], text_color[1], text_color[2], 1.0f);

	//draws each pixel, in each character, in each line
	lines.draw(vertex_buffer_object);
	
	//check if .25s have passed since last cursor draw
	if (glfwGetTime() > .4f)
	{
		glfwSetTime(0);
		//toggle cursor_display
		cursor_display = (cursor_display == true ? false : true);
	}

	if (cursor_display == true)
	{
		//create color that is a combination of the background and text colors, and modify the uniform for the cursor
		float cursor_red = text_color[0] + background_color[0];
		float cursor_green = text_color[1] + background_color[1];
		float cursor_blue = text_color[2] + background_color[2];
		glUniform4f(text_color_ID, cursor_red / 2.0f, cursor_green / 2.0f, cursor_blue / 2.0f, 1.0f);

		//get current cursor location
		vec4 cursor = lines.getCursor();

		//generate cursor triangles based on current location
		float cursor_triangles[] = {
			cursor.x, cursor.y + 1.0f, cursor.z, 1.0f,
			cursor.x, cursor.y + 9.0f, cursor.z, 1.0f,
			cursor.x + 4.0f, cursor.y + 1.0f, cursor.z, 1.0f,
			cursor.x + 4.0f, cursor.y + 1.0f, cursor.z, 1.0f,
			cursor.x, cursor.y + 9.0f, cursor.z, 1.0f,
			cursor.x + 4.0f, cursor.y + 9.0f, cursor.z, 1.0f,
		};

		//draw cursor
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cursor_triangles), cursor_triangles, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glfwSwapBuffers(window);
}

void display_handler::printErrors()
{
	for (vector<string>::iterator i = display_errors.begin(); i != display_errors.end(); i++)
	{
		cout << *i << endl;
	}
}

//increments/decrements the text color index
void display_handler::scrollTextColor(int i)
{
	if (text_color_index == 0 && i == -1)
		text_color_index = 7;

	else if (text_color_index == 7 && i == 1)
		text_color_index = 0;

	else text_color_index += i;

	switch (text_color_index)
	{
	case 0: text_color = vec4(1.0f, 0.0f, 0.0f, 1.0f); break;
	case 1: text_color = vec4(1.0f, 1.0f, 0.0f, 1.0f); break;
	case 2: text_color = vec4(1.0f, 0.0f, 1.0f, 1.0f); break;
	case 3: text_color = vec4(1.0f, 1.0f, 1.0f, 1.0f); break;
	case 4: text_color = vec4(0.0f, 1.0f, 0.0f, 1.0f); break;
	case 5: text_color = vec4(0.0f, 1.0f, 1.0f, 1.0f); break;
	case 6: text_color = vec4(0.0f, 0.0f, 1.0f, 1.0f); break;
	case 7: text_color = vec4(0.0f, 0.0f, 0.0f, 1.0f); break;
	}
}

//increments/decrements the background color index
void display_handler::scrollBackgroundColor(int i)
{
	if (background_color_index == 0 && i == -1)
		background_color_index = 7;

	else if (background_color_index == 7 && i == 1)
		background_color_index = 0;

	else background_color_index += i;

	switch (background_color_index)
	{
	case 0: background_color = vec4(0.4f, 0.0f, 0.0f, 0.4f); break;
	case 1: background_color = vec4(0.4f, 0.4f, 0.0f, 1.0f); break;
	case 2: background_color = vec4(0.4f, 0.0f, 0.4f, 1.0f); break;
	case 3: background_color = vec4(0.4f, 0.4f, 0.4f, 1.0f); break;
	case 4: background_color = vec4(0.0f, 0.4f, 0.0f, 1.0f); break;
	case 5: background_color = vec4(0.0f, 0.4f, 0.4f, 1.0f); break;
	case 6: background_color = vec4(0.0f, 0.0f, 0.4f, 1.0f); break;
	case 7: background_color = vec4(0.0f, 0.0f, 0.0f, 1.0f); break;
	}

	glClearColor(background_color[0], background_color[1], background_color[2], 1.0f);
}