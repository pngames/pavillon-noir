function PNSaberWeaponClass(id)	
	------INHERITANCE----------------------------
	local OBJ = inheritFrom(PNWeaponClass(id))
	OBJ.className="PNSaberWeapon"
	---------------------------------------------
	OBJ.range = 70
	OBJ.reload = 0
	OBJ.handling = 1
	OBJ.type = "slasher"
	OBJ.skill = "strength"
	OBJ.modifier = 1

	
	return OBJ
end