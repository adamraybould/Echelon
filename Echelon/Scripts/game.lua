
LEVELS =
{
	"testlevel",
}

for i, file in ipairs(LEVELS) do
	RegisterLevel(GetScriptPath().. "Levels/".. file)
end

LevelManager:LoadLevel("testlevel")