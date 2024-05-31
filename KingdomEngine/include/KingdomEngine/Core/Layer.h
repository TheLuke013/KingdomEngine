#ifndef LAYER_H
#define LAYER_H

#include "KingdomEngine/Core/Event.h"

#include <string>

namespace KE
{
	class Layer : public EventListener
	{
	public:
		Layer(const std::string& name)
			: layerName(name)
		{

		}
		virtual ~Layer() = default;

		std::string GetName() const { return layerName; }

		virtual void OnReady() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(Event e) = 0;

	private:
		std::string layerName;
	};
}

#endif
