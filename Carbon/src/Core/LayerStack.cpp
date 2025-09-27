#include "LayerStack.h"
#include <algorithm>

namespace Carbon
{
	void LayerStack::PushLayer(Layer* layer)
	{
		layers.emplace(layers.end()-overlaycount, layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(begin(), end(), layer);
		if (it != end())
		{
			layers.erase(it);
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers.emplace(layers.end(), overlay);
		overlaycount++;
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto it = std::find(beginOverlay(), end(), layer);
		if (it != end())
		{
			layers.erase(it);
			overlaycount--;
		}
	}
}