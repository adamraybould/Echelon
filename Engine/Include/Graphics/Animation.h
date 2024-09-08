#ifndef ANIMATION_H
#define ANIMATION_H
#include "Core/TypeDefs.h"

using namespace Core;
namespace Graphics
{
    struct Frame
    {
        int X;
        int Y;
        int Width;
        int Height;
        int Duration;

        Frame(const int x, const int y, const int width, const int height, const int duration)
                : X(x), Y(y), Width(width), Height(height), Duration(duration) {}
    };

    struct Animation
    {
    public:
        String Name;

        std::vector<Frame> Frames;
        bool Looping = true;

    public:
        Animation() = default;

        void SetName(const String& name) { Name = name; }
        void AddFrame(const Frame frame) { Frames.push_back(frame); }

        Frame& GetFrame(const UInt index) { return Frames.at(index); }
        UInt GetFrameLength() const { return Frames.size(); }
    };
}

#endif //ANIMATION_H
