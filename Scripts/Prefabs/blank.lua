
local assets =
{
	Asset("SPRITE", "Mobs/Human", 0)
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()
	inst.entity:AddRigidbody()
	inst.entity:AddAnimator()

	inst.Animator:PlayAnimation("Idle(D)")

	inst:AddTag("human")
	inst:AddTag("carbon")
	inst:AddTag("blank")

	return inst
end

return Prefab("blank", fn, assets)