#ifndef GUNBOT_H
#define GUNBOT_H
#include "Engine/Core/ECS/Entity.h"

namespace Core::Components { class SpriteRenderer; }

namespace Echelon
{
	namespace Entities::Mobs
    {
	    class Gunbot : public Entity
	    {
	    private:
	        SpriteRenderer* m_renderer;

	    public:
	        Gunbot(const char* name);

	        void Initialize() override;
	        void Update(float delta) override;
	        void Render(Renderer& renderer) override;
	    };
    }
}

#endif //GUNBOT_H
