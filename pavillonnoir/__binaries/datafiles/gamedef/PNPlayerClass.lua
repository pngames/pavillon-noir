function PNPlayerClass(id)
	-- make inheritance -----
	local OBJ = inheritFrom({className = "PNPlayer"}, PNCharacterClass(id))
	-------------------------
	---------------setting camera behavior-----------------
	PNRenderCam:setPositionTarget(OBJ)
	PNRenderCam:setViewTarget(OBJ)
    PNRenderCam:setTargetPosition(0, 30 , 150)
    PNRenderCam:addTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
    PNRenderCam:addTargetMode(PN3DObject.TMODE_ORIENTATION_ABS_LOCKED)
   --PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_ABS_LOCKED)
-----------------------------------------------------------
--[[%
Call at each iterate of main loop.
Do some recurent stuff

@param deltaTime real
	is the delTaTime since the last call of the function
%--]]			
	function OBJ:onUpdate(deltaTime)
		--if (isInstanceOf(self, "PN3DObject"))then
		--	pnprint("IAM PN3Dobject")
		--end
		self.__index:onUpdate(deltaTime)
	end
--------------------------------------------------------
--[[%
Call at the start of a map
%--]]		
	function OBJ:onInit()
        self.__index:onUpdate(deltaTime)
		pnprint(self.id .. ":onInit()\n")
	    --[[
	     self.view = PNRenderCam
	     self.view:setPositionTarget(OBJ)
	     self.view:setViewTarget(OBJ)
         self.view:setTargetPosition(0, 600 , 1000)
         self.view:addTargetMode(PN3DObject.TMODE_VIEW_DISTANCE_LOCKED)
		--]]
	end
----------------------------------------------------------
--[[%
Call when before object destruction
%--]]
	function OBJ:onDestroy()
		nothing = 0
		--self.view:setMovingMode(PN3DObject.MMODE_FREE)
		PNRenderCam:setTarget(tolua.cast(nothing, "PN3DObject"))
		--PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_DISTANCE_ABS_LOCKED)
	end
--------------------------------------------------------
--[[%
Call when player push the primary attack button
%--]]	
	function OBJ:onPrimaryAttack()
		local id = nil
		local entity = nil
		local nearest_d = 99999999999999	-- nearest distance
		local nearest_e = nil 				-- nearest entitie
		-- loop on entities seen by the player
		for id, entity in pairs(self.seen_entities) do
			local distance = self:getPosition():getDistance(entity:getPosition())
			-- select the nearest entity seen by the player
			if (distance < nearest_d) then
				nearest_d = distance
				nearest_e = entity
			end			
		end
		-- if a entity has been selected
		if (nearest_e ~= nil) then
			-- set it as target of player
			self.setTarget(nearest_e)
			-- set player in ATTACK mode
			self.combat_state = COMBAT_STATE.ATTACK
			-- prevent every body that player is attakink target
			sendGameActionEvent("Attack", self:getId(), entity:getTarget(), true)
		end
		--@TODO: launch attack annimation				
	end
---------------------------------------------------------
	
	return OBJ
end