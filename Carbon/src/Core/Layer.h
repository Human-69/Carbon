#pragma once

#include "cbpch.h"
#include <Events/Event.h>

namespace Carbon {

	class Layer
	{
	public:
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;

		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& event) = 0;
	};

}
