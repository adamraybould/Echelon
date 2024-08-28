
function GetRandomRange(min, max)
	return math.random(min, max)
end

function IsTableEmpty(table)
	local next = next
	return next(table) == nil
end

function RemoveByValue(table, value)
	if table ~= nil then
		for i = #t, 1, -1 do
			if t[i] == value then
				table.remove(t, i)
			end
		end
	end
end

function GetScriptPath()
	local str = debug.getinfo(2, "S").source:sub(2)
	return str:match("(.*/)")
end