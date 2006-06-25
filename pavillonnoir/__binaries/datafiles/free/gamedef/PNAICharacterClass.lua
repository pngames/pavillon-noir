function PNAICharacterClass(id)
	--pnprint("PNAICharacterClass creating\n")
	-- make inheritance -----
	local OBJ = inheritFrom(PNCharacterClass(id))
	OBJ.className = "PNAICharacter" 
    if (gameMap.entities.className[OBJ.className] == nil) then
		gameMap.entities.className[OBJ.className] = {}
	end
	gameMap.entities.className[OBJ.className][id] = OBJ
    -------------------------
    OBJ:setId(id)
    OBJ.id = id
    --pnprint("PNCharacterClass creating 2\n")

	--OBJ:setMovingSpeed(0.5)
	OBJ.hurry = false
	OBJ.realCharacType = CHARACTER_TYPE.CIVILIAN
	OBJ.shownCharacType = CHARACTER_TYPE.CIVILIAN
--	--pnprint("create pathFinding\n")
	OBJ.pathFinding = PNPathFinding:new_local(OBJ:getCoord())
--	--pnprint("pathFinding created\n")
--	--pnprint("create pathFinding\n")
	OBJ.pathFinding:unserializeFromPath(gameMap:getWpFile())
--	--pnprint("pathFinding created\n")
	OBJ.toReach = PN3DObject:new_local()
	OBJ.elapsedTurns = 0
	OBJ.ennemies = {}
	OBJ:setTarget(nil)
--	--pnprint("PNCharacterClass creating 3\n")
--------------------------------------------------------
--[[%
Called at the update
Calls a Behaviour Function depending on the state in which the character is
%--]]
	function OBJ:beSmart()
		--print("==>> PNAICharacter:beSmart()")
	    --print(self)
		if (self.state == self.stateEnum.PN_IA_TRAVELLING) then
			self:manageTravel()
		elseif (self.state == self.stateEnum.PN_IA_FIGHTING) then
			self:manageFight()
		elseif (self.state == self.stateEnum.PN_IA_COMA) then
			self:manageComa()
		end
	    --print("<<== PNAICharacter:beSmart()")
	end
--------------------------------------------------------
--[[%
Behaviour Function
Called during PathFinding to resolve the travel
%--]]
	function OBJ:manageTravel()
--		pnprint("toReach        : " .. self.toReach:getCoord().x .. " " .. self.toReach:getCoord().y .. " " .. self.toReach:getCoord().z .. "\n")
--		pnprint("Target position: " .. self:getViewTarget():getCoord().x .. " " .. self:getViewTarget():getCoord().y .. " " .. self:getViewTarget():getCoord().z .. "\n")
--		pnprint("player position: " .. self:getCoord().x .. " " .. self:getCoord().y .. " " .. self:getCoord().z .. "\n")
--		pnprint("cam position   : " .. self.view:getCoord().x .. " " .. self.view:getCoord().y .. " " .. self.view:getCoord().z .. "\n")
--		pnprint("player orient  : " .. self:getOrient().x .. " " .. self:getOrient().y .. " " .. self:getOrient().z .. " " .. self:getOrient().w .. "\n")
--		pnprint("cam orient     : " .. self.view:getOrient().x .. " " .. self.view:getOrient().y .. " " .. self.view:getOrient().z .. " " .. self.view:getOrient().w .. "\n")
		local distance = self:getCoord():getDistance(self.toReach:getCoord())
		if (distance <= 30.0) then
			self.pathFinding:moveNext(self.toReach)
			local distance2 = self:getCoord():getDistance(self.toReach:getCoord())
			if (distance2 <= 30.0) then
				self:setTarget(nil)
				self:restoreState()
				self:onMoveForward(ACTION_STATE.STOP)
				return
			end
			self:setTarget(self.toReach)
			self:setTargetMode(self.TMODE_VIEW_ABS_LOCKED)
		end
		for id, val in pairs(self.ennemies) do
			if (val == 1) then
				local ennemy = gameMap.entities.all[id]
				--pnprint(self.id .. " viewing an ennemy (" .. ennemy:getId() .. ") while travelling, can he attack him ?\n")
				--if (self:getCoord():getDistance(ennemy:getCoord()) < self:getCoord():getDistance(self.toReach:getCoord())) then
				if (self:getCoord():getDistance(ennemy:getCoord()) < 5 * self.selected_weapon.range) then
					self:startFight(ennemy)
				end
			end
		end
	end
--------------------------------------------------------
--[[%
Called while handling a fight
%--]]
	function OBJ:manageFight()
		print("==>> PNAICharacter:manageFight()")
	    print(self)
	    print("<<== PNAICharacter:manageFight()")
	end
--------------------------------------------------------
--[[%
Called on a MoveTo event
Prepares the character to handle the PathFinding
%--]]
	function OBJ:moveTo(p)
		OBJ.goal = PNPoint3f:new_local(p)
		--pnprint("moveto: " .. p.x .. " " .. p.y .. " " .. p.z .. "\n")
		self:setState(self.stateEnum.PN_IA_TRAVELLING)
		self.pathFinding:moveTo(p)
		self.pathFinding:moveNext(self.toReach)
		local fdistance = self:getCoord():getFlatDistance(self.toReach:getCoord())
		if (fdistance <= 25.0) then
			self.pathFinding:moveNext(self.toReach)
		end
		-- setDirect and rotate
		self:setTarget(self.toReach)
		self:setTargetMode(self.TMODE_VIEW_ABS_LOCKED)
		self:onMoveForward(ACTION_STATE.START)
	end
--------------------------------------------------------
--[[%
Called when an ennemy enters the frustrum
Prepares the Character to handle a fight
%--]]
	OVERRIDE(OBJ, "startFight")
	function OBJ:startFight(target)
--[[		self:setTarget(target)
		self:setTargetMode(self.TMODE_VIEW_ABS_LOCKED)
	    print("==>> PNAICharacter:startFight()")
	    print(self)
	    print("<<== PNAICharacter:startFight()") --]]
	end
--------------------------------------------------------
--[[%
Called when hearing a sound
No yet implemented
%--]]	
	function OBJ:hear()
		--do something
	end
--------------------------------------------------------
--[[%
Called at every loop
%--]]
	OVERRIDE(OBJ, "onUpdate")
	function OBJ:onUpdate(deltaTime)
	    --print("==>> PNAICharacter:onUpdate()")
	    --print(self)
		self:beSmart()
		self:PNCharacter_onUpdate(deltaTime)
	    --print("<<== PNAICharacter:onUpdate()")
	end
--------------------------------------------------------
--[[%
Called on a collision event
Not yet implemented
%--]]
	OVERRIDE(OBJ, "onCollision")
	function OBJ:onCollision(target, direction)
	-- Si target et direction et autre condition ok alors
		-- lance premier script self.scripts.event.collision[0]		
	end
--------------------------------------------------------
--[[%
Called when an object enters the frustrum of the character
If it is detected as an ennemy, the character switches to the fighting mode
%--]]
	OVERRIDE(OBJ, "onFrustrumIn")
	function OBJ:onFrustrumIn(target)
		self:PNCharacter_onFrustrumIn(target)
		if (self.health_state < HEALTH_STATE.COMA and self.realCharacType ~= CHARACTER_TYPE.CIVILIAN) then
			--pnprint(self.id .. " viewing " .. target:getId() .. "\n")
			if ((target:getId() ~= self.id) and (isInstanceOf(target, "PNCharacter")) --[[and target:getCoord():getDistance(self:getCoord()) <= 250]]) then -- modif de stephane sur la distance
				--pnprint("J'ai cru voir un rominet !\n")
				if ((target:getCharacType() ~= self.realCharacType) and (target:getCharacType() ~= CHARACTER_TYPE.CIVILIAN) and (target.health_state < HEALTH_STATE.COMA)) then
					self.ennemies[target:getId()] = 1
					if (self:getViewTarget() == nil) then
						--pnprint("Mais oui, j'ai bien vu un rominet !\n")
						if (self.state ~= self.stateEnum.PN_IA_TRAVELING) then
							if (self:getCoord():getDistance(target:getCoord()) < (5 * self.selected_weapon.range)) then
								--pnprint("Il est pas loin, je vais me le faire !\n")
								self:startFight(target)
							else
								--pnprint("Je vais voir ca de plus pres !\n")
								self:moveTo(target:getCoord())
							end
						end
					end
				end
			end
		end
	end
--------------------------------------------------------
--[[%
Called when an object enters the frustrum of the character
%--]]
	OVERRIDE(OBJ, "onFrustrumOut")
	function OBJ:onFrustrumOut(target)
		if (self.health_state < HEALTH_STATE.COMA) then
			self:PNCharacter_onFrustrumOut(target)
			--pnprint(self.id .. " NOT viewing " .. target:getId() .. "\n")
			if (target:getId() ~= self.id) then
				if (self.ennemies[target:getId()] ~= nil) then
					self.ennemies[target:getId()] = nil
				end
			end
		end
	end
--------------------------------------------------------
--[[%
Called at init
Not used yet
%--]]
	OVERRIDE(OBJ, "onInit")
  	function OBJ:onInit()
		self:PNCharacter_onInit()
	end
--------------------------------------------------------
--[[%
Called at destruction
Not used yet
%--]]
	OVERRIDE(OBJ, "onDestroy")
	function OBJ:onDestroy()
		self:PNCharacter_onDestroy()
	end
--------------------------------------------------------
--[[%
Call at another Character's death
%--]]
	function OBJ:isDead(deadId)
		--pnprint("=> " .. self.id .. ":isDead(" .. deadId .. ")\n")
		if (self.ennemies[deadId] ~= NULL) then
			self.ennemies[deadId] = NULL
		end
		if ((self:getViewTarget() ~= nil) and (self:getViewTarget():getId() == deadId)) then
			self.elapsed_turns = 0
			self.combat_state = COMBAT_STATE.NEUTRAL
			self:onMoveForward(ACTION_STATE.STOP)
			self:setMovingState(PN3DObject.STATE_NONE)
			local newTargetId = -1
			for id, val in self.ennemies do
				if (val == 1) then
					if (newTargetId == -1) then
						newTargetId = id
					end
				elseif (self:getCoord():getDistance(gameMap.entities.all[newTargetId]:GetCoord()) > self:getCoord():getDistance(gameMap.entities.all[id]:GetCoord())) then
					if (gameMap.entities.all[id].health_state < HEALTH_STATE.COMA) then
						newTargetId = id
					end
				end
			end
			local target = gameMap.entities.all[newTargetId]
			if (newTargetId ~= -1) then
				if (self:getCoord():getDistance(target:getCoord()) < 10 * self.selected_weapon.range) then
					--pnprint("Il est pas loin, je vais me le faire !\n")
					self:startFight(target)
				else
					--pnprint("Je vais voir ca de plus pres !\n")
					self:moveTo(target:getCoord())
				end
			else
				self:setTarget(nil)
				if (self.state == self.stateEnum.PN_IA_WAIT_ANIM_END)then
					self.restoreAtAnimEnd = true;
				else
					self:restoreState()
				end
			end
		end
		--pnprint("<= " .. self.id .. ":isDead(" .. deadId .. ")\n")
	end
--------------------------------------------------------
--[[%
Called when another character gets out of Coma
%--]]
	function OBJ:isAlive(liveId)
		if (self.seen_entities[liveId] ~= nil) then
			self:onFrustrumIn(gameMap.entities.all[liveId])
		end
	end
--------------------------------------------------------
	return OBJ
end
