#include "characters.h"

pixel::pixel(vec2 origin)
{
	base_point = origin;
	setIndices();
}

//adjusts vertices according to the base point of the pixel
void pixel::setIndices()
{
	indices[0] = vec4(base_point[0], base_point[1], 1.0f, 1.0f);
	indices[1] = vec4(base_point[0] + 1.0f, base_point[1], 1.0f, 1.0f);
	indices[2] = vec4(base_point[0], base_point[1] + 1.0f, 1.0f, 1.0f);
	indices[3] = vec4(base_point[0] + 1.0f, base_point[1], 1.0f, 1.0f);
	indices[4] = vec4(base_point[0], base_point[1] + 1.0f, 1.0f, 1.0f);
	indices[5] = vec4(base_point[0] + 1.0f, base_point[1] + 1.0f, 1.0f, 1.0f);
}

//modifies the base point and updates the indices
void pixel::movePixel(float x_offset, float y_offset)
{
	base_point.x += x_offset;
	base_point.y += y_offset;

	setIndices();
}

void pixel::draw(GLuint VBO)
{
	//bind vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//pass data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//use vertex attrib pointer to instruct OpenGLU how to interpret the data on the buffer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//draws vertices (2 triangles per "pixel")
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//disable array/unbind vbo
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//the following function adds a "pixel" at location based on the Character Pixel Location Matrix (see header.h)
void character::addPixel(int i)
{
	int x, y;

	if (i == -1)
	{
		x = 1;
		y = -1;
	}

	else
	{
		//column
		x = i % 3;
		//row
		y = i / 3;
	}

	//base point of pixel is calculated relative to the character's base point
	x += base_point.x;
	y += base_point.y;

	vec2 temp(x, y);

	//pixel is added to the pixel vector
	pixels.push_back(pixel(vec2(x,y)));
}

//draws all pixels of the character
void character::draw(GLuint VBO)
{
	for (vector<pixel>::iterator i = pixels.begin(); i != pixels.end(); i++)
	{
		i->draw(VBO);
	}
}

//moves the base_point to a new origin, passing offsets to each pixel
void character::changeBase(vec2 origin)
{
	float x_offset = origin.x - base_point.x;
	float y_offset = origin.y - base_point.y;

	for (vector<pixel>::iterator i = pixels.begin(); i != pixels.end(); i++)
	{
		i->movePixel(x_offset, y_offset);
	}
}

//initializes the character using an index number referring to the Character Pixel Location Matrix (see header.h)
character::character(vec2 origin, char c)
{
	//establish base point of the character
	base_point = origin;

	switch (c)
	{
	case ' ': break;

	case '0':
	case 'O':
		addPixel(1);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(19);
		break;

	case '1':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(4);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(16);
		addPixel(18);
		addPixel(19);
		break;

	case '2':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(6);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case '3':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(8);
		addPixel(10);
		addPixel(11);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case '4':
		addPixel(2);
		addPixel(5);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		break;

	case '5':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(15);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case '6':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case '7':
		addPixel(1);
		addPixel(4);
		addPixel(7);
		addPixel(10);
		addPixel(14);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case '8':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case '9':
		addPixel(2);
		addPixel(5);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case 'A':
		addPixel(0);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(19);
		break;

	case 'B':
		addPixel(0);
		addPixel(1);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		break;

	case 'C':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(9);
		addPixel(12);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case 'D':
		addPixel(0);
		addPixel(1);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		break;

	case 'E':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(6);
		addPixel(9);
		addPixel(10);
		addPixel(12);
		addPixel(15);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case 'F':
		addPixel(0);
		addPixel(3);
		addPixel(6);
		addPixel(9);
		addPixel(10);
		addPixel(12);
		addPixel(15);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case 'G':
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(11);
		addPixel(12);
		addPixel(15);
		addPixel(19);
		addPixel(20);
		break;

	case 'H':
		addPixel(0);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		break;

	case 'I':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(4);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(16);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case 'J':
		addPixel(1);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(11);
		addPixel(14);
		addPixel(17);
		addPixel(20);
		break;

	case 'K':
		addPixel(0);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		break;

	case 'L':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(6);
		addPixel(9);
		addPixel(12);
		addPixel(15);
		addPixel(18);
		break;

	case 'M':
		addPixel(0);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(13);
		addPixel(14);
		addPixel(15);
		addPixel(16);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		break;

	case 'N':
		addPixel(0);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(13);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		break;

	case 'P':
		addPixel(0);
		addPixel(3);
		addPixel(6);
		addPixel(9);
		addPixel(10);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		break;

	case 'Q':
		addPixel(2);
		addPixel(4);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(19);
		break;

	case 'R':
		addPixel(0);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		break;

	case 'S':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case 'T':
		addPixel(1);
		addPixel(4);
		addPixel(7);
		addPixel(10);
		addPixel(13);
		addPixel(16);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case 'U':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		break;

	case 'V':
		addPixel(1);
		addPixel(4);
		addPixel(6);
		addPixel(8);
		addPixel(9);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		break;

	case 'W':
		addPixel(0);
		addPixel(2);
		addPixel(3);
		addPixel(4);
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		break;

	case 'X':
		addPixel(0);
		addPixel(2);
		addPixel(3);
		addPixel(5);
		addPixel(6);
		addPixel(8);
		addPixel(10);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		break;

	case 'Y':
		addPixel(1);
		addPixel(4);
		addPixel(7);
		addPixel(10);
		addPixel(12);
		addPixel(14);
		addPixel(15);
		addPixel(17);
		addPixel(18);
		addPixel(20);
		break;

	case 'Z':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(6);
		addPixel(10);
		addPixel(14);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;

	case '=':
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(12);
		addPixel(13);
		addPixel(14);
		break;

	case '+':
		addPixel(7);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(13);
		break;

	case '-':
		addPixel(9);
		addPixel(10);
		addPixel(11);
		break;

	case '*':
		addPixel(6);
		addPixel(8);
		addPixel(10);
		addPixel(12);
		addPixel(14);
		break;

	case '/':
		addPixel(6);
		addPixel(10);
		addPixel(14);
		break;

	case '^':
		addPixel(15);
		addPixel(17);
		addPixel(19);
		break;

	case '!':
		addPixel(4);
		addPixel(10);
		addPixel(13);
		addPixel(16);
		break;

	case '(':
		addPixel(2);
		addPixel(4);
		addPixel(6);
		addPixel(9);
		addPixel(12);
		addPixel(16);
		addPixel(20);
		break;

	case ')':
		addPixel(0);
		addPixel(4);
		addPixel(8);
		addPixel(11);
		addPixel(14);
		addPixel(16);
		addPixel(18);
		break;

	case '.':
		addPixel(1);
		break;

	case ',':
		addPixel(1);
		addPixel(-1);
		break;

	/*
	case '0':
		addPixel(0);
		addPixel(1);
		addPixel(2);
		addPixel(3);
		addPixel(4);
		addPixel(5);
		addPixel(6);
		addPixel(7);
		addPixel(8);
		addPixel(9);
		addPixel(10);
		addPixel(11);
		addPixel(12);
		addPixel(13);
		addPixel(14);
		addPixel(15);
		addPixel(16);
		addPixel(17);
		addPixel(18);
		addPixel(19);
		addPixel(20);
		break;
	*/
	}
}

line::line(vec4 origin)
{
	cursor = vec4(origin.x, origin.y, 0.0f, 1.0f);
}

void line::addString(string added_string)
{
	int length = added_string.length();
	mat4 nextChar = glm::translate(mat4(1.0f), vec3(4.0f, 0.0f, 0.0f));

	for (int i = 0; i < length; i++)
	{
		characters.push_back(character(vec2(cursor.x, cursor.y), added_string[i]));
		cursor = nextChar * cursor;
	}

	line_string += added_string;
}

void line::lineUp()
{
	vec2 new_point;

	for (vector<character>::iterator i = characters.begin(); i != characters.end(); i++)
	{
		new_point = i->getBase();
		new_point.y += 9.0f;
		i->changeBase(new_point);
	}
}

void line::addChar(char c)
{
	//set translation matrix for cursor
	mat4 nextChar = glm::translate(mat4(1.0f), vec3(4.0f, 0.0f, 0.0f));

	characters.push_back(character(vec2(cursor.x, cursor.y), c));
	cursor = nextChar * cursor;
	line_string += c;
}

void line::removeChar()
{
	if (characters.size() > 0)
	{
		mat4 nextChar = glm::translate(mat4(1.0f), vec3(-4.0f, 0.0f, 0.0f));
		characters.pop_back();
		cursor = nextChar * cursor;
		line_string.erase(line_string.end() - 1);
	}
}

void line::draw(GLuint VBO)
{
	for (vector<character>::iterator i = characters.begin(); i != characters.end(); i++)
	{
		i->draw(VBO);
	}
}

void line_group::addLine(line added_line)
{
	for (vector<line>::iterator i = line_list.begin(); i != line_list.end(); i++)
	{
		i->lineUp();
	}

	line_list.push_back(added_line);

	current_range = added_line.getRange();
}

void line_group::draw(GLuint VBO)
{
	for (vector<line>::iterator i = line_list.begin(); i != line_list.end(); i++)
	{
		i->draw(VBO);
	}
}

void line_group::removeChar()
{
	vector<line>::iterator target = line_list.end();
	target--;

	target->removeChar();
}

void line_group::addChar(char c)
{
	vector<line>::iterator target = line_list.end();
	target--;

	target->addChar(c);
}

int line_group::getCurrentRange()
{
	int highest = 4;
	vector<line>::iterator target = line_list.end();

	for (int i = 0; i < 3; i++)
	{
		target--;
		highest = (target->getRange() > highest ? target->getRange() : highest);

		if (target == line_list.begin())
			return highest;
	}

	return highest + 1.0f;
	

	/*
	//analyze the previous line
	vector<line>::iterator target = line_list.end();
	target--;

	int range_last = target->getRange();

	//if the last line only has one element, return the range of the previous
	if (line_list.size() == 1)
	{
		return range_last + 1.0f;
	}

	else target--;

	//if the 2nd to last line is longer than the last, return it. otherwise return the current line's range +1 for the cursor
	int temp = (range_last > target->getRange() ? range_last : target->getRange());
	temp += 1.0f;
	return temp;
	*/
}

vec4 line_group::getCursor()
{
	//analyze the previous line
	vector<line>::iterator target = line_list.end();
	target--;

	return target->getCursor();
}

string line_group::convertCurrentLine()
{
	vector<line>::iterator target_line = line_list.end()-1;
	return target_line->getString();
}

void line_group::removeLine()
{
	line_list.erase(line_list.begin());
}