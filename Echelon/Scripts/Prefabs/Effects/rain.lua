
local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()

	inst:AddTag("FX")

	return inst
end

return Prefab("rain", fn)