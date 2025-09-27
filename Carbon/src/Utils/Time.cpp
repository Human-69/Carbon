#include "Time.h"

namespace Carbon
{
	Timer Time::t;
	float Time::lastframetime = Time::t.GetElapsedTime();
	float Time::deltatime = 0.0f;
}