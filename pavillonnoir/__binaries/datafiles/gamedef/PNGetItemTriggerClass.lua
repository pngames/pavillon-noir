function PNGetItemTriggerClass(id, item)
	local OBJ = inheriteFrom(PNActionTriggerClass(id))
	
	OBJ.item = item
	OBJ.range = 5.0
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
		self.PNActionTriggerClass_onInit()
		
	end
	
	---------------------------------------------------
	------------------onUpdate---------------------------
	OVERRIDE(OBJ, "onUpdate")
	function OBJ:onUpdate()
		self.PNActionTriggerClass_onUpdate()
		
	end
	
	---------------------------------------------------
	-------------------Action-------------------------
	OVERRIDE(OBJ, "executeAction")
	function OBJ:executeAction(entity, entity_state)
		if (entity:getId() == "player" and entity_state == TRIGGER_STATE.STILL_IN)then
			entity:getItem(self.item)
		end
	end
	---------------------------------------------------
	return OBJ
end