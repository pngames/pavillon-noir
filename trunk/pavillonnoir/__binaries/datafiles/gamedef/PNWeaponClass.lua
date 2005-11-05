function PNWeaponClass(id)	
	------INHERITANCE----------------------------
	local OBJ= inheritFrom(PNItemClass(id))
	OBJ.className="PNWeapon"
	---------------------------------------------
	OBJ.range = 0;
	OBJ.reload = 0;
	OBJ.handling = 1;
	--------------------------------------------- 
	return OBJ
end