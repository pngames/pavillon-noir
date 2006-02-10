function PNSaberWeaponClass(id)	
	------INHERITANCE----------------------------
	local OBJ = inheritFrom(PNWeaponClass(id))
	OBJ.className="PNWeapon"
	---------------------------------------------
	OBJ.range = 2
	OBJ.reload = 0
	OBJ.handling = 1
	OBJ.type = "slasher"
	OBJ.skill = "strength"
	OBJ.modifier = 1
	OBJ.trigger = nil;
	--------------------------------------------------------------------------- 
-------------------------------------------------------------------------------
	OVERRIDE(OBJ, "onInit")
	function OBJ:onInit()
		self.PNWeaponClass_onInit()
		self.trigger = PNGetItemTriggerClass(getUID(), self)
		self.trigger:onInit()
	end
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
	OVERRIDE(OBJ, "onUpdate")
	function OBJ:onUpdate(deltaTime)
		self:PNWeaponClass_onUpdate(deltaTime)
		if (self.isHold == false)then
			self.trigger:onUpdate(deltaTime)
		end
	end
-------------------------------------------------------------------------------
	
	return OBJ
end