#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include "States/Level.h"
#include "Core/TypeDefs.h"

using namespace Core::States;
namespace Core::Systems
{
    class EntityManager;

    class LevelManager
    {
    private:
        EntityManager& m_entityManager;

        Level* m_currentLevel; // Current Loaded Level
        Array<UniquePtr<Level>> m_levels; // All Possible Levels

    public:
        LevelManager(EntityManager& entityManager);
        ~LevelManager();

        void Initialise() const;
        void Update(float delta) const;
        void Render(Renderer& renderer) const;

        template<typename T>
        bool AddLevel()
        {
            static_assert(std::is_base_of_v<Level, T>, "T must be a subclass of Level");

            // Check if Level already exists
            for (UInt i = 0; i < m_levels.size(); i++)
            {
                if (typeid(m_levels[i]) == typeid(T))
                    return false;
            }

            m_levels.push_back(std::make_unique<T>(m_entityManager));
            return true;
        }

        bool LoadLevel(const UInt levelIndex)
        {
            if (levelIndex >= m_levels.size() || levelIndex < 0)
                return false;

            Level& level = *m_levels[levelIndex];
            m_currentLevel = &level;
            return true;
        }
    };
}

#endif //LEVELMANAGER_H
