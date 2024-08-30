
local MainCamera = Class(function(self, inst)
	self.inst = inst
	self.target = nil
	self.currentpos = Vector2(0, 0)
	self.targetpos = Vector2(0, 0)

	self.followspeed = 50
	self.followrange = 30
	self.smoothing = 4
	self.canChange = true
end)

function MainCamera:Update(delta)
	if Input:IsKeyDown(KEY_F) and self.canChange then
		self:SetTarget(GetRandomItem(Entities))
		self.canChange = false
	end

	if self.target ~= nil then
		self.targetpos.x = self.target.Transform:GetWorldPosition().x
		self.targetpos.y = self.target.Transform:GetWorldPosition().y

		self.currentpos.x = Lerp(self.currentpos.x, self.targetpos.x, self.smoothing * delta)
		self.currentpos.y = Lerp(self.currentpos.y, self.targetpos.y, self.smoothing * delta)

		local distance = self.currentpos:Distance(self.targetpos)
		if distance < 20 then
			self.canChange = true
		end
	end

	-- Apply Properties to Engine Camera
	Engine:SetCameraPosition(self.currentpos)
end

function MainCamera:SetTarget(inst)
	self.target = inst

	if inst ~= nil then
		self.targetpos.x = self.target.Transform:GetWorldPosition().x
		self.targetpos.y = self.target.Transform:GetWorldPosition().y
	else
		self.target.x = 0
		self.target.y = 0
	end
end

function MainCamera:SnapToPosition(pos)
	self.currentpos.x = pos.x
	self.currentpos.y = pos.y
end

return MainCamera