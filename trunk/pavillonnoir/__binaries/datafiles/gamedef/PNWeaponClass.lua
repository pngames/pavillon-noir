function PNWeaponClass(id)	
	------INHERITANCE----------------------------
	local OBJ= inheritFrom({className="PNWeapon"}, PNItemClass(id))
	---------------------------------------------
	OBJ.range = 0;
	OBJ.reload = 0;
	OBJ.handling = 1;
	--------------------------------------------- 
	return OBJ
end