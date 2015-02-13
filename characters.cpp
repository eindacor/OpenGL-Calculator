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

	//column
	x = i % 5;
	//row
	y = i / 5;

	if (character_width <= x)
		character_width = x + 1;

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

line::line(vec4 origin)
{
	cursor = vec4(origin.x, origin.y, 0.0f, 1.0f);
}

void line::addString(string added_string)
{
	int length = added_string.length();
	for (int i = 0; i < length; i++)
	{
		character to_add(vec2(cursor.x, cursor.y), added_string[i]);

		//determine offset based on character added
		float x_offset = to_add.getWidth();
		mat4 nextChar = glm::translate(mat4(1.0f), vec3((x_offset + TEXT_PADDING), 0.0f, 0.0f));

		characters.push_back(character(vec2(cursor.x, cursor.y), added_string[i]));
		cursor = nextChar * cursor;
	}

	line_string += added_string;
}

int line::getRange()
{
	int range = 0;

	for (vector<character>::iterator i = characters.begin(); i != characters.end(); i++)
	{
		range += i->getWidth();
	}

	return range;
}

void line::lineUp()
{
	vec2 new_point;

	for (vector<character>::iterator i = characters.begin(); i != characters.end(); i++)
	{
		new_point = i->getBase();
		new_point.y += 9.0f + LINE_PADDING;
		i->changeBase(new_point);
	}
}

void line::addChar(char c)
{
	character temp(vec2(cursor.x, cursor.y), c);
	float x_offset = float(temp.getWidth());
	x_offset += TEXT_PADDING;

	//set translation matrix for cursor
	mat4 nextChar = glm::translate(mat4(1.0f), vec3(x_offset, 0.0f, 0.0f));

	characters.push_back(character(vec2(cursor.x, cursor.y), c));
	cursor = nextChar * cursor;
	line_string += c;
}

void line::removeChar()
{
	if (characters.size() > 0)
	{
		vector<character>::iterator i = characters.end() - 1;
		float x_offset = float(i->getWidth());
		x_offset += TEXT_PADDING;
		x_offset *= -1.0f;
		mat4 nextChar = glm::translate(mat4(1.0f), vec3(x_offset, 0.0f, 0.0f));

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
	int char_width_total = 0;
	vector<line>::iterator target = line_list.end();
	int padding = 0;
	bool first_highest = true;

	for (int i = 0; i < 4; i++)
	{
		target--;
		if (target->getRange() > char_width_total)
		{
			char_width_total = target->getRange();
			padding = ((target->getCharCount()-1) * TEXT_PADDING);

			if (i != 0)
				first_highest = false;
		}

		if (target == line_list.begin())
		{
			char_width_total += padding;
			return char_width_total;
		}
	}

	char_width_total += padding;

	//adds additional space for the cursor if the active line is the largest in scope
	if (first_highest == true)
	{
		char_width_total += (5 + TEXT_PADDING);
	}
		
	return char_width_total;
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

void line_group::clear()
{
	line_list.clear();
}