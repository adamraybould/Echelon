
local function IsMovementButtonDown()
	return Input:IsKeyDown(KEY_W) or Input:IsKeyDown(KEY_S) or Input:IsKeyDown(KEY_A) or Input:IsKeyDown(KEY_D)
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
	if Input:IsKeyDown(KEY_W) then
		movement = Vector2(movement.x, -1.0)
		self.inst.Animator:PlayAnimation("Move_U")
	elseif Input:IsKeyDown(KEY_S) then
		movement = Vector2(movement.x, 1.0)
		self.inst.Animator:PlayAnimation("Move_D")
	end

	if Input:IsKeyDown(KEY_A) then
		movement = Vector2(-1.0, movement.y)
		self.inst.Animator:PlayAnimation("Move_L")
	elseif Input:IsKeyDown(KEY_D) then
		movement = Vector2(1.0, movement.y)
		self.inst.Animator:PlayAnimation("Move_R")
	end

	-- Sprinting
	if Input:IsKeyDown(KEY_SHIFT) then
		self.inst.components.movement:RunInDirection(movement:Normalise(), delta)
	else
		self.inst.components.movement:WalkInDirection(movement:Normalise(), delta)
	end
end

return PlayerController