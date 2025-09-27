#pragma once
#include <Layer.h>

namespace Carbon {

	class LayerStack
	{
	public:
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator beginOverlay() { return layers.end() - overlaycount; }
		std::vector<Layer*>::iterator end() { return layers.end(); }
		uint32_t size() { return layers.size(); };
	private:
		std::vector<Layer*> layers;
		int overlaycount = 0;
	};

}

