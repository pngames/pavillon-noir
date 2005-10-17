function PNCharacterClass(id)
	pnprint("PNCharacterClass creating\n")
	-- make inheritance -----
	pnprint("PNCharaterClass creating\n")
    local PNCharacter = {__index = PNCharacter:new_local()}
	PNCharacter.__instance  = PNCharacter.__index
    setmetatable(PNCharacter, PNCharacter)
    tolua.inherit(PNCharacter, PNCharacter.__instance) -- make obj be recognize as PN3DSkeletonObject
	PNCharacter.className = "PNCharacter"
    -------------------------
    PNCharacter:setId(id)
    PNCharacter.id = id
    pnprint("PNCharacterClass creating 2\n")

	PNCharacter:setMovingSpeed(0.5)
	PNCharacter.hurry = false
	PNCharacter.characTypeEnum = {PN_CHARAC_PIRATE = 0, PN_CHARAC_NAVY = 1, PN_CHARAC_CIVILIAN = 2}
	PNCharacter.realCharacType = PNCharacter.characTypeEnum.PN_CHARAC_CIVILIAN
	PNCharacter.shownCharacType = PNCharacter.characTypeEnum.PN_CHARAC_CIVILIAN
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
	PNCharacter.ennemies = {}
	
	function PNCharacter:onInit()
	end
	
	function PNCharacter:beSmart()
		if (self.state == self.stateEnum.PN_IA_TRAVELLING) then --ca pete ici, la 
			local distance = self:getCoord():getDistance(self.toReach:getCoord())
			if (distance <= 50.0) then
				self.pathFinding:moveNext(self.toReach)
				local distance2 = self:getCoord():getDistance(self.toReach:getCoord())
					if (distance2 <= 50.0) then
						self:restoreState()
						self:onActionMoveForward(false)
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
		self:onActionMoveForward(true)
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

	function PNCharacter:getCharacType()
		return self.shownCharacType
	end

	function PNCharacter:setState(st)
		table.insert(self.pastStates, 0, self.state)
		self.state = st
		if (self.pastStates[0] == self.stateEnum.PN_IA_TRAVELLING) then
			self:onActionMoveForward(false)
		end
	end

	function PNCharacter:restoreState()
--		pnprint("=> PNCharacter:restoreState()\n")
		self.state = self.pastStates[0]
		table.remove(self.pastStates,0)
--		pnprint("<= PNCharacter:restoreState()\n")
	end

	--temp function

	function PNCharacter:onUpdate(deltaTime)
		self:beSmart()
		self:update(deltaTime)
	end

	function PNCharacter:onActionMoveTo(target)
		--do something
	end

	function PNCharacter:oncollision(target, direction)
	-- Si target et direction et autre condition ok alors
		-- lance premier script self.scripts.event.collision[0]		
	end

    ---------------------move events-----------------------
	function PNCharacter:onActionMoveForward(state)
		pnprint("LUA PNCharacter:onActionMoveForward()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function PNCharacter:onActionMoveBackward(state)
		pnprint("LUA PNCharacter:onActionMoveBackward()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end

	function PNCharacter:onActionMoveLeft(state)
		pnprint("LUA PNCharacter:onActionMoveLeft()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function PNCharacter:onActionMoveRight(state)
		pnprint("LUA PNCharacter:onActionMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end

	function PNCharacter:onFrustrumIn(target)
		if (target:getId() ~= self.id) then
			self.ennemies[target:getId()] = 1
			if ((target:getCharacType() ~= self.realCharacType) and (target:getCharacType() ~= PNCharacter.characTypeEnum.PN_CHARAC_CIVILIAN)) then
				self:setTarget(target)
				self:setState(PN_IA_FIGHTING)
			end
		end
	end

	function PNCharacter:onFrustrumOut(target)
		if (target:getId() ~= self.id) then
			if (self.ennemies[target:getId()] ~= NULL) then
				self.ennemies[target:getId()] = NULL
			end
		end
	end

  	function PNCharacter:onInit()
	end

	function PNCharacter:onDestroy()
	end

	return PNCharacter
end
