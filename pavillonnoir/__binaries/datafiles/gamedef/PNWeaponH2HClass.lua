function PNWeaponH2HClass(id)	
	------INHERITANCE----------------------------
	local OBJ= inheritFrom(PNWeaponClass(id))
	OBJ.className="PNWeaponH2H"
	---------------------------------------------
	OBJ.range = 10;
	OBJ.reload = 0;
	OBJ.handling = 0;
	--------------------------------------------- 
	return OBJ
end