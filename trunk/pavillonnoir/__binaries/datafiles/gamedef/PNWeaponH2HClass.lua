function PNWeaponH2HClass(id)	
	------INHERITANCE----------------------------
	local OBJ= inheritFrom(PNWeaponClass(id))
	OBJ.className="PNWeaponH2H"
	---------------------------------------------
	OBJ.range = 50
	OBJ.reload = 0
	OBJ.handling = 0
	OBJ.type = "h2h_combat"
	OBJ.skill = "strength"
	OBJ.modifier = -1
	--------------------------------------------- 
	return OBJ
end