/*
 * Exception.cpp
 *
 *  Created on: 06.03.2016
 *      Author: chaos
 */

#include "Exception.h"

namespace ca
{
	namespace glfw
	{
		Exception::Exception(const char* message, int code, Exception* parent) : ca::core::Exception(message, code, parent)
		{
		}


		Exception::Exception(const char* message, int code) : ca::core::Exception(message, code)
		{
		}

		Exception::Exception(const char* message) : ca::core::Exception(message)
		{
		}


		Exception::~Exception()
		{
		}

	} /* namespace glfw */
} /* namespace ca */
