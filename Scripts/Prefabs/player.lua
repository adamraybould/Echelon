
local assets =
{
	Asset("SPRITE", "Mobs/Carbon/HumanBase")
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()

	inst.Transform:SetPosition(Vector2(488, 128))

	inst.entity:AddRigidbody()
	--inst.Rigidbody:SetLinearDamping(30.0)

	inst:AddComponent("movement")
	inst:AddComponent("playercontroller")

	inst:AddTag("player")
	inst:AddTag("human")
	inst:AddTag("carbon")

	return inst
end

return Prefab("player", fn, assets)