function PNWeaponClass(id)	
	------INHERITANCE----------------------------
	local PNWeapon= inheriteFrom({className="PNWeapon"}, PNItemClass(id))
	---------------------------------------------
	PNWeapon.range = 0;
	PNWeapon.load = 0;
	PNWeapon.handling = 1;
	--------------------------------------------- 
	return PNWeapon
end