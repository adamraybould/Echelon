#ifndef ANIMATION_H
#define ANIMATION_H
#include "Core/TypeDefs.h"

using namespace Core;
namespace Graphics
{
    struct AnimationFrame
    {
        int X;
        int Y;
        int Width;
        int Height;
        int Duration;

        AnimationFrame(const int x, const int y, const int width, const int height, const int duration)
                : X(x), Y(y), Width(width), Height(height), Duration(duration) {}
    };

    struct Animation
    {
    public:
        String Name;

        std::vector<AnimationFrame> Frames;
        bool Looping = true;

    public:
        Animation() = default;

        void SetName(const String& name) { Name = name; }
        void AddFrame(const AnimationFrame frame) { Frames.push_back(frame); }

        AnimationFrame& GetFrame(const UInt index) { return Frames.at(index); }
        UInt GetFrameLength() const { return Frames.size(); }
    };
}

#endif //ANIMATION_H
