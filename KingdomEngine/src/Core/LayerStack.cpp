#include "KingdomEngine/Core/LayerStack.h"

namespace KE
{
	LayerStack::LayerStack()
	{
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

	void LayerStack::OnEventLayers(Event& e)
	{
		for (auto layer : layers)
		{
			layer->OnEvent(e);
		}
	}
}