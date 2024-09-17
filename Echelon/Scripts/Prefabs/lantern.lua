
local lantern_unlit_assets =
{
	Asset("SPRITE", "Objects/Lantern", 0)
}

local lantern_lit_assets =
{
	Asset("SPRITE", "Objects/Lantern", 1)
}

local lantern_lit_special_assets =
{
	Asset("SPRITE", "Objects/Lantern", 2)
}

local function fn()
	local inst = CreateEntity()

	inst.entity:AddTransform()
	inst.entity:AddRenderer()
	inst.entity:AddRigidbody()
	inst.entity:AddLightSource()

	inst.Rigidbody:CreateStaticBody()

	inst.Light:SetIntensity(0.75);
	inst.Light:SetColor(255, 255, 255)
	inst.Light:SetRadius(2)

	inst:AddTag("Lantern")
	inst:AddTag("Item")

	return inst
end

return Prefab("lantern_unlit", fn, lantern_unlit_assets),
	Prefab("lantern_lit", fn, lantern_lit_assets)