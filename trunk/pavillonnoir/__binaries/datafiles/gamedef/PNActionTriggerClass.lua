TRIGGER_STATE = {STILL_OUT=0, STILL_IN=1, GO_IN=2, GO_OUT=3}

function PNActionTriggerClass(id)
	local OBJ = inheritFrom(PN3DObjectClass(id))
	OBJ.className="PNActionTrigger"
	OBJ.actionRange = 0
	OBJ.last_entities_state = {}
	 
	function OBJ:executeAction(entity, entity_state)
		
	end 
	
	function OBJ:onInit()
		--self.actionRange = self:getCenter():getDistance(self:getMax())
		self:customInit()	
	end
	
	function OBJ:customInit()
	end
	
	OVERRIDE(OBJ, "onUpdate")
	function OBJ:onUpdate(deltaTime)
		self:PN3DObject_onUpdate(deltaTime)	
		for  id_1,  entity in pairs(gameMap.entities.className.PNPlayer) do 
     		--pnprint(id_1)
      		--pnprint("\n")
      		if (self.last_entities_state[id_1] == nil) then 
      			self.last_entities_state[id_1] = TRIGGER_STATE.STILL_OUT
      		end 
      		local distance_trigger = self:getCoord():getDistance(entity:getCoord())
      		if (distance_trigger <= self.actionRange) then 
      			if   (self.last_entities_state[id_1] == TRIGGER_STATE.STILL_OUT)then
      				self.last_entities_state[id_1] = TRIGGER_STATE.GO_IN
      			elseif (self.last_entities_state[id_1] == TRIGGER_STATE.GO_IN) then
      				self.last_entities_state[id_1] = TRIGGER_STATE.STILL_IN
      			end
      		else      			
      			if   (self.last_entities_state[id_1] == TRIGGER_STATE.STILL_IN)then
      				self.last_entities_state[id_1] = TRIGGER_STATE.GO_OUT
      			elseif (self.last_entities_state[id_1] == TRIGGER_STATE.GO_OUT) then
      				self.last_entities_state[id_1] = TRIGGER_STATE.STILL_OUT
      			end
      		end
      		local entity_state = self.last_entities_state[id_1]
      		--print("[lua] entity coord: ".. entity:getCoord().x .." ".. entity:getCoord().z .." ")
      		--print("[lua] distance: ".. distance_trigger)
      		--print("[lua] action rage ".. self.actionRange)
      		--print("[lua] state"..entity_state)
      	
      		self:executeAction(entity, entity_state)
      		--pnprint("\n")
      	
		end
	end
	
	return OBJ
end