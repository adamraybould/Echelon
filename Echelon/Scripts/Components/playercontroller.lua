
local animations =
{
	[KEY_W] = {movement = Vector2(0.0, 1.0), pressed = false, idle = "Idle(U)", walk = "Walk(U)", run = "Run(U)" },
	[KEY_S] = {movement = Vector2(0.0, -1.0),  pressed = false, idle = "Idle(D)", walk = "Walk(D)", run = "Run(D)" },
	[KEY_A] = {movement = Vector2(-1.0, 0.0), pressed = false, idle = "Idle(L)", walk = "Walk(L)", run = "Run(L)" },
	[KEY_D] = {movement = Vector2(1.0, 0.0),  pressed = false, idle = "Idle(R)", walk = "Walk(R)", run = "Run(R)" }
}


local function IsMovementButtonDown()
	return Input:IsKeyDown(KEY_W) or Input:IsKeyDown(KEY_S) or Input:IsKeyDown(KEY_A) or Input:IsKeyDown(KEY_D)
end

local PlayerController = Class(function(self, inst)
	self.inst = inst
	self.locomotor = self.inst.components.locomotor

	self.animation = animations[KEY_S]

	inst:StartUpdatingComponent(self)
end)

function PlayerController:Update(delta)
	local movement = Vector2(0, 0)

	for key, data in pairs(animations) do
		if (Input:IsKeyDown(key)) then
			movement = movement + data.movement

			if not data.pressed then
				data.pressed = true

				self.animation = data
			end
		else
			for key, data in pairs(animations) do
				data.pressed = false
			end
		end
	end

	-- Sprinting
	if IsMovementButtonDown() then
		if Input:IsKeyDown(KEY_SHIFT) then
			self.locomotor:RunInDirection(movement:Normalise(), delta)

			self:PlayAnimation(self.animation.run)

			self.inst.SoundEmitter:StopSound("PlayerWalk")
			self.inst.SoundEmitter:PlaySound("PlayerRun", 0.5, false)
		else
			self.locomotor:WalkInDirection(movement:Normalise(), delta)

			self:PlayAnimation(self.animation.walk)

			self.inst.SoundEmitter:StopSound("PlayerRun")
			self.inst.SoundEmitter:PlaySound("PlayerWalk", 0.6, false)
		end
	end

	if not IsMovementButtonDown() then
		if self.animation then
			self:PlayAnimation(self.animation.idle)

			self.inst.SoundEmitter:StopSound("PlayerWalk")
			self.inst.SoundEmitter:StopSound("PlayerRun")
		end
	end
end

function PlayerController:PlayAnimation(name)
	self.currentanim = name
	self.inst.Animator:PlayAnimation(name)
end

return PlayerController