
local MAX_PARTICLES = 100

local MIN_LIFETIME = 2
local MAX_LIFETIME = 3

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
	local angle = -45
	local dx = math.cos(angle * PI / 180)
	inst.ParticleSystem:SetVelocity(-0.3, dx)

	local particles_per_second = 15

	inst.ParticleSystem:CreateBoxEmitter(MAX_PARTICLES, 0, -400, 1000, 400)
	inst.ParticleSystem:SetScale(2)

	inst.ParticleSystem:SetParticleTexture(TEXTURE)
	inst.ParticleSystem:SetMaxParticleCount(MAX_PARTICLES)
	inst.ParticleSystem:SetParticleLifetime(MIN_LIFETIME, MAX_LIFETIME)
	inst.ParticleSystem:SetParticleSpeed(MIN_SPEED, MAX_SPEED)

	inst.OnEntityWake = OnEntityWake

	return inst
end

return Prefab("rain", fn, assets)