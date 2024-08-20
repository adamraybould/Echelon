#ifndef MAINLEVEL_H
#define MAINLEVEL_H
#include "Entities/PlayerCharacter.h"
#include "States/Level.h"
#include "Systems/EntityManager.h"

using namespace Engine::States;
namespace Echelon::Levels
{
    class MainLevel : public Level
    {
    private:
        Entities::PlayerCharacter* m_pPlayer;

    public:
        MainLevel();

        void Initialize() override;
        void Update(float delta) override;
        void Render(SDL_Renderer& renderer) override;

        template<typename T, typename... Args>
        inline T& CreateEntity(const Vector2 position = {0, 0}, const float rotation = 0.0f, const Vector2 scale = {1, 1}, Args... args)
        {
            T& entity = GetEntityManager().CreateEntity<T>(std::forward<Args>(args)...);

            Entity& baseEntity = static_cast<Entity&>(entity);
            baseEntity.Transform().Position = position;
            baseEntity.Transform().Rotation = rotation;
            baseEntity.Transform().Scale = scale;

            return entity;
        }
    };
}

#endif //MAINLEVEL_H
