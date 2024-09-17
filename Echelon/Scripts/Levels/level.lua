require("class")

Level = Class(function(self, name, init)
	self.name = name
	self.init = init
	self.level = nil
end)

function Level:LoadMap(name)
	print("BOob")
	self.level:LoadMap(name)
end