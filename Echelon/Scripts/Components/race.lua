
local Race = Class(function(self, inst)
	self.inst = inst
	self.race = nil
end)

function Race:SetRace(race)
	if TableContains(RACES, race) then
		self.race = race
	end
end

return Race