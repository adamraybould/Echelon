
local assets =
{
	Asset("SPRITE", "Mobs/Human")
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()
	inst.entity:AddRigidbody()
	inst.entity:AddAnimator()

	inst.Rigidbody:CreateDynamicBody()

	inst.Transform:SetPosition(Vector2(488, 128))
	inst.Animator:PlayAnimation("Idle(D)")

	inst:AddComponent("health")
	inst.components.health:SetMaxHealth(TUNING.BASE_PLAYER_HEALTH)

	inst:AddComponent("race")
	inst.components.race:SetRace(RACES.HUMAN)

	inst:AddComponent("locomotor")
	inst:AddComponent("playercontroller")

	inst:AddTag("Player")

	return inst
end

return Prefab("player", fn, assets)