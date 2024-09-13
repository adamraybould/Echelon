
Player = SpawnPrefab("player")
Player.Transform:SetPosition(Vector2(500, 500))

local focalpoint = SpawnPrefab("focalpoint")

Camera:SnapToPosition(Player:GetPosition())
Camera:SetTarget(Player)

local rain = SpawnPrefab("rain")
rain.Transform:SetParent(Player.Transform)

--SpawnMultiplePrefabs("blank", 5)

--local gunbot = SpawnPrefab("gunbot")
--local drillbot = SpawnPrefab("drillbot")

--gunbot.Rigidbody:SetPosition(Vector2(GetRandomRange(-500, 500), GetRandomRange(-500, 500)))
--drillbot.Rigidbody:SetPosition(Vector2(GetRandomRange(-500, 500), GetRandomRange(-500, 500)))

