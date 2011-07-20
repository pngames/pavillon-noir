function PNItemClass(id)
	------INHERITANCE----------------------------
	local OBJ = inheritFrom(PN3DObjectClass(id))
	OBJ.className = "PNItem"
	---------------------------------------------
	------MODIFIERS LIST-------------------------
	OBJ.modifier = PNModifierClass()
	OBJ.load = 0;
	OBJ.isHold = false 
	---------------------------------------------
	OBJ.trigger = nil;
-------------------------------------------------------------------------------
	OVERRIDE(OBJ, "onInit")
	function OBJ:onInit()
		print("[LUA] PNItem:onInit")
		self.PN3DObject_onInit()
		self.trigger = PNGetItemTriggerClass(getUID(), self)
		self.trigger:onInit()
	end
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
	OVERRIDE(OBJ, "onUpdate")
	function OBJ:onUpdate(deltaTime)
		self:PN3DObject_onUpdate(deltaTime)
		if (self.isHold == false)then
			--pnprint(self:getId() .. " " .. isNotHold)
			self.trigger:prepareUpdate();
			self.trigger:onUpdate(deltaTime)
		end
	end
-------------------------------------------------------------------------------
	return OBJ
end