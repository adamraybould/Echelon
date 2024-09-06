require("class")

Prefab = Class( function(self, name, fn, assets)
	self.name = string.sub(name, string.find(name, "[^/]*$"))
	self.desc = ""
	self.fn = fn
	self.assets = assets or {}
end)

function Prefab:__tostring()
	return string.format("Prefab %s - %s", self.name, self.desc)
end

Asset = Class(function(self, type, file, param)
	self.type = type
	self.file = file
	self.param = param
end)