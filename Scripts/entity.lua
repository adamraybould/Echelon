---@class Entity
require("class")

StopUpdatingComponents = {}

local Components = {}

local function LoadComponent(name)
	if Components[name] == nil then
		Components[name] = require("Components/"..name)
		assert(Components[name], "Failed to load Component "..name)
	end

	return Components[name]
end

local function AddListener(table, event, inst, fn)
	local listeners = table[event]
	if not listeners then
		listeners = {}
		table[event] = listeners
	end

	local listener_fns = listeners[inst]
	if not listener_fns then
		listener_fns = {}
		listeners[inst] = listener_fns
	end

	table.insert(listener_fns, fn)
end

local function RemoveListener(table, event, inst, fn)
	if table then
		local listeners = table[event]
		if listeners then
			local listener_fns = listeners[inst]
			if listener_fns then
				RemoveByValue(listener_fns, fn)

				if next(listener_fns) == nil then
					listeners[inst] = nil
				end
			end

			if next(listeners) == nil then
				table[event] = nil
			end
		end
	end
end

Entity = Class(function(self, entity)
	self.entity = entity
	self.components = {}
	self.GUID = entity.GUID
	self.name = nil

	self.updatecomponents = nil
	self.eventlisteners = nil
end)

function Entity:AddComponent(name)
	local lowerName = string.lower(name)

	local cmp = LoadComponent(name)
	if not cmp then
		assert(cmp, "Failed to load Component: '".. name)
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

---Enables the Component to start updating each frame
---@param component table
function Entity:StartUpdatingComponent(component)
	if not self:IsValid() then
		return
	end

	-- Add any Entities with Updating Components to a new Array
	-- Entities get added to a New Updating Entities Array, that'll be added to the main Entities array
	-- after processing the frame
	if not self.updatecomponents then
		self.updatecomponents = {}
		NewUpdatingEntities[self.GUID] = self
	end

	-- Removes Component from the Array of Non-Updating Components
	if StopUpdatingComponents[component] == self then
		StopUpdatingComponents[component] = nil
	end

	local componentname = nil
	for k, v in pairs(self.components) do
		if v == component then
			componentname = k
			break
		end
	end

	self.updatecomponents[component] = componentname or "Component"
end


---Stops the Component from updating each frame
---@param component table
function Entity:StopUpdatingComponent(component)
	if self.updatecomponents then
		StopUpdatingComponents[component] = self
	end
end

-- Is called at the end of the Update Loop
function Entity:StopUpdatingComponent_Deferred(component)
	if self.updatecomponents then
		self.updatecomponents[component] = nil

		if IsTableEmpty(self.updatecomponents) then
			self.updatecomponents = nil
			UpdatingEntities[self.GUID] = nil
			NewUpdatingEntities[self.GUID] = nil
		end
	end
end

function Entity:GetComponentName(component)
	for k, v in pairs(self.components) do
		if v == component then
			return k
		end
	end

	error("No Component Found")
	return "Component"
end

function Entity:SetName(name)
	self.name = name
	self.entity:SetName(name)
end

function Entity:AddTag(tag)
	self.entity:AddTag(tag)
end

function Entity:RemoveTag(tag)
	self.entity:RemoveTag(tag)
end

function Entity:HasTag(tag)
	return self.entity:HasTag(tag)
end

function Entity:HasTags(tags)
	for i = 1, #tags do
		if not self:HasTag(tags[i]) then
			return false
		end
	end

	return true
end

function Entity:HasOneOfTags(tags)
	for i = 1, #tags do
		if self:HasTag(tags[i]) then
			return true
		end
	end

	return false
end

function Entity:IsValid()
	return true
end

function Entity:BroadcastEvent(event, data)
	if self.eventlisteners then
		local listeners = self.eventlisteners[event]
		if listeners then
			for entity, fns in pairs(listeners) do
				for i, fn in ipairs(fns) do
					fn(self, data)
				end
			end
		end
	end
end

function Entity:ListenForEvent(event, fn, source)
	source = source or self

	if not source.eventlisteners then
		source.eventlisteners = {}
	end

	AddListener(source.eventlisteners, event, self, fn)
end

function Entity:StopListeningForEvent(event, fn, source)
	assert(type(fn) == "function")

	source = source or self
	RemoveListener(source.eventlisteners, event, self, fn)
end

function Entity:GetPosition()
	return Vector2(self.Transform:GetWorldPosition().x, self.Transform:GetWorldPosition().y)
end

function Entity:GetRotation()
	return self.Transform:GetRotation()
end