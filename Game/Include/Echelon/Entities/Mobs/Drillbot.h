#ifndef DRILLBOT_H
#define DRILLBOT_H
#include "Engine/Core/ECS/Entity.h"

namespace Core::Components { class SpriteRenderer; }

namespace Echelon
{
	namespace Entities::Mobs
    {
	    class Drillbot : public Entity
	    {
	    private:
	        SpriteRenderer* m_renderer;

	    public:
	        Drillbot(const char* name);

	        void Initialize() override;
	        void Update(float delta) override;
	        void Render(Renderer& renderer) override;
	    };
    }
}

#endif //DRILLBOT_H
