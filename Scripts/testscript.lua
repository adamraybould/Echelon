
Player = SpawnPrefab("player")

local focalpoint = SpawnPrefab("focalpoint")
Camera:SetTarget(Player)

local gunbot = SpawnPrefab("gunbot")
local drillbot = SpawnPrefab("drillbot")

SpawnMultiplePrefabs("blank", 5)
