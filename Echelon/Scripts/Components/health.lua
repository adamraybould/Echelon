
local Health = Class(function(self, inst)
	self.inst = inst

	self.maxHealth = 100
	self.currenthealth = self.maxHealth
	self.invincible = false
	self.canheal = true
end)

function Health:SetCurrentHealth(value)
	self.currenthealth = value
end

function Health:SetMaxHealth(value)
	self.maxHealth = value
	self.currenthealth = value
end

function Health:Damage(damage)
	if not self:IsDead() and not self.IsInvincible() then
		if self.currenthealth - damage < 0 then
			self.currenthealth = 0
		else
			self.currenthealth = self.currenthealth - damage
		end
	end
end

function Health:Kill()
	if not self:IsDead() then
		self:Damage(self.currenthealth)
	end
end

---Returns if Entity is Dead
---@return boolean
function Health:IsDead()
	return self.currenthealth <= 0
end


---Returns if Entity is Invincible
---@return boolean
function Health:IsInvincible()
	return self.invincible
end

return Health