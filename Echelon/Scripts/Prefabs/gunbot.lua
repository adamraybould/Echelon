
local assets =
{
	Asset("SPRITE", "Mobs/Robots/Gunbot")
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRigidbody()
	inst.entity:AddRenderer()
	inst.entity:AddAnimator()

	inst:AddComponent("health")
	inst.components.health:SetMaxHealth(100)

	--inst:AddComponent("movement")

	inst:AddTag("robot")

	return inst
end

return Prefab("gunbot", fn, assets)