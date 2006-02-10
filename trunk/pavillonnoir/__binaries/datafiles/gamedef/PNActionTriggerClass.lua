TRIGGER_STATE = {STILL_OUT=0, STILL_IN=1, GO_IN=2, GO_OUT=3}

function PNActionTriggerClass(id)
	local OBJ = inheritFrom(PN3DObjectClass(id))
	
	OBJ.actionRange = 0
	OBJ.last_entities_state = {}
	 
	function OBJ:executeAction(entity, entity_state)
		
	end 
	
	function OBJ:onInit()
		OBJ.actionRange = self:getCenter():getDistance(self:getMax())
		OBJ:custumInit()	
	end
	
	function OBJ:customInit()
	end
	
	function OBJ:onUpdate(deltaTime)	
		for  id_1,  entity in pairs(gameMap.entities.all) do 
     		pnprint(id_1)
      		pnprint("\n")
      		if (OBJ.last_entities_state[id_1] == nil) then 
      			OBJ.last_entities_state[id_1] = TRIGGER_STATE.STILL_OUT
      		end 
      		local distance_trigger = self:getCenter():getDistance(entity:getCenter())
      		if (distance_trigger <= OBJ.actionRange) then 
      			if   (OBJ.last_entities_state[id_1] == TRIGGER_STATE.STILL_OUT)then
      				OBJ.last_entities_state[id_1] = TRIGGER_STATE.GO_IN
      			elseif (OBJ.last_entities_state[id_1] == TRIGGER_STATE.GO_IN) then
      				OBJ.last_entities_state[id_1] = TRIGGER_STATE.GO_IN
      			end
      		else      			
      			if   (OBJ.last_entities_state[id_1] == TRIGGER_STATE.STILL_IN)then
      				OBJ.last_entities_state[id_1] = TRIGGER_STATE.GO_OUT
      			elseif (OBJ.last_entities_state[id_1] == TRIGGER_STATE.GO_OUT) then
      				OBJ.last_entities_state[id_1] = TRIGGER_STATE.STILL_OUT
      			end
      		end
      		local entity_state = OBJ.last_entities_state[id_1]
      		
      		OBJ:executeAction(entity, entity_state)
      		pnprint("\n")
      	
		end
	end
	
	return OBJ
end