#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include <string>
#include <vector>

namespace MapleEngine
{
	struct ENGINE_API Frame
	{
		// The index of this frame within the Sprite Sheet
		int Index;

		// The animation duration of this frame
		float Duration;

		Frame(int index, float duration = 0.1f)
		{
			Index = index;
			Duration = duration;
		}
	};

	struct ENGINE_API Animation
	{
		// Name of the Animation
		std::string Name;

		// List of Frames within the Animation
		std::vector<Frame> Frames;

		// Is the Animation Looping?
		bool IsLooping = true;

		// Is the Animation Valid? Does it have any Frames?
		bool IsNull;

		Animation(const char* animationName)
		{
			Name = animationName;
			IsNull = true;
		}

		/* Adds a Frame to Animation */
		void AddAnimationFrame(Frame frame)
		{
			IsNull = false;
			Frames.push_back(frame);
		}

		/* Returns the Index of the First Animation Frame */
		int GetStartIndex() const { return Frames[0].Index; }

		/* Returns the Index of the Last Animation Frame */
		int GetLastIndex() const { return Frames[Frames.size() - 1].Index; }

		int GetFrameCount() const { return Frames.size(); }
	};
}