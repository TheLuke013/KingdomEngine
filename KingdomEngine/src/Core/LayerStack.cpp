#include "KingdomEngine/Core/LayerStack.h"

namespace KE
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (auto layer : layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.push_back(layer);
	}

	void LayerStack::RemoveLayer(Layer* layer)
	{
		std::string name = layer->GetName();
		for (auto layer = layers.begin(); layer != layers.end(); ++layer)
		{
			if ((*layer)->GetName() == name)
			{
				layers.erase(layer);
				break;
			}
		}
	}

	void LayerStack::UpdateLayers()
	{
		for (auto layer : layers)
		{
			layer->Update();
		}
	}

	void LayerStack::InitLayers()
	{
		for (auto layer : layers)
		{
			layer->OnReady();
		}
	}

	void LayerStack::UpdateEventLayers(Event e)
	{
		for (auto layer : layers)
		{
			layer->_OnEvent(e);
		}
	}
}