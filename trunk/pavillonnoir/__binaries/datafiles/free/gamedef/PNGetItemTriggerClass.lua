function PNGetItemTriggerClass(id, item)
	local OBJ = inheritFrom(PNActionTriggerClass(id))
	
	OBJ.className="PNGetItemTrigger"
	OBJ.item = item
	OBJ.actionRange = 50
	OBJ:setPositionTarget(item)
	OBJ:addTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	
	------------------Custom Init---------------------------
	OVERRIDE(OBJ, "CustomInit")
	function OBJ:customInit()
	
	end
	
	---------------------------------------------------
	------------------onInit---------------------------
	OVERRIDE(OBJ, "onInit")
	function OBJ:onInit()
		self:PNActionTrigger_onInit()
		
	end
	
	---------------------------------------------------
	------------------onUpdate---------------------------
	OVERRIDE(OBJ, "onUpdate")
	function OBJ:onUpdate(deltaTime)
		if (self.item ~= nil and self.item.isHold ~= nil and  self.item.isHold == false)then
			self:PNActionTrigger_onUpdate(deltaTime)
		end
	end
	
	---------------------------------------------------
	-------------------Action-------------------------
	OVERRIDE(OBJ, "executeAction")
	function OBJ:executeAction(entity, entity_state)
		if (entity:isA("PNCharacter") and entity_state == TRIGGER_STATE.STILL_IN)then
			--print("[LUA] get the item")
			entity:getItem(self.item)
		end
	end
	---------------------------------------------------
	return OBJ
end