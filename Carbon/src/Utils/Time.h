#pragma once
#include <chrono>

namespace Carbon {
	struct Timestep
	{
		Timestep(float currentTime, float deltatime) : deltatime(), elapsedTime(currentTime) {}

		float elapsedTime;
		float deltatime;
	};

	class Timer
	{
	public:
		Timer() { Reset(); }

		void Reset() { start = std::chrono::high_resolution_clock::now(); };

		float GetElapsedTime() const { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() * 0.001f; };

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start;
	};

	class Time
	{
	public:
		static void OnUpdate()
		{
			float elapsed = t.GetElapsedTime();
			deltatime = elapsed - lastframetime;
			lastframetime = elapsed;
		};

		static Timestep GetTime() { return Timestep(t.GetElapsedTime(), deltatime); };
	private:
		static inline float lastframetime;
		static inline float deltatime;
		static inline Timer t;
	};
}