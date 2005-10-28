function PNItemClass(id)
	------INHERITANCE----------------------------
	local OBJ = inheritFrom({className = "PNItem"}, PN3DObjectClass(id))
	---------------------------------------------
	------MODIFIERS LIST-------------------------
	OBJ.modifier = PNModifierClass()
	OBJ.load = 0;
	---------------------------------------------
	return OBJ
end