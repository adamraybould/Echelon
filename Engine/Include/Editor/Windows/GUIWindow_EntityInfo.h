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
            const int WINDOW_WIDTH = 350;
            const int WINDOW_HEIGHT = 250;

        private:
            Scene::Entity* m_pEntity = nullptr;
            Scene::Components::SpriteRenderer* m_pEntityRenderer;
            Graphics::Sprite* m_pEntitySprite = nullptr;

            ImVec2 m_windowPos;

            float m_offsetX;
            float m_offsetY;

            float m_windowExpansionWidth = 0.0f;
            float m_windowExpansionHeight = 0.0f;

        public:
            GUIWindow_EntityInfo(EngineGUI& engineGUI);

            void OpenWindow() override;
            void CloseWindow() override;

            void Update(float delta) override;
            void Render() override;

            ImVec2 GetWindowPosition() override;
            ImVec2 GetWindowSize() override;

        private:
            Vector2F GetEntityScreenPosition(const Scene::Entity& entity) const;
            ImTextureID GetTextureID(const Graphics::Texture2D& texture) { return (ImTextureID)(intptr_t)&texture.GetRawTexture(); }

            void DisplayInfo(const Scene::Entity& entity);

            void DisplaySprite();
            void DisplayComponentInfo() const;
            void DisplayTags() const;
        };
    }
}

#endif //GUIWINDOW_ENTITYINFO_H
