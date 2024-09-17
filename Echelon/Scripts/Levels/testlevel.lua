
local function Init()
	local level = LevelManager:GetLevel("testlevel")
	level:LoadMap("Map")

	print("Test Level Initialised")
end

return Level("testlevel", Init)