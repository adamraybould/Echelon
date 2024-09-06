
Player = SpawnPrefab("player")

local focalpoint = SpawnPrefab("focalpoint")

Camera:SnapToPosition(Player:GetPosition())
Camera:SetTarget(Player)

--SpawnMultiplePrefabs("blank", 5)

--local gunbot = SpawnPrefab("gunbot")
--local drillbot = SpawnPrefab("drillbot")

--gunbot.Rigidbody:SetPosition(Vector2(GetRandomRange(-500, 500), GetRandomRange(-500, 500)))
--drillbot.Rigidbody:SetPosition(Vector2(GetRandomRange(-500, 500), GetRandomRange(-500, 500)))

