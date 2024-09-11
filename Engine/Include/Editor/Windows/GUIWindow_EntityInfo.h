#ifndef GUIWINDOW_ENTITYINFO_H
#define GUIWINDOW_ENTITYINFO_H
#include "Editor/GUIWindow.h"
#include "Graphics/Sprite.h"

namespace Scene { class Entity; }
namespace Scene::Components { class SpriteRenderer; }

namespace Core
{
    namespace Editor
    {
        class GUIWindow_EntityInfo : public GUIWindow
        {
            const UInt MAX_WINDOW_DISTANCE = 800;

        private:
            Scene::Entity* m_pEntity = nullptr;
            Scene::Components::SpriteRenderer* m_pEntityRenderer;
            Graphics::Sprite* m_pEntitySprite = nullptr;

            Vector2F m_windowOffset;
            float m_windowDistance;

            float m_windowExpansionWidth = 0.0f;
            float m_windowExpansionHeight = 0.0f;

        public:
            GUIWindow_EntityInfo(EngineGUI& engineGUI);

            void OpenWindow() override;
            void CloseWindow() override;

            void Update(float delta) override;
            void Render() override;

        private:
            Vector2F GetEntityScreenPosition(const Scene::Entity& entity) const;
            static ImTextureID GetTextureID(const Graphics::Texture2D& texture) { return reinterpret_cast<ImTextureID>(reinterpret_cast<intptr_t>(&texture.GetRawTexture())); }

            void DisplayInfo(const Scene::Entity& entity);

            void DisplaySprite() const;
            void DisplayComponentInfo() const;
            void DisplayTags() const;
        };
    }
}

#endif //GUIWINDOW_ENTITYINFO_H
