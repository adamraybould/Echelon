require("class")

Prefab = Class( function(self, name, fn)
	self.name = string.sub(name, string.find(name, "[^/]*$"))
	self.desc = ""
	self.fn = fn
end)

function Prefab:__tostring()
	return string.format("Prefab %s - %s", self.name, self.desc)
end