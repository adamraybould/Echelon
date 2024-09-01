#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#include "Component.h"
#include "Engine/Graphics/SpriteSheet.h"

namespace Core
{
    namespace Graphics { class Texture2D; class Sprite; }

    using namespace Graphics;
    namespace Components
    {
        class SpriteRenderer : public Component
        {
        private:
            Sprite* m_pSprite;
            UInt m_flipped;

            Rectangle m_source;
            Vector2 m_spriteScale;

        public:
            SpriteRenderer(Entity& owner);
            void SetupEmbedding(lua_State* L) override;

            void Initialize() override;
            void Update(float delta) override;
            void Render(Renderer& renderer) override;
            void Destroy() override;

            void SetSourceFromFrame(UInt frameIndex);

            void SetDisplaySource(UInt x, UInt y, UInt width, UInt height);
            Rectangle GetDisplaySource() const { return m_source; }

            Sprite& GetSprite() const;
        };
    }
}

#endif //SPRITERENDERER_H
