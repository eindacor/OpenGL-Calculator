#include "header.h"

void convertString(string line, vector<character> &characters, vec4 &origin)
{
	
}

int main()
{
	display_handler display_context("The Window", "fragment_shader.glsl", "vertex_shader.glsl");

	if (display_context.getErrors() == true)
	{
		display_context.printErrors();
		return 0;
	}
		
	vector<character> gl_characters;

	vec4 origin(3.0f, 2.0f, 0.0f, 1.0f);

	line_group lines;

	lines.addLine(line(origin));
	key_handler keystates;

	string entered_string;

	bignum previous;
	settings user_settings(PRECISION, false, false);

	glfwSetTime(0);
	
	std::ofstream log_file;

	do
	{
		try
		{
			glfwPollEvents();

			KEYRETURN returned_key = keystates.checkKeys(lines, display_context, user_settings);

			bool base_change = false;

			if (returned_key == ENTER && base_change == false)
			{
				entered_string = lines.convertCurrentLine();

				if (entered_string == "clear")
				{
					lines.clear();
					lines.addLine(line(origin));
				}

				else
				{

					solution answer = solve(entered_string, previous, user_settings);

					if (answer.getError())
					{
						string error_string = "INVALID ENTRY";
						line error_line(origin);
						error_line.addString(error_string);
						lines.addLine(error_line);
					}

					else
					{
						string answer_string = answer.getSolved().getNumberString(true, false, 20);
						log_file.open("calc_log_file.txt", std::ofstream::out);
						log_file.write(&answer_string[0], answer_string.length());
						log_file.close();

						line solved_line(origin);
						string solved_string = "= ";
						solved_string += answer.getSolved().getNumberString(true, false, 10);
						solved_line.addString(solved_string);
						lines.addLine(solved_line);
						previous = answer.getSolved();
					}

					string spacer_string = "---------";
					line spacer_line(origin);
					spacer_line.addString(spacer_string);
					lines.addLine(spacer_line);

					lines.addLine(line(origin));
				}
			}

			else if (returned_key == ENTER && base_change == true)
			{

			}

			else if (returned_key == BASE)
			{
				base_change = true;
				string error_string = "ENTER DESIRED BASE";
				line error_line(origin);
				error_line.addString(error_string);
				lines.addLine(error_line);
			}

			else if (returned_key == OPTIONS)
			{

			}

			/*
			test *= bignum(10);
			line test_line(origin);
			test_line.addString(test.getNumberString(true, false, 10));
			lines.addLine(test_line);
			*/

			display_context.render(lines);

			if (lines.getCount() > 20)
				lines.removeLine();
		}

		catch (bignum_Error caught)
		{
			string error = caught.getErrorReport();
			std::ofstream error_log;
			error_log.open("JEPbignum_error_log.txt", std::ofstream::out);
			error_log.write(&error[0], error.length());
			error_log.close();
			
			string error_report = "AN ERROR HAS OCCURRED, PLEASE CHECK THE ERROR LOG";
			line error_line(origin);
			error_line.addString(error_report);
			lines.addLine(error_line);
			lines.addLine(line(origin));
		}

	} while (glfwGetKey(display_context.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
		!glfwWindowShouldClose(display_context.getWindow()));

	return 0;
}