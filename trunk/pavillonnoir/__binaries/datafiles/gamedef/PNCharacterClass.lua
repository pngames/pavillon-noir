function PNCharacterClass(id)
	pnprint("PNCharacterClass creating\n")
	-- make inheritance -----
	pnprint("PN3DSkeletonObjectClass creating\n")
    local PNCharacter = {__index = PN3DSkeletonObject:new_local()}
	PNCharacter.__instance  = PNCharacter.__index
    setmetatable(PNCharacter, PNCharacter)
    tolua.inherit(PNCharacter, PNCharacter.__instance) -- make obj be recognize as PN3DSkeletonObject
	PNCharacter.className = "PNCharacterClass"
    -------------------------
    PNCharacter:setId(id)
    PNCharacter.id = id
    pnprint("PNCharacterClass creating 2\n")
--	if (PNCharacter.id ~= "") then 
--		gameMap.entities.all[PNCharacter.id] = PNCharacter
--	end
	PNCharacter:setMovingSpeed(0.5)
	PNCharacter.hurry = false
--	pnprint("create pathFinding\n")
	PNCharacter.pathFinding = PNPathFinding:new_local(PNCharacter:getCoord())
--	pnprint("pathFinding created\n")
--	pnprint("create pathFinding\n")
	PNCharacter.pathFinding:unserializeFromFile(gameMap:getWpFile())
--	pnprint("pathFinding created\n")
	PNCharacter.toReach = PN3DObject:new_local()
	PNCharacter.stateEnum = {PN_IA_PASSIVE = 0, PN_IA_TRAVELLING = 1, PN_IA_FIGHTING = 2}
	PNCharacter.state = PNCharacter.stateEnum.PN_IA_PASSIVE
	PNCharacter.pastStates = {}
	
	function PNCharacter:onLuaInit()
	end
	
	function PNCharacter:beSmart()
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

	function PNCharacter:moveTo(p)
		self.state = self.stateEnum.PN_IA_TRAVELLING
		self.pathFinding:moveTo(p)
		self.pathFinding:moveNext(self.toReach)
		-- setDirect and rotate
		self:setTarget(self.toReach)
		self:setMovingMode(self.MMODE_VIEW_ABS_LOCKED)
		self:onLuaActionMoveForward(true)
	end

	function PNCharacter:hear()
		--do something
	end

	function PNCharacter:see()
		--do something
	end

	function PNCharacter:startFight()
		--do something
	end
	
	function PNCharacter:manageFight()
		--do something
	end

	function PNCharacter:setState(st)
		table.insert(self.pastStates, 0, self.state)
		self.state = st
	end

	function PNCharacter:restoreState()
--		pnprint("=> PNCharacter:restoreState()\n")
		self.state = self.pastStates[0]
		table.remove(self.pastStates,0)
--		pnprint("<= PNCharacter:restoreState()\n")
	end
	
	--temp function
	
	function PNCharacter:onLuaUpdate(deltaTime)
		self:beSmart()
		self:update(deltaTime)
	end
	
	function PNCharacter:onLuaActionMoveTo(target)
		--do something
	end
	
	function PNCharacter:oncollision(target, direction)
	-- Si target et direction et autre condition ok alors
		-- lance premier script self.scripts.event.collision[0]		
	end

    ---------------------move events-----------------------
	function PNCharacter:onLuaActionMoveForward(state)
		pnprint("LUA PNCharacter:onLuaActionMoveForward()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function PNCharacter:onLuaActionMoveBackward(state)
		pnprint("LUA PNCharacter:onLuaActionMoveBackward()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function PNCharacter:onLuaActionMoveLeft(state)
		pnprint("LUA PNCharacter:onLuaActionMoveLeft()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function PNCharacter:onLuaActionMoveRight(state)
		pnprint("LUA PNCharacter:onLuaActionMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end

	function PNCharacter:onFrustrumIn(target)
		pnprint(target.id)
		pnprint(" entered Frustrum\n")
	end

	function PNCharacter:onFrustrumOut(target)
		pnprint(target.id)
		pnprint(" exited Frustrum\n")
	end

	return PNCharacter	
end
