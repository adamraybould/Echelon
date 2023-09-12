#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include "Component.h"
#include "Engine/Graphics/Sprite.h"

namespace MapleEngine
{
	class ENGINE_API SpriteRenderer : public Component
	{
	private:
		Sprite* m_pSprite;
		int m_flip;

	public:
		SpriteRenderer(Entity& entity);

		void Initialize() override;
		void Update(float dt) override;
		void Render() override;
		void Destroy() override;

		/* Set the Sprite to be Renderered */
		void SetSprite(Sprite& sprite);

		/* Set if the Sprite should be Flipped */
		void SetFlip(bool value);

		Sprite* GetSprite() { return m_pSprite; }
	};
}