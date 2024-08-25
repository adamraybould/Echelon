
local function fn()
	local inst = CreateEntity() -- Called from main.lua

	print("Gunbot Online")
	return inst
end

return Prefab("gunbot", fn)