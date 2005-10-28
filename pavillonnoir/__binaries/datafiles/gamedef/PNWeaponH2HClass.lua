function PNWeaponH2HClass(id)	
	------INHERITANCE----------------------------
	local OBJ= inheritFrom({className="PNWeaponH2H"}, PNWeaponClass(id))
	---------------------------------------------
	OBJ.range = 10;
	OBJ.reload = 0;
	OBJ.handling = 0;
	--------------------------------------------- 
	return OBJ
end