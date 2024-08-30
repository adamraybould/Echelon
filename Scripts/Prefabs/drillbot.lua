
local assets =
{
	Asset("SPRITE", "Mobs/Robots/drillbot")
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()

	inst.Transform:SetPosition(Vector2(GetRandomRange(-500, 500), GetRandomRange(-500, 500)))

	inst.entity:AddRigidbody()

	inst:AddTag("robot")

	return inst
end

return Prefab("drillbot", fn, assets)