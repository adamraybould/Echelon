
function Class(base, _ctor)
	local c = {} -- Class Instance

	if not _ctor and type(base) == 'function' then
		_ctor = base
		base = nil
	elseif type(base) == 'table' then
		for i,v in pairs(base) do
			c[i] = v
		end

		c._base = base
	end

	c.__index = c

	-- expose a constructor which can be called by <classname>(<args>)
	local mt = {}

	mt.__call = function(class_tbl, ...)
		local obj = {}
		-- Initialize properties here...
		setmetatable(obj, c)
		if c._ctor then
			c._ctor(obj, ...)
		end
		return obj
	end

	c.init = init
	c.is_a = function(self, klass)
		local m = getmetatable(self)
		while m do
			if m == klass then return true end
			m = m._base
		end
		return false
	end

	setmetatable(c, mt)
	return c
end

local function _is_a(self, klass)
	local m = getmetatable(self)
	while m do
		if m == klass then
			return true
		end
		m = m._base
	end

	return false
end