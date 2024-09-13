
local LocoMotor = Class(function(self, inst)
	self.inst = inst

	self.walkspeed = TUNING.BASE_WALK_SPEED
	self.runspeed = TUNING.BASE_RUN_SPEED
	self.isrunning = false

	inst:AddTag("Locomotor")

	--self.inst:StartUpdatingComponent(self)
end)

function LocoMotor:Update(delta)
end

function LocoMotor:WalkInDirection(dir, delta)
	self.isrunning = false
	self.inst.Rigidbody:ApplyImpulse(dir * (self:GetWalkSpeed() * delta))
end

function LocoMotor:RunInDirection(dir, delta)
	self.isrunning = true
	self.inst.Rigidbody:ApplyImpulse(dir * (self:GetRunSpeed() * delta))
end

function LocoMotor:GetWalkSpeed()
	return self.walkspeed
end

function LocoMotor:GetRunSpeed()
	return self.runspeed
end

return LocoMotor