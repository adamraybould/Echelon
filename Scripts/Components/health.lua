
local Health = Class("Health", function(self, inst)
	self.inst = inst

	self.maxHealth = 100
	self.health = self.maxHealth
	self.invincible = false

	PrintMessage("Test Message - Boobs")
end)

function Health:SetCurrentHealth(value)
	self.health = value
end

function Health:SetMaxHealth(value)
	self.maxHealth = value
	self.health = value
end

function Health:IsDead()
	return self.health <= 0
end

_G["Health"] = Health
return Health