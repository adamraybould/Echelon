---@class Main

require("prefablist")
require("class")
require("prefab")
require("entity")

function ScriptPath()
	local str = debug.getinfo(2, "S").source:sub(2)
	return str:match("(.*/)")
end

Prefabs = {}
Entities = {}

function CreateEntity(name)
	local base = God:CreateEntity()
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

	local guid = God:SpawnPrefab(name)
	Entities[guid].name = name
	return Entities[guid]
end

function RegisterPrefab(prefab)
	Prefabs[prefab.name] = prefab
	God:RegisterPrefab(prefab.name)
end

PREFABDEFINITIONS = {}

function LoadPrefab(prefabFile)
	local path = prefabFile .. ".lua"

	print("Loading Prefab File: ".. prefabFile);
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
	LoadPrefab(ScriptPath().. "Prefabs/".. file)
end