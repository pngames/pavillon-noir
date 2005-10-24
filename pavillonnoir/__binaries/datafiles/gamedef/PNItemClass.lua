function PNItemClass(id)
	------INHERITANCE----------------------------
	local PNItem = inheritFrom({className = "PNItems"}, PN3DObjectClass(id))
	---------------------------------------------
	------MODIFIERS LIST-------------------------
	PNItem.modifier = PNModifierClass()
	PNItem.load = 0;
	---------------------------------------------
	return PNItem
end