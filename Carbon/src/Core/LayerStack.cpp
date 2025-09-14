#include "LayerStack.h"
#include <algorithm>

namespace Carbon
{
	void LayerStack::PushLayer(Layer* layer)
	{
		layers.push_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(begin(), end(), layer);
		if (it != end())
		{
			layers.erase(it);
		}
	}
}