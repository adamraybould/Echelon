
local assets =
{
	Asset("SPRITE", "Mobs/Carbon/Human")
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRigidbody()
	inst.entity:AddRenderer()
	inst.entity:AddAnimator()

	inst.Transform:SetPosition(Vector2(488, 128))

	inst:AddComponent("movement")
	inst:AddComponent("playercontroller")

	inst:AddTag("player")
	inst:AddTag("human")
	inst:AddTag("carbon")

	return inst
end

return Prefab("player", fn, assets)