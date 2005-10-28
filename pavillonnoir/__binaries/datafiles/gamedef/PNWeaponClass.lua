function PNWeaponClass(id)	
	------INHERITANCE----------------------------
	local OBJ= inheriteFrom({className="PNWeapon"}, PNItemClass(id))
	---------------------------------------------
	OBJ.range = 0;
	OBJ.load = 0;
	OBJ.handling = 1;
	--------------------------------------------- 
	return OBJ
end