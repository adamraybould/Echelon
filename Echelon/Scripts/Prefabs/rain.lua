
local MAX_PARTICLES = 200

local MIN_LIFETIME = 3
local MAX_LIFETIME = 6

local MIN_SPEED = 800
local MAX_SPEED = 1000

local TEXTURE = "FX/raindrop.png"

local assets =
{
	Asset("TEXTURE", TEXTURE),
	Asset("AUDIO", "Audio/SFX.bank")
}

local function OnEntityWake(inst)
	inst.SoundEmitter:PlaySound("Rain", 0.4, true)
end

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddParticleSystem()
	inst.entity:AddSoundEmitter()

	inst:AddTag("FX")

	-----------------------------------------------------
	local angle = 145
	local dx = math.cos(angle * PI / 180)
	inst.ParticleSystem:SetVelocity(-0.3, dx)

	inst.ParticleSystem:CreateBoxEmitter(MAX_PARTICLES, 0, 500, 2000, 500)
	inst.ParticleSystem:SetScale(1)

	inst.ParticleSystem:SetParticleTexture(TEXTURE)
	inst.ParticleSystem:SetMaxParticleCount(MAX_PARTICLES)
	inst.ParticleSystem:SetParticleLifetime(MIN_LIFETIME, MAX_LIFETIME)
	inst.ParticleSystem:SetParticleSpeed(MIN_SPEED, MAX_SPEED)

	inst.OnEntityWake = OnEntityWake

	return inst
end

return Prefab("rain", fn, assets)