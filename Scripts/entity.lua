---@class Entity
require("class")

local Components = {}

local function LoadComponent(name)
	if Components[name] == nil then
		Components[name] = require("Components/"..name)
		assert(Components[name], "Failed to load Component "..name)
	end

	return Components[name]
end

Entity = Class(function(self, entity)
	self.entity = entity
	self.components = {}
	self.name = nil
	self.GUID = entity.GUID
end)

function Entity:AddComponent(name)
	local lowerName = string.lower(name)

	local cmp = LoadComponent(name)
	if not component then
		error("Component ".. name .. " does not exist")
	end

	local component = cmp(self)
	self.components[name] = component

	return component
end

function Entity:RemoveComponent(name)
	local component = self.components[name]
	if component then
		self.components[name] = nil

		if component.OnRemove then
			component.OnRemove()
		end
	end
end

function Entity:SetName(name)
	self.prefab = name
	self.entity:SetName(name)
end

function Entity:SetPrefab(name)
	self.prefab = name
	self.entity:SetPrefab(name)
end