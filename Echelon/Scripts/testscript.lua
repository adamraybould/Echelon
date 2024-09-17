
Player = SpawnPrefab("player")
Player.Transform:SetPosition(Vector2(1024, 1024))

local focalpoint = SpawnPrefab("focalpoint")

Camera:SnapToPosition(Player:GetPosition())
Camera:SetTarget(Player)

local lantern = SpawnPrefab("lantern_lit")
lantern.Transform:SetPosition(Vector2(1000, 1000))

--local rain = SpawnPrefab("rain")
--rain.Transform:SetParent(Player.Transform)

