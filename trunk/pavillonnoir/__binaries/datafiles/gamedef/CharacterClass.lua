function CharacterClass(id)
	pnprint("CharacterClass creating\n")
    local Character = PNCharacter:new_local()
    Character.className = "Character"
    Character:setId(id)
    Character.id = id
    pnprint("CharacterClass creating 2\n")
	if (Character.id ~= "") then 
		gameMap.entities.all[Character.id] = Character
	end
	Character:setMovingSpeed(0.5)
	Character.hurry = false
--	pnprint("create pathFinding\n")
	Character.pathFinding = PNPathFinding:new_local(Character:getCoord())
--	pnprint("pathFinding created\n")
--	pnprint("create pathFinding\n")
	Character.pathFinding:unserializeFromFile(gameMap:getWpFile())
--	pnprint("pathFinding created\n")
	Character.toReach = PN3DObject:new_local()
	Character.stateEnum = {PN_IA_PASSIVE = 0, PN_IA_TRAVELLING = 1, PN_IA_FIGHTING = 2}
	Character.state = Character.stateEnum.PN_IA_PASSIVE
	Character.pastStates = {}
	
	function Character:beSmart()
		if (self.state == self.stateEnum.PN_IA_TRAVELLING) then --ca pete ici, la 
			local distance = self:getCoord():getDistance(self.toReach:getCoord())
			if (distance <= 50.0) then
				self.pathFinding:moveNext(self.toReach)
				local distance2 = self:getCoord():getDistance(self.toReach:getCoord())
					if (distance2 <= 50.0) then
						self:restoreState()
						self:onLuaActionMoveForward(false)
						return
					end
					self:setTarget(self.toReach)
					self:setMovingMode(self.MMODE_VIEW_ABS_LOCKED)
			end
		end
		
	end

	function Character:moveTo(p)
		self.state = self.stateEnum.PN_IA_TRAVELLING
		self.pathFinding:moveTo(p)
		self.pathFinding:moveNext(self.toReach)
		-- setDirect and rotate
		self:setTarget(self.toReach)
		self:setMovingMode(self.MMODE_VIEW_ABS_LOCKED)
		self:onLuaActionMoveForward(true)
	end

	function Character:hear()
		--do something
	end

	function Character:see()
		--do something
	end

	function Character:startFight()
		--do something
	end
	
	function Character:manageFight()
		--do something
	end

	function Character:setState(st)
		table.insert(self.pastStates, 0, self.state)
		self.state = st
	end

	function Character:restoreState()
--		pnprint("=> Character:restoreState()\n")
		self.state = self.pastStates[0]
		table.remove(self.pastStates,0)
--		pnprint("<= Character:restoreState()\n")
	end
	
	--temp function
	
	function Character:onLuaUpdate(deltaTime)
		self:beSmart()
		self:update(deltaTime)
	end
	
	function Character:onLuaActionMoveTo(target)
		--do something
	end
	
	function Character:oncollision(target, direction)
	-- Si target et direction et autre condition ok alors
		-- lance premier script self.scripts.event.collision[0]		
	end

    ---------------------move events-----------------------
	function Character:onLuaActionMoveForward(state)
		pnprint("LUA Character:onLuaActionMoveForward()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function Character:onLuaActionMoveBackward(state)
		pnprint("LUA Character:onLuaActionMoveBackward()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function Character:onLuaActionMoveLeft(state)
		pnprint("LUA Character:onLuaActionMoveLeft()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function Character:onLuaActionMoveRight(state)
		pnprint("LUA Character:onLuaActionMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end

	function Character:onFrustrumIn(target)
		pnprint(target.id)
		pnprint(" entered Frustrum\n")
	end

	function Character:onFrustrumOut(target)
		pnprint(target.id)
		pnprint(" exited Frustrum\n")
	end

	return Character	
end