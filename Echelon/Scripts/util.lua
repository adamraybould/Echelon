
function GetRandomRange(min, max)
	return math.random(min, max)
end

function GetTableSize(table)
	local numItems = 0
	if table ~= nil then
		for k,v in pairs(table) do
			numItems = numItems + 1
		end
	end
	return numItems
end

function GetRandomItem(choices)
	local numChoices = GetTableSize(choices)

	if numChoices < 1 then
		return
	end

	local choice = math.random(numChoices) -1

	local picked = nil
	for k,v in pairs(choices) do
		picked = v
		if choice<= 0 then
			break
		end
		choice = choice -1
	end
	assert(picked~=nil)
	return picked
end

function TableContains(table, value)
	if table ~= nil then
		for k, v in pairs(table) do
			if v == value then
				return true
			end
		end
	end

	return false
end

function IsTableEmpty(table)
	local next = next
	return next(table) == nil
end

function RemoveByValue(table, value)
	if table ~= nil then
		for i = #table, 1, -1 do
			if table[i] == value then
				table.remove(t, i)
			end
		end
	end
end

function GetScriptPath()
	local str = debug.getinfo(2, "S").source:sub(2)
	return str:match("(.*/)")
end