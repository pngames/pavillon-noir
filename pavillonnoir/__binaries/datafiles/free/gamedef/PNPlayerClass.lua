function PNPlayerClass(id)
	-- make inheritance -----
	local OBJ = inheritFrom(PNCharacterClass(id))
	OBJ.className = "PNPlayer" 

	OBJ.walkingSpeed = 0.05
	OBJ.runningSpeed = 0.3

	---------------setting camera behavior-----------------
	

	--PNRenderCam:setViewTarget(OBJ)
--	PNRenderCam:setViewBoneTarget("Bip01 Head")
--	PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
	
--	PNRenderCam:setPositionTarget(OBJ)
--   PNRenderCam:setTargetPosition(0, 75 , 200)
--    PNRenderCam:addTargetMode(PN3DObject.TMODE_POSITION_LOCKED)


    OBJ.stats=	{strength=3,
						 address=3,
						 adaptation=6,
						 awareness=6,
						 resistance=9
						}
	OBJ.skills=	{h2h_combat=5, -- hand to hand
						 firearm=5,
						 slasher=4,
						 throw_weapon=7,
						 dodge=2,
						 escrime=2
						}
						    
    OBJ.realCharacType = CHARACTER_TYPE.NAVY
	OBJ.shownCharacType = CHARACTER_TYPE.NAVY
-----------------------------------------------------------
	function OBJ:onMouseLook(x, y)
		self:rotateYawRadians(math.rad(x/2))	
		--PNRenderCam:subTargetMode(PN3DObject.TMODE_VIEW_ABS_LOCKED)	
		--PNRenderCam:onMouseLook(x, y)
	end    
------------------------------ MOVE -----------------------
	OVERRIDE(OBJ, "onMoveForward")
	function OBJ:onMoveForward(state)
	--pnprint("==>> PNPlayer:onMoveForward()\n")
		if (self.health_state < HEALTH_STATE.COMA) then
			self:PNCharacter_onMoveForward(state)
		end
	--pnprint("<<== PNPlayer:onMoveForward()\n")
	end	
	
	
	OVERRIDE(OBJ, "onMoveBackward")
	function OBJ:onMoveBackward(state)
		if (self.health_state < HEALTH_STATE.COMA) then
			self:PNCharacter_onMoveBackward(state)
		end
	end
	
	OVERRIDE(OBJ, "onMoveLeft")	
	function OBJ:onMoveLeft(state)
		if (self.health_state < HEALTH_STATE.COMA) then
			self:PNCharacter_onMoveLeft(state)
		end
	end	

	OVERRIDE(OBJ, "onMoveRight")
	function OBJ:onMoveRight(state)
		if (self.health_state < HEALTH_STATE.COMA) then
			self:PNCharacter_onMoveRight(state)
		end
	end
------------------------- ROTATE -----------------------------
	OVERRIDE(OBJ, "onRotateRight")
	function OBJ:onRotateRight(state)
		if (self.health_state < HEALTH_STATE.COMA) then
			self:PNCharacter_onRotateRight(state)
		end
	end

	OVERRIDE(OBJ, "onRotateLeft")	
	function OBJ:onRotateLeft(state)
		if (self.health_state < HEALTH_STATE.COMA) then
			self:PNCharacter_onRotateLeft(state)
		end
	end
	
	OVERRIDE(OBJ, "onRotateUp")
	function OBJ:onRotateUp(state)
		if (self.health_state < HEALTH_STATE.COMA) then
			self:PNCharacter_onRotateUp(state)
			PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		end
	end
	
	OVERRIDE(OBJ, "onRotateDown")	
	function OBJ:onRotateDown(state)
		if (self.health_state < PN_IA_COMA) then
			self:PNCharacter_onRotateDown(state)
			PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
		end
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
		if (self.state == self.stateEnum.PN_IA_COMA) then
			self:manageComa()
		end
		if (self.updateLife == true) then
			GUIChangeLife(self.health_state)
			self.updateLife = false
		end
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
        self:PNCharacter_onInit()
		pnprint(self.id .. ":onInit()\n")
   		GUIChangeLife(self.health_state)
   		PNRenderCam:setCoord(self:getCoord())
   		PNRenderCam:setViewTarget(self)
		PNRenderCam:setViewBoneTarget("Bip01 Head")
		PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_ABS_LOCKED)
	
		PNRenderCam:setPositionTarget(self)
    	PNRenderCam:setTargetPosition(0, 75 , 200)
    	PNRenderCam:addTargetMode(PN3DObject.TMODE_POSITION_LOCKED)
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
	function OBJ:onPrimaryAttack(state)
	if (state == ACTION_STATE.START) then
		local id = nil
		local entity = nil
		local nearest_d = 2 * self.selected_weapon.range	-- nearest distance
		local nearest_e = nil 				-- nearest entitie

		--self:startAnimation(CHARACTER_ANIM.STRIKE_TORSO)
		if (self.combat_state == COMBAT_STATE.NEUTRAL and self.health_state < HEALTH_STATE.COMA) then
			--pnprint("tappe !!!\n")
			--if (state == true) then
			--pnprint ("Player wants to fight\n")
			-- loop on entities seen by the player
			for id, entity in pairs(self.seen_entities) do
				if ((isInstanceOf(entity, "PNCharacter")) and (entity.health_state <= HEALTH_STATE.COMA)) then 
					--pnprint("He can attack " .. id .. "\n")
					local distance = self:getCoord():getDistance(entity:getCoord())
					-- select the nearest entity seen by the player
					if (distance < nearest_d) then
						nearest_d = distance
						nearest_e = entity
					end
				end			
			end
			-- if a entity has been selected
			if (nearest_e ~= nil) then
				--pnprint("He will finally attack " .. nearest_e:getId() .. "\n")
				-- set it as target of player
				self:setTarget(nearest_e)
				-- set player in ATTACK mode
				self.combat_state = COMBAT_STATE.ATTACK
				-- prevent every body that player is attaking target
				gameMap:onAttack(self.id, nearest_e:getId())
				--sendGameActionEvent("Attack", self:getId(), entity:getTarget(), true)
			else
				--pnprint("tappe dans le vent\n")
				self:startAnimation(CHARACTER_ANIM.STRIKE_HEAD)
			end
		end
		--@TODO: launch attack annimation
	end
	end
-------------------------------------------------------------------------------
--[[%
Called at the Defense Action
%--]]
	OVERRIDE(OBJ, "onDefense")
	function OBJ:onDefense(state)	
		--print("[LUA] onDefense "..state)
		if (state == ACTION_STATE.START) then
			self.combat_state = COMBAT_STATE.DEFENSE
		else
			self.combat_state = COMBAT_STATE.NEUTRAL
		end
	end
---------------------------------------------------------
	OVERRIDE(OBJ, "startFight")
    function OBJ:startFight(damage, localisation)
    	--nothing
    end
---------------------------------------------------------
--[[%
Called at the end of a Fight Action
%--]]
	OVERRIDE(OBJ, "onDamage")
    function OBJ:onDamage(damage, localisation, source)
    	if (damage > 2) then
    		damage = 2 --Gros hack pour pas que le player meurre trop vite
    	end
    	self:PNCharacter_onDamage(damage, localisation, source)
    	-- call refresh of life bar
    	self.updateLife = true
    	if (self.health_state > HEALTH_STATE.COMA) then
    		gameMap:sendEventFromLua(self, 18) -- GameOverEvent
    	end
	end
--------------------------------------------------------
--[[%
Checks if waited Animation is the one that ended
%--]]
	function OBJ:checkAnimEnd(anim)
		--pnprint("=> PNPlayer:checkAnimEnd(" .. anim .. ") and waited: " .. self.waitedAnim .. "\n")
		if (anim == self.waitedAnim) then
			if (anim == CHARACTER_ANIM.DIE) then
				if ((self.state == self.stateEnum.PN_IA_WAIT_ANIM_END) and (self.waitedAnim == anim)) then
					if (self.health_state >= HEALTH_STATE.LETHAL) then --if is dead
						self:setState(self.stateEnum.PN_IA_DEAD)
						--pnprint("Actually he really is dead\n")
					elseif (self.health_state == HEALTH_STATE.COMA) then
						self:setState(self.stateEnum.PN_IA_COMA)
						--pnprint("Actually it only is a coma\n")
					end
				end
			elseif (self.combat_state == COMBAT_STATE.ATTACK) then -- if is fighting
				--pnprint("restoring Neutral combat state\n")
				self.combat_state = COMBAT_STATE.NEUTRAL
			end
			self.waitedAnim = -1
		end
		--pnprint("<= PNPlayer:checkAnimEnd\n")
	end
---------------------------------------------------------
	OVERRIDE(OBJ, "onFrustrumIn")
	function OBJ:onFrustrumIn(target)
		if (target:getId() ~= self.id) then
			--pnprint ("Player sees " .. target:getId() .. "\n")
			self.seen_entities[target:getId()] = target
		end
	end
---------------------------------------------------------
	OVERRIDE(OBJ, "onFrustrumOut")
	function OBJ:onFrustrumOut(target)
		if (target:getId() ~= self.id) then
			--pnprint ("Player doesn't see " .. target:getId() .. " anymore\n")
			self.seen_entities[target:getId()] = nil
		end
	end
---------------------------------------------------------
	OVERRIDE(OBJ, "getItem")
	function OBJ:getItem(item)
		self:PNCharacter_getItem(item)
		sendGameActionEvent("Item_inv", self:getId(), item:getId(), 1)
	end
	
-----------------------------------------------------------
--[[%
Called at the Use Action
%--]]
	function OBJ:onUse(state)	
		if (state == 1)then
			for  id_1,  entity in pairs(gameMap.entities.all) do
				if (entity:isA("PNCharacter")  and entity:getId() ~= self:getId() and self:getCoord():getDistance(entity:getCoord()) < 100.0)then
					  sendGameActionEvent("Chat", self:getId(), entity:getId(), 1)
				end
			end
		end
	end
		
	return OBJ

end
