
local assets =
{
	Asset("SPRITE", "Mobs/Carbon/HumanBase")
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()

	inst.Transform:SetPosition(Vector2(GetRandomRange(-500, 500), GetRandomRange(-500, 500)))

	inst:AddTag("human")
	inst:AddTag("carbon")
	inst:AddTag("blank")

	return inst
end

return Prefab("blank", fn, assets)