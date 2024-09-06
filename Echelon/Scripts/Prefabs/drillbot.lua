
local assets =
{
	Asset("SPRITE", "Mobs/Robots/Drillbot")
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRigidbody()
	inst.entity:AddRenderer()
	inst.entity:AddAnimator()

	inst:AddTag("robot")

	return inst
end

return Prefab("drillbot", fn, assets)