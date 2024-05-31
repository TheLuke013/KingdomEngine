#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include "KingdomEngine/Core/Layer.h"

#include <vector>

namespace KE
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void RemoveLayer(Layer* layer);

		void InitLayers();
		void UpdateLayers();
		void UpdateEventLayers(Event e);

	private:
		std::vector<Layer*> layers;
	};
}

#endif
