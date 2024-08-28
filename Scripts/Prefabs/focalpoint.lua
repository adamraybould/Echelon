
local function AttachToEntity(inst, entity)
	inst.Transform:SetParent(entity.Transform)
end

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	AttachToEntity(inst, Player)

	return inst
end

return Prefab("focalpoint", fn)