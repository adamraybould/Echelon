#ifndef GUIWINDOW_ENTITYINFO_H
#define GUIWINDOW_ENTITYINFO_H
#include "Engine/Core/Editor/GUIWindow.h"
#include "Engine/Graphics/Sprite.h"

namespace Core
{
    class Entity;

    namespace Editor
    {
        class GUIWindow_EntityInfo : public GUIWindow
        {
        private:
            Entity* m_pEntity = nullptr;
            Graphics::Sprite* m_pEntitySprite = nullptr;

            const int WINDOW_WIDTH = 180;
            const int WINDOW_HEIGHT = 250;
            Vector2 m_position;

        public:
            GUIWindow_EntityInfo(EngineGUI& engineGUI);

            void OpenWindow() override;
            void CloseWindow() override;

            void Update(float delta) override;
            void Render() override;

        private:
            Vector2 GetEntityScreenPosition(const Entity& entity);
            ImTextureID GetTextureID(const Graphics::Texture2D& texture) { return (ImTextureID)(intptr_t)&texture.GetRawTexture(); }
        };
    }
}

#endif //GUIWINDOW_ENTITYINFO_H
