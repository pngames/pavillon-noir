function PNGetItemTriggerClass(id, item)
	local OBJ = inheritFrom(PNActionTriggerClass(id))
	
	OBJ.className="PNGetItemTrigger"
	OBJ.item = item
	OBJ.actionRange = 80
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
		self:PNActionTrigger_onUpdate(deltaTime)
		
	end
	
	---------------------------------------------------
	-------------------Action-------------------------
	OVERRIDE(OBJ, "executeAction")
	function OBJ:executeAction(entity, entity_state)
		if (entity:getId() == "player" and entity_state == TRIGGER_STATE.STILL_IN)then
			print("[LUA] get the item")
			entity:getItem(self.item)
		end
	end
	---------------------------------------------------
	return OBJ
end