function PNPlayerClass(id)
	-- make inheritance -----
	local OBJ = inheritFrom({className = "PNPlayer"}, PNCharacterClass(id))
	-------------------------
	---------------setting camera behavior-----------------
	
--	local RCVT = PN3DObjectClass("RCVT")
--	RCVT:setPositionTarget(PNRenderCam)
--	RCVT:setViewTarget(OBJ)
--	RCVT:setMovingSpeed(0.2);
--	RCVT:addTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	
--	PNRenderCam:setViewTarget(RCVT)
	PNRenderCam:setViewTarget(OBJ)
	PNRenderCam:setPositionTarget(OBJ)
    PNRenderCam:setTargetPosition(0, 50 , 150)
    PNRenderCam:setTargetDistance(150)
    PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
    PNRenderCam:addTargetMode(PN3DObject.TMODE_DISTANCE_LOCKED)
    PNRenderCam:addTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
    --PNRenderCam:addTargetMode(PN3DObject.TMODE_ORIENTATION_ABS_LOCKED)
    
    
-----------------------------------------------------------
	function OBJ:onMouseLook(y, x)
		PNRenderCam:subTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
	--	PNRenderCam:getViewTarget():subMovingState(PN3DObject.STATE_T_FORWARD)
		
	end    
------------------------------ MOVE -----------------------
	function OBJ:onMoveForward(state)
		self.__index:onMoveForward(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
		--if (state == ACTION_STATE.START) then
		--	PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--	PNRenderCam:getViewTarget():addMovingState(PN3DObject.STATE_T_FORWARD)
		--end
	end	

	function OBJ:onMoveBackward(state)
		self.__index:onMoveBackward(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
		--if (state == ACTION_STATE.START) then
		--	PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--	PNRenderCam:getViewTarget():addMovingState(PN3DObject.STATE_T_FORWARD)
		--end	
	end
	
	function OBJ:onMoveLeft(state)
		self.__index:onMoveLeft(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
		--if (state == ACTION_STATE.START) then
		--	PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--	PNRenderCam:getViewTarget():addMovingState(PN3DObject.STATE_T_FORWARD)
		--end	
	end	

	function OBJ:onMoveRight(state)
		self.__index:onMoveRight(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
		--if (state == ACTION_STATE.START) then
		--	PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--	PNRenderCam:getViewTarget():addMovingState(PN3DObject.STATE_T_FORWARD)
		--end
	end
------------------------- ROTATE -----------------------------
	function OBJ:onRotateRight(state)
		self.__index:onRotateRight(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	end
	
	function OBJ:onRotateLeft(state)
		self.__index:onRotateLeft(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	end
	
	function OBJ:onRotateUp(state)
		self.__index:onRotateUp(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	end
	
	function OBJ:onRotateDown(state)
		self.__index:onRotateDown(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	end    
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
		--local RCVT= PNRenderCam:getViewTarget()
		--if (self:getCoord():getDistance(RCVT:getCoord()) <= 5)then
		--	RCVT:subMovingState(PN3DObject.STATE_T_FORWARD)
		--else
		--	RCVT:addMovingState(PN3DObject.STATE_T_FORWARD)
		--RCVT:update(deltaTime)
		--end
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
