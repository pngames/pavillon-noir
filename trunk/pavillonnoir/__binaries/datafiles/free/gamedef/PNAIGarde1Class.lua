function PNAIGarde1Class(id)
	--pnprint("PNAINavy creating\n")
	-- make inheritance -----
	local OBJ = inheritFrom(PNAINavyClass(id))
	OBJ.className = "PNAIGarde1" 
    -------------------------
    OBJ:setId(id)
    OBJ.id = id
    OBJ.go = false
--------------------------------------------------------
	OVERRIDE(OBJ, "onUse")
	function OBJ:onUse(state)
		local p = PNPoint3f:new_local(5650, 25, -425)
		self:moveTo(p)
		self.go = true
	end
--------------------------------------------------------
	OVERRIDE(OBJ, "manageComa")
	function OBJ:manageComa()
		self:PNAINavy_manageComa()
		self:setState(self.stateEnum.PN_IA_PASSIVE)
	end
--------------------------------------------------------
	OVERRIDE(OBJ, "onUpdate")
	function OBJ:onUpdate(deltaTime)
	    --print("==>> PNAICharacter:onUpdate()")
	    --print(self)
		self:PNAINavy_onUpdate(deltaTime)
		if (self.state == self.stateEnum.PN_IA_TRAVELLING) then
			self:onRun(ACTION_STATE.START)
		else
			self:onRun(ACTION_STATE.STOP)
		end
		if (self.state == PN_IA_FIGHTING and (self:getViewTarget() == nil or self:getViewTarget().health_state >= HEALTH_STATE.COMA)) then
			self:setState(PN_IA_PASSIVE)
		end
		if (self.state == self.stateEnum.PN_IA_PASSIVE and self.health_state < HEALTH_STATE.COMA and self.go == true) then
			local p = PNPoint3f:new_local(5650, 25, -425)
			self:moveTo(p)	
		end
	    --print("<<== PNAICharacter:onUpdate()")
	end
--------------------------------------------------------
	return OBJ
end
