
local assets =
{
	Asset("SPRITE", "Mobs/Carbon/Human", 0)
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()
	inst.entity:AddRigidbody()

	inst.Rigidbody:SetPosition(Vector2(GetRandomRange(-500, 500), GetRandomRange(-500, 500)))

	inst:AddTag("human")
	inst:AddTag("carbon")
	inst:AddTag("blank")

	return inst
end

return Prefab("blank", fn, assets)