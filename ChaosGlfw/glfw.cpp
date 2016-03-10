/*
 * glfw.cpp
 *
 *  Created on: 06.03.2016
 *      Author: chaos
 */


#include "glfw.h"

namespace ca
{
	namespace glfw
	{
		bool initialized = false;

		void init ()
		{
			if (initialized) return;
			if (GL_FALSE == glfwInit())
			{
				throw new ca::glfw::Exception("Failed to initialize glfw.");
			}

			initialized = true;
		}
	}
}

