#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#include "Component.h"

namespace Engine::Graphics
{
    class Texture2D;
    class Sprite;
}

using namespace Engine::Graphics;
namespace Engine::ECS
{
    class SpriteRenderer : public Component
    {
    private:
        Sprite* m_pSprite;
        UInt m_flipped;

    public:
        SpriteRenderer(Entity& owner, Sprite& sprite);

        void Initialize() override;
        void Update(float delta) override;
        void Render(Renderer& renderer) override;
        void Destroy() override;

        /* Sets the Sprite source rect to a new Frame. Only works with Sprite Sheets */
        void SetSpriteFrame(UInt frameIndex) const;
    };
}

#endif //SPRITERENDERER_H
