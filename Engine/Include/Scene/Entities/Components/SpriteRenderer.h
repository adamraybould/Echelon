#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#include "Component.h"
#include "Core/Maths/Vector2.h"
#include "Core/Maths/Rectangle.h"
#include "Rendering/IRenderable.h"

namespace Graphics { class SpriteSheet; class Texture2DOLD; class Sprite; struct Frame; }
using namespace Graphics;

namespace Scene
{
    namespace Components
    {
        class SpriteRenderer final : public Component, Rendering::IRenderable
        {
        private:
            Sprite* m_pSprite;
            SpriteSheet* m_pSpriteSheet;

            RectF m_src;
            RectF m_dest;
            UInt m_flipped;

        public:
            SpriteRenderer(Entity& owner);
            void SetupEmbedding(lua_State* L) override;

            void Initialize() override;
            void Destroy() override;

            void Render(Renderer& renderer) override;
            float GetDepth() override;

            void SetFrame(UInt index);

            void SetFrameSource(UInt x, UInt y, UInt width, UInt height);
            void SetFrameSource(RectU source);

            RectF GetFrameSource() const { return m_src; }
            RectF GetDisplayRect() const { return m_dest; }

            Vector2F GetFrameSize() const { return { m_src.Width, m_src.Height }; }

            Sprite& GetSprite() const { return *m_pSprite; }
            SpriteSheet* GetSpriteSheet() const { return m_pSpriteSheet; }
        };
    }
}

#endif //SPRITERENDERER_H
