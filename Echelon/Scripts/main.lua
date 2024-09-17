---@class Main

require("constants")
require("maths")
require("util")
require("prefablist")
require("class")
require("prefab")
require("entity")
require("update")
require("Levels/level")

Prefabs = {}
Entities = {}
UpdatingEntities = {}
NewUpdatingEntities = {}
StopUpdatingEntities = {}

local MainCamera = require("camera")
Camera = MainCamera()

function CreateEntity(name)
	local base = World:CreateEntity()
	local guid = base.GUID
	local entity = Entity(base)

	if name ~= nil then
		entity.name = name
	end

	Entities[guid] = entity
	return Entities[guid]
end

function SpawnPrefab(name)
	name = string.sub(name, string.find(name, "[^/]*$"))

	local guid = World:SpawnPrefab(name)
	return Entities[guid]
end

function SpawnMultiplePrefabs(name, num)
	for i = 1, num, 1 do
		local prefab = SpawnPrefab(name)
		prefab.Rigidbody:SetPosition(Vector2(GetRandomRange(-500, 500), GetRandomRange(-500, 500)))
	end
end

function RegisterPrefab(prefab)
	Prefabs[prefab.name] = prefab
	World:RegisterPrefab(prefab.name, prefab)
end

PREFABDEFINITIONS = {}

function LoadPrefab(prefabFile)
	local path = prefabFile .. ".lua"

	local prefab = loadfile(path)
	assert(prefab, "Failed to load Prefab: '".. prefabFile.. "' at '"..path.."'")
	if type(prefab) == "string" then
		local errorMessage = "Error loading file: '"..path.."'\n"..fn

		print(errorMessage)
		assert(false, errorMessage)
	end
	assert(type(prefab) == "function", "Prefab file doesn't return a callable chunk: "..prefabFile)

	local ret = {prefab()}
	if ret then
		for i,val in ipairs(ret) do
			if type(val)== "table" and val.is_a and val:is_a(Prefab) then
				RegisterPrefab(val)
				PREFABDEFINITIONS[val.name] = val
			end
		end
	end

	return ret
end

local Scripts = {}

function LoadScript(fileName)
	if not Scripts[fileName] then
		local script = loadfile(fileName)
		assert(type(script) == "function", script)

		Scripts[fileName] = script() -- Calls the fn() function
	end

	return Scripts[fileName]
end

function RunScript(fileName)
	local script = LoadScript(fileName)
	if script then
		script() -- Calls the fn() function
	end
end

-- Register Prefabs
for i, file in ipairs(PREFABFILES) do
	LoadPrefab(GetScriptPath().. "Prefabs/".. file)
end

function OnEntityWake(guid)
	local inst = Entities[guid]
	if inst then
		if inst.OnEntityWake then
			inst:OnEntityWake()
		end

		for k, v in pairs(inst.components) do
			if v.OnEntityWake then
				v:OnEntityWake()
			end
		end
	end
end

function RegisterLevel(file)
	local path = file .. ".lua"

	local level = loadfile(path)
	assert(level, "Failed to load Level: '".. file.. "' at '"..path.."'")
	if type(level) == "string" then
		local errorMessage = "Error loading file: '"..path.."'\n"

		print(errorMessage)
		assert(false, errorMessage)
	end

	assert(type(level) == "function", "Level file doesn't return a callable chunk: "..file)

	local ret = {level()}
	if ret then
		for i, val in ipairs(ret) do
			if type(val) == "table" and val.is_a and val:is_a(Level) then
				LevelManager:RegisterLevel(val.name, val)
			end
		end
	end
end