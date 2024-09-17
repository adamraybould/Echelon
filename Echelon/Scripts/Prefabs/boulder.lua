
local assets =
{
	Asset("SPRITE", "Objects/Terrain/Rocks", 0)
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()
	inst.entity:AddRigidbody()

	inst.Rigidbody:CreateStaticBody()

	inst:AddComponent("inspectable")

	inst:AddTag("Boulder")

	return inst
end

return Prefab("boulder", fn, assets)