
local assets =
{
	Asset("SPRITE", "Objects/Tree", 0)
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()
	inst.entity:AddRigidbody()

	inst.Rigidbody:CreateStaticBody()

	inst:AddTag("Tree")

	return inst
end

return Prefab("tree", fn, assets)