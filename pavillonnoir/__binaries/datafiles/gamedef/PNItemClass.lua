function PNItemClass(id)
	------INHERITANCE----------------------------
	local OBJ = inheritFrom(PN3DObjectClass(id))
	OBJ.className = "PNItem"
	---------------------------------------------
	------MODIFIERS LIST-------------------------
	OBJ.modifier = PNModifierClass()
	OBJ.load = 0;
	OBJ.isHold = false 
	---------------------------------------------
	return OBJ
end