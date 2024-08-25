
local function fn()
	local inst = CreateEntity()

	print("Drillbot Online")
	return inst
end

return Prefab("drillbot", fn)