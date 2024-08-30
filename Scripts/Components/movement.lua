
local Movement = Class(function(self, inst)
	self.inst = inst

	self.walkspeed = TUNING.BASE_WALK_SPEED
	self.runspeed = TUNING.BASE_RUN_SPEED
	self.isrunning = false

	self.inst:StartUpdatingComponent(self)
end)

function Movement:Update(delta)
end

function Movement:WalkInDirection(direction, delta) -- TODO: remove delta eventually
	self.inst.Rigidbody:ApplyImpulse(direction * self:GetWalkSpeed())
end

function Movement:RunInDirection(direction, delta) -- TODO: remove delta eventually
	self.inst.Rigidbody:ApplyImpulse(direction * self:GetRunSpeed())
end

function Movement:GetWalkSpeed()
	return self.walkspeed
end

function Movement:GetRunSpeed()
	return self.runspeed
end

return Movement