#include "Rendering/IRenderable.h"

#include "Core/IO/Renderer.h"

using namespace Core;
namespace Rendering
{
    IRenderable::IRenderable()
    {
        SetActiveRendering(true);
    }
}
