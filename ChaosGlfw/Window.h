/*
 * Window.h
 *
 *  Created on: 06.03.2016
 *      Author: chaos
 */

#ifndef _ChaosGlfw_Window_h_
#define _ChaosGlfw_Window_h_

#include <GLFW/glfw3.h>
#include <map>
#include <list>
#include <ChaosCore/core.h>
#include <ChaosGL/ScreenRenderer.h>
#include "Exception.h"

using namespace std;

namespace ca
{
	namespace glfw
	{
		class Window
		{

		public:
			class EventListener;

		private:

			/**
			 * Provides the title of the window
			 */
			const char* _title = "Unnamed Window";

			/**
			 * Provides a hint name to value map, which is used before
			 * opening the window
			 */
			map<int, int> _hints;

			/**
			 * Provides the glfw window object
			 */
			GLFWwindow* _window = nullptr;

			/**
			 * Provides the screen renderer
			 */
			ca::gl::ScreenRenderer* _renderer;

			/**
			 * Provides a list of listeners of this window
			 */
			list<EventListener*> _listeners;


			static void _onWindowClose (GLFWwindow* window);
			static void _onWindowResize (GLFWwindow* window);
			static void _onWindowMove (GLFWwindow* window);
			static void _onWindowFocus (GLFWwindow* window);
		public:

			/**
			 * Constructor of this class
			 */
			Window(ca::gl::ScreenRenderer* renderer);


			/**
			 * Destructor of this class
			 */
			virtual ~Window();


			/**
			 * Updates the window content by swapping the buffers and calling the renderer
			 */
			void update ();


			/**
			 * Adds a new window event listener
			 */
			void addEventListener (EventListener* listner);


			/**
			 * Determines if the listener has been added to this window
			 */
			bool hasEventListener (EventListener* listener);


			/**
			 * Determines if this window has listeners
			 */
			bool hasEventListeners ();


			/**
			 * Removes the accodring listener fromt his window
			 */
			void removeEventListener (EventListener* listener);


			/**
			 * Removes all listeners from this window
			 */
			void removeEventListeners ();


			/**
			 * Opens the window width given width and height
			 * @param width The width of the window
			 * @param height The height of the window
			 */
			void open (int width, int height);


			/**
			 * Opens the window width given width and height
			 * @param width The width of the window
			 * @param height The height of the window
			 */
			void open (int width, int height, GLFWmonitor* monitor, GLFWwindow* share);


			/**
			 * Closes the window
			 */
			void close ();

			/**
			 * Determines if the window will close or not
			 */
			bool willClose ();


			/**
			 * Sets the title of the window
			 * @param title The title of the window
			 */
			void setTitle (const char* title);


			/**
			 * Sets the title of the window
			 * @return The title of the window
			 */
			const char* getTitle ();


			/**
			 * Resets the all window hints to default and returns the old hints
			 * @return The old hint settings
			 */
			map<int, int> resetHints ();


			/**
			 * Sets a hint which is used before opening the window
			 * @param name The name of the window hint
			 * @param value The value of the window hint
			 */
			void setHint (int name, int value);


			/**
			 * Returns the value of the given window hint name
			 * @param
			 */
			int getHint (int name);


			/**
			 * Sets the hint for open gl profile
			 * @param profile
			 */
			void setOpenGLProfile (int profile);


			/**
			 * Returns the open gl profile hint value
			 * @return The OpenGL Profile hint value
			 */
			int getOpenGLProfile ();

			/**
			 * Sets the OpenGL context verison
			 * @param major
			 * @param minor
			 */
			void setContextVersion (int major, int minor);


			/**
			 * Returns the OpenGL context version
			 * @param major
			 * @param minor
			 */
			void getContextVersion (int* major, int *minor);


			class EventListener
			{
			public:
				virtual void windowWillClose (Window* window) {};
				virtual void windowDidResize (Window* window) {};
				virtual void windowDidMove (Window* window) {};
				virtual void windowGetsFocus (Window* window) {};
			};
		};

	} /* namespace glfw */
} /* namespace ca */

#endif /* WINDOW_H_ */
