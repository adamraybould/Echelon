
local bush1_assets =
{
	Asset("SPRITE", "Objects/Terrain/Bushes", 0)
}

local bush2_assets =
{
	Asset("SPRITE", "Objects/Bushes", 1)
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()
	inst.entity:AddRigidbody()

	inst.Rigidbody:CreateStaticBody()

	inst:AddTag("Bush")

	return inst
end

return Prefab("bush_1", fn, bush1_assets),
	Prefab("bush_2", fn, bush2_assets)