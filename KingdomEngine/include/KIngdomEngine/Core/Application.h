#ifndef APPLICATION_H
#define APPLICATION_H

#include "KingdomEngine/Core/Log.h"

namespace KE
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		virtual void OnReady() = 0;
		virtual void Update() = 0;

	private:
		bool isRunning = true;
	};

	Application* CreateApplication();
}

#endif