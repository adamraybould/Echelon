
local Inspectable = Class(function(self, inst)
	self.inst = inst
	inst:AddTag("Inspectable")
end)

function Inspectable:GetStatus(viewer)
	if self.inst == viewer then
		return
	end


end

function Inspectable:GetDescription(viewer)
	if self.inst == viewer then
		return
	end


end

return Inspectable