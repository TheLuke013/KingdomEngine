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

		void PushLayer(Layer* layer);
		void RemoveLayer(Layer* layer);

		void UpdateLayers();
		void InitLayers();
		void OnEventLayers(Event& e);

	private:
		std::vector<Layer*> layers;
	};
}

#endif
