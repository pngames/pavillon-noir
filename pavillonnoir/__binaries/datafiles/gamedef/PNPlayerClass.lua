function PNPlayerClass(id)
	-- make inheritance -----
	local OBJ = inheritFrom(PNCharacterClass(id))
	OBJ.className = "PNPlayer" 
	---------------setting camera behavior-----------------
	
--	local RCVT = PN3DObjectClass("RCVT")
--	RCVT:setPositionTarget(PNRenderCam)
--	RCVT:setViewTarget(OBJ)
--	RCVT:setMovingSpeed(0.2);
--	RCVT:addTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	
--	PNRenderCam:setViewTarget(RCVT)
	PNRenderCam:setViewTarget(OBJ)
	PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
	
	PNRenderCam:setPositionTarget(OBJ)
    PNRenderCam:setTargetPosition(0, 75 , 200)
    PNRenderCam:addTargetMode(PN3DObject.TMODE_POSITION_LOCKED)
    
    --PNRenderCam:setTargetDistance(150)
    --PNRenderCam:setTargetOrientation(PNQuatf:new_local(0.0, 0.0, 0.1, 1));

    --PNRenderCam:addTargetMode(PN3DObject.TMODE_DISTANCE_ABS_LOCKED)
    --PNRenderCam:addTargetMode(PN3DObject.TMODE_ORIENTATION_LOCKED)
    --PNRenderCam:addTargetMode(PN3DObject.TMODE_ORIENTATION_ABS_LOCKED)
    
    
-----------------------------------------------------------
	function OBJ:onMouseLook(y, x)
	--	PNRenderCam:subTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
	--	PNRenderCam:getViewTarget():subMovingState(PN3DObject.STATE_T_FORWARD)
		
	end    
------------------------------ MOVE -----------------------
	OVERRIDE(OBJ, "onMoveForward")
	function OBJ:onMoveForward(state)
	pnprint("==>> PNPlayer:onMoveForward()\n")
		self:PNCharacter_onMoveForward(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)		
	pnprint("<<== PNPlayer:onMoveForward()\n")
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
		--if (state == ACTION_STATE.START) then
		--	PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--	PNRenderCam:getViewTarget():addMovingState(PN3DObject.STATE_T_FORWARD)
		--end
	end	
	
	OVERRIDE(OBJ, "onMoveBackward")
	function OBJ:onMoveBackward(state)
		self:PNCharacter_onMoveBackward(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
		--if (state == ACTION_STATE.START) then
		--	PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--	PNRenderCam:getViewTarget():addMovingState(PN3DObject.STATE_T_FORWARD)
		--end	
	end
	
	OVERRIDE(OBJ, "onMoveLeft")	
	function OBJ:onMoveLeft(state)
		self:PNCharacter_onMoveLeft(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
		--if (state == ACTION_STATE.START) then
		--	PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--	PNRenderCam:getViewTarget():addMovingState(PN3DObject.STATE_T_FORWARD)
		--end	
	end	

	OVERRIDE(OBJ, "onMoveRight")
	function OBJ:onMoveRight(state)
		self:PNCharacter_onMoveRight(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
		--if (state == ACTION_STATE.START) then
		--	PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--	PNRenderCam:getViewTarget():addMovingState(PN3DObject.STATE_T_FORWARD)
		--end
	end
------------------------- ROTATE -----------------------------
	OVERRIDE(OBJ, "onRotateRight")
	function OBJ:onRotateRight(state)
		self:PNCharacter_onRotateRight(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	end

	OVERRIDE(OBJ, "onRotateLeft")	
	function OBJ:onRotateLeft(state)
		self:PNCharacter_onRotateLeft(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	end
	
	OVERRIDE(OBJ, "onRotateUp")
	function OBJ:onRotateUp(state)
		self:PNCharacter_onRotateUp(state)
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	end
	
	OVERRIDE(OBJ, "onRotateDown")	
	function OBJ:onRotateDown(state)
		self:PNCharacter_onRotateDown(state)
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
	OVERRIDE(OBJ, "onUpdate")			
	function OBJ:onUpdate(deltaTime)
		--if (isInstanceOf(self, "PN3DObject"))then
		--	pnprint("IAM PN3Dobject")
		--end
		self:PNCharacter_onUpdate(deltaTime)
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
	OVERRIDE(OBJ, "onInit")		
	function OBJ:onInit()
        self:PNCharacter_onUpdate(deltaTime)
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
--[[%
Called at the end of a Fight Action
%--]]
	OVERRIDE(OBJ, "onDamage")
    function OBJ:onDamage(damage, localisation)
    	self:PNCharacter_onDamage(damage, localisation)
    	-- call refresh of life bar
	end
---------------------------------------------------------
	
	return OBJ
end
