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
		Exception::Exception(const char* message, int code, Exception* parent) : chaos::Exception(message, code, parent)
		{
		}


		Exception::Exception(const char* message, int code) : chaos::Exception(message, code)
		{
		}

		Exception::Exception(const char* message) : chaos::Exception(message)
		{
		}


		Exception::~Exception()
		{
		}

	} /* namespace glfw */
} /* namespace ca */
