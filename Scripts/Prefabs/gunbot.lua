
local assets =
{
	Asset("SPRITE", "Mobs/Robots/gunbot", 36)
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()

	inst.Transform:SetPosition(Vector2(GetRandomRange(-500, 500), GetRandomRange(-500, 500)))

	inst.entity:AddRigidbody()

	inst:AddComponent("health")
	inst.components.health:SetMaxHealth(100)

	--inst:AddComponent("movement")

	inst:AddTag("robot")

	return inst
end

return Prefab("gunbot", fn, assets)