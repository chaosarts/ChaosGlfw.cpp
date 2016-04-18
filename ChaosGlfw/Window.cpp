/*
 * Window.cpp
 *
 *  Created on: 06.03.2016
 *      Author: chaos
 */

#include "Window.h"
using namespace std;

namespace ca
{
	namespace glfw
	{
		map<GLFWwindow*, Window*> windowMap;



		void Window::_onWindowClose(GLFWwindow* window)
		{
			map<GLFWwindow*, Window*>::iterator windowIt = windowMap.find(window);
			if (windowIt == windowMap.end()) return;

			Window* win = windowIt->second;
			list<EventListener*>::iterator it = win->_listeners.begin();
			while (it != win->_listeners.end())
				(*(it++))->windowWillClose(win);
		}


		void Window::_onWindowFocus(GLFWwindow* window)
		{
			map<GLFWwindow*, Window*>::iterator windowIt = windowMap.find(window);
			if (windowIt == windowMap.end()) return;

			Window* win = windowIt->second;
			list<EventListener*>::iterator it = win->_listeners.begin();
			while (it != win->_listeners.end())
				(*(it++))->windowGetsFocus(win);
		}


		void Window::_onWindowMove(GLFWwindow* window)
		{
			map<GLFWwindow*, Window*>::iterator windowIt = windowMap.find(window);
			if (windowIt == windowMap.end()) return;

			Window* win = windowIt->second;
			list<EventListener*>::iterator it = win->_listeners.begin();
			while (it != win->_listeners.end())
				(*(it++))->windowDidMove(win);
		}


		void Window::_onWindowResize(GLFWwindow* window)
		{
			map<GLFWwindow*, Window*>::iterator windowIt = windowMap.find(window);
			if (windowIt == windowMap.end()) return;

			Window* win = windowIt->second;
			list<EventListener*>::iterator it = win->_listeners.begin();
			while (it != win->_listeners.end())
				(*(it++))->windowDidResize(win);
		}


		Window::Window(ca::gl::ScreenRenderer* renderer)
		{
			_renderer = renderer;
			resetHints();
		}


		Window::~Window()
		{
			glfwDestroyWindow(_window);
		}


		void Window::update()
		{
			if (_window == nullptr)
			{
				chaos::info("Unable to update window: window has not been opened.");
				return;
			}

			glfwMakeContextCurrent(_window);
			_renderer->render();
			glfwSwapBuffers(_window);
		}


		void Window::addEventListener (EventListener* listener)
		{
			_listeners.push_back(listener);
		}


		bool Window::hasEventListener (EventListener* listener)
		{
			list<EventListener*>::iterator it = _listeners.begin();
			while (it != _listeners.end() || (*it) != listener) it++;
			return it != _listeners.end();
		}


		bool Window::hasEventListeners()
		{
			return !_listeners.empty();
		}


		void Window::removeEventListener (EventListener* listener)
		{
			list<EventListener*>::iterator it = _listeners.begin();
			while (it != _listeners.end() || (*it) != listener) it++;
			_listeners.erase(it);
		}


		void Window::removeEventListeners()
		{
			_listeners.clear();
		}


		void Window::open(int width, int height, GLFWmonitor* monitor, GLFWwindow* share)
		{
			map<int, int>::iterator it = _hints.begin();
			while (it != _hints.end())
			{
				glfwWindowHint(it->first, it->second);
				it++;
			}

			_window = glfwCreateWindow(width, height, _title, monitor, share);
			if (!_window) throw new ca::glfw::Exception("Failed to open window");

			windowMap[_window] = this;
			glfwSetWindowCloseCallback(_window, _onWindowClose);
		}



		void Window::open(int widht, int height)
		{
			open(widht, height, nullptr, nullptr);
		}


		void Window::close ()
		{
			glfwSetWindowShouldClose(_window, GL_TRUE);
		}


		bool Window::willClose()
		{
			return glfwWindowShouldClose(_window) == GL_TRUE;
		}


		void Window::setTitle(const char* title)
		{
			_title = title;
		}


		const char* Window::getTitle ()
		{
			return _title;
		}


		map<int, int> Window::resetHints ()
		{
			map<int, int> old = _hints;

			_hints[GLFW_RESIZABLE] = GL_TRUE;
			_hints[GLFW_VISIBLE] = GL_TRUE;
			_hints[GLFW_DECORATED] = GL_TRUE;
			_hints[GLFW_FOCUSED] = GL_TRUE;
			_hints[GLFW_AUTO_ICONIFY] = GL_TRUE;
			_hints[GLFW_FLOATING] = GL_FALSE;
			_hints[GLFW_RED_BITS] = 8;
			_hints[GLFW_GREEN_BITS] = 8;
			_hints[GLFW_BLUE_BITS] = 8;
			_hints[GLFW_ALPHA_BITS] = 8;
			_hints[GLFW_DEPTH_BITS] = 24;
			_hints[GLFW_STENCIL_BITS] = 8;
			_hints[GLFW_ACCUM_RED_BITS] = 0;
			_hints[GLFW_ACCUM_GREEN_BITS] = 0;
			_hints[GLFW_ACCUM_BLUE_BITS] = 0;
			_hints[GLFW_ACCUM_ALPHA_BITS] = 0;
			_hints[GLFW_AUX_BUFFERS] = 0;
			_hints[GLFW_SAMPLES] = 0;
			_hints[GLFW_REFRESH_RATE] = GLFW_DONT_CARE;
			_hints[GLFW_STEREO] = GL_FALSE;
			_hints[GLFW_SRGB_CAPABLE] = GL_FALSE;
			_hints[GLFW_DOUBLEBUFFER] = GL_TRUE;
			_hints[GLFW_CLIENT_API] = GLFW_OPENGL_API;
			_hints[GLFW_CONTEXT_VERSION_MAJOR] = 1;
			_hints[GLFW_CONTEXT_VERSION_MINOR] = 0;
			_hints[GLFW_CONTEXT_ROBUSTNESS] = GLFW_NO_ROBUSTNESS;
			_hints[GLFW_CONTEXT_RELEASE_BEHAVIOR] = GLFW_ANY_RELEASE_BEHAVIOR;
			_hints[GLFW_OPENGL_FORWARD_COMPAT] = GL_FALSE;
			_hints[GLFW_OPENGL_DEBUG_CONTEXT] = GL_FALSE;
			_hints[GLFW_OPENGL_PROFILE] = GLFW_OPENGL_ANY_PROFILE;
			
			return old;
		}

		void Window::setHint(int name, int value)
		{
			_hints[name] = value;
		}


		int Window::getHint(int name)
		{
			return _hints[name];
		}


		void Window::setOpenGLProfile(int profile)
		{
			setHint(GLFW_OPENGL_PROFILE, profile);
		}


		int Window::getOpenGLProfile()
		{
			return getHint(GLFW_OPENGL_PROFILE);
		}


		void Window::setContextVersion(int major, int minor)
		{
			setHint(GLFW_CONTEXT_VERSION_MAJOR, major);
			setHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		}


		void Window::getContextVersion(int *major, int *minor)
		{
			*major = getHint(GLFW_CONTEXT_VERSION_MAJOR);
			*minor = getHint(GLFW_CONTEXT_VERSION_MINOR);
		}
	} /* namespace glfw */
} /* namespace ca */
