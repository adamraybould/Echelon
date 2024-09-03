
local assets =
{
	Asset("SPRITE", "Mobs/Human")
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()
	inst.entity:AddRigidbody()
	inst.entity:AddAnimator()

	inst.Rigidbody:CreateDynamicBody()

	inst.Transform:SetPosition(Vector2(488, 128))
	inst.Animator:PlayAnimation("Idle(D)")

	inst:AddComponent("locomotor")
	inst:AddComponent("playercontroller")

	inst:AddTag("Player")
	inst:AddTag("Human")

	return inst
end

return Prefab("player", fn, assets)