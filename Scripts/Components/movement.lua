
local Movement = Class(function(self, inst)
	self.inst = inst

	self.walkspeed = TUNING.BASE_RUN_SPEED
	self.runspeed = TUNING.BASE_RUN_SPEED
	self.isrunning = false

	self.inst:StartUpdatingComponent(self)
end)

function Movement:Update(delta)
	self:MoveInDirection(Vector2(1, 1))
end

function Movement:MoveInDirection(direction)
	self.inst.Transform:AddPosition(direction)
end

function Movement:GetWalkSpeed()
	return self.walkspeed
end

function Movement:GetRunSpeed()
	return self.runspeed
end

return Movement