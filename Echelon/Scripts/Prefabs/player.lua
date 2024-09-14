
local assets =
{
	Asset("SPRITE", "Mobs/Human"),
	Asset("AUDIO", "Audio/SFX.bank")
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()
	inst.entity:AddRigidbody()
	inst.entity:AddAnimator()
	inst.entity:AddSoundEmitter()
	inst.entity:AddLightSource()

	inst.Rigidbody:CreateDynamicBody()

	inst.Animator:PlayAnimation("Idle(D)")

	inst.Light:SetIntensity(0.75);
	inst.Light:SetColor(255, 255, 255)
	inst.Light:SetRadius(2)

	inst:AddComponent("health")
	inst.components.health:SetMaxHealth(TUNING.BASE_PLAYER_HEALTH)

	inst:AddComponent("race")
	inst.components.race:SetRace(RACES.HUMAN)

	inst:AddComponent("role")

	inst:AddComponent("locomotor")
	inst:AddComponent("playercontroller")

	inst:AddTag("Player")

	return inst
end

return Prefab("player", fn, assets)