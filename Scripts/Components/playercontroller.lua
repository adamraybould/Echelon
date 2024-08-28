
local function IsMovementButtonDown()
	return Input:IsKeyDown(KEY_MOVE_UP) or Input:IsKeyDown(KEY_MOVE_DOWN) or Input:IsKeyDown(KEY_MOVE_LEFT) or Input:IsKeyDown(KEY_MOVE_RIGHT)
end

local PlayerController = Class(function(self, inst)
	self.inst = inst

	self.inst:StartUpdatingComponent(self)
end)

function PlayerController:Update(delta)
	if not IsMovementButtonDown() then
		return
	end

	local movement = Vector2(0, 0)
	if Input:IsKeyDown(KEY_MOVE_UP) then
		movement = Vector2(movement.x, -1.0)
		self.inst.Renderer:SetFrame(1)
	elseif Input:IsKeyDown(KEY_MOVE_DOWN) then
		movement = Vector2(movement.x, 1.0)
		self.inst.Renderer:SetFrame(0)
	end

	if Input:IsKeyDown(KEY_MOVE_LEFT) then
		movement = Vector2(-1.0, movement.y)
		self.inst.Renderer:SetFrame(3)
	elseif Input:IsKeyDown(KEY_MOVE_RIGHT) then
		movement = Vector2(1.0, movement.y)
		self.inst.Renderer:SetFrame(2)
	end

	newpos = self.inst:GetPosition() + movement:Normalise() * (250 * delta)
	self.inst.Transform:SetPosition(newpos)
end

return PlayerController