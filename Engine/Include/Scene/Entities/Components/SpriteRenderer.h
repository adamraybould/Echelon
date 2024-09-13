#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#include "Component.h"
#include "Core/Maths/Vector2.h"
#include "Core/Maths/Rectangle.h"
#include "Rendering/Renderable.h"

namespace Graphics { class SpriteSheet; class Texture2DOLD; class Sprite; }
using namespace Graphics;

namespace Scene
{
    namespace Components
    {
        class SpriteRenderer final : public Component, Rendering::Renderable
        {
        private:
            Sprite* m_pSprite;
            UInt m_flipped;

            RectF m_source;
            Vector2F m_spriteScale;

            Vector2F m_uv0;
            Vector2F m_uv1;

        public:
            SpriteRenderer(Entity& owner);
            void SetupEmbedding(lua_State* L) override;

            void Initialize() override;
            void Update(float delta) override;
            void Destroy() override;

            void Render(Renderer& renderer) override;
            float GetDepth() override;

            void SetSourceFromFrame(UInt frameIndex);

            void SetDisplaySource(int x, int y, int width, int height);
            RectF GetDisplaySource() const { return m_source; }

            Sprite& GetSprite() const;
        };
    }
}

#endif //SPRITERENDERER_H
