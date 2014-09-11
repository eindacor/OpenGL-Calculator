#ifndef DISPLAY_H
#define DISPLAY_H

#include "header.h"

class display_handler
{
public:
	display_handler(string title, string vert_file, string frag_file);
	~display_handler();

	void printErrors();

	GLFWwindow* getWindow() { return window; }

	bool getErrors() { return errors; }

	void render(line_group lines);
	void scrollTextColor(int i);
	void scrollBackgroundColor(int i);
	int createProgram(string vert_file, string frag_file);
	int createShader(GLenum type, string file);

private:
	GLuint program_ID;
	GLuint fragment_shader_ID;
	GLuint vertex_shader_ID;
	GLint translation_matrix_ID;
	GLint scaling_matrix_ID;
	GLint text_color_ID;
	vec4 text_color;
	vec4 background_color;
	GLFWwindow* window;
	vector<string> display_errors;
	bool errors = true;
	string window_title;
	int text_color_index;
	int background_color_index;

	bool cursor_display;

	GLuint vertex_buffer_object;
	GLuint vertex_array_object;
};

#endif