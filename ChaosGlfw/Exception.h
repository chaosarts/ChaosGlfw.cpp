/*
 * Exception.h
 *
 *  Created on: 06.03.2016
 *      Author: chaos
 */

#ifndef _ChaosGlfw_Exception_h_
#define _ChaosGlfw_Exception_h_

#include <ChaosCore/Exception.h>

namespace ca
{
	namespace glfw
	{

		class Exception: public chaos::Exception
		{
		public:
			Exception(const char* message, int code, Exception* parent);
			Exception(const char* message, int code);
			Exception(const char* message);
			virtual ~Exception();
		};

	} /* namespace glfw */
} /* namespace ca */

#endif /* EXCEPTION_H_ */
