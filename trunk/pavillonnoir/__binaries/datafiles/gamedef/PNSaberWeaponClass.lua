function PNSaberWeaponClass(id)	
	------INHERITANCE----------------------------
	local OBJ = inheritFrom(PNWeaponClass(id))
	OBJ.className="PNSaberWeapon"
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
		print("[LUA] PNSaberWeapo:onInit")
		self.PNWeapon_onInit()
		self.trigger = PNGetItemTriggerClass(getUID(), self)
		self.trigger:onInit()
	end
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
	OVERRIDE(OBJ, "onUpdate")
	function OBJ:onUpdate(deltaTime)
		self:PNWeapon_onUpdate(deltaTime)
		if (self.isHold == false)then
			self.trigger:onUpdate(deltaTime)
		end
	end
-------------------------------------------------------------------------------
	
	return OBJ
end