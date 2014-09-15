#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "header.h"

class pixel
{
public:
	pixel(vec2 origin);
	~pixel(){};

	void draw(GLuint VBO);
	void setIndices();
	void movePixel(float x_offset, float y_offset);

private:
	vec2 base_point;
	vec4 indices[6];
};

class character
{
public:
	character(vec2 origin, char c);
	~character(){};

	void addPixel(int i);
	void draw(GLuint VBO);
	void changeBase(vec2 origin);
	int getWidth() { return character_width; }

	vec2 getBase() { return base_point; }

private:
	vec2 base_point;
	vector<pixel> pixels;
	int character_width;
};

class line
{
public:
	line(vec4 origin);
	~line(){};

	void addChar(char c);
	void removeChar();
	void lineUp();
	void draw(GLuint VBO);
	void addString(string s);
	string getString() { return line_string; }
	int getCharCount() { return characters.size(); }

	vec4 getCursor() { return cursor; }

	int getRange();

private:
	vec4 cursor;
	vector<character> characters;
	string line_string;
};

class line_group
{
public:
	line_group(){};
	~line_group(){};

	void draw(GLuint VBO);
	void addLine(line added_line);
	void addChar(char c);
	void removeChar();
	vec4 getCursor();
	void removeLine();
	int getCount() { return line_list.size(); }

	string convertCurrentLine();

	int getCurrentRange();

private:
	vector<line> line_list;
	int current_range;
};

#endif