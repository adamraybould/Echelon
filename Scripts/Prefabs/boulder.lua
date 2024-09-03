
local assets =
{
	Asset("SPRITE", "Objects/Rocks", 0)
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()
	inst.entity:AddRigidbody()

	inst.Rigidbody:CreateStaticBody()

	inst:AddTag("Boulder")

	return inst
end

return Prefab("boulder", fn, assets)