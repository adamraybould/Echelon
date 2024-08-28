
function Update(delta)
	-- Update Entity Components
	for k, v in pairs(UpdatingEntities) do
		if v.updatecomponents ~= nil then
			for component in pairs(v.updatecomponents) do
				if component.Update and not StopUpdatingComponents[component] then
					component:Update(delta)
				end
			end
		end
	end

	-- Add New Updating Entities to a new array
	if next(NewUpdatingEntities) ~= nil then
		for k, v in pairs(NewUpdatingEntities) do
			UpdatingEntities[k] = v
		end

		NewUpdatingEntities = {}
	end

	if next(StopUpdatingComponents) ~= nil then
		for k, v in pairs(StopUpdatingComponents) do
			v:StopUpdatingComponent_Deferred(k)
		end

		StopUpdatingComponents = {}
	end
end