function PNIACharacterClass(id)
	pnprint("PNIACharacterClass creating\n")
	-- make inheritance -----
	local PNIACharacter = inheritFrom({className = "PNIACharacter"}, PNCharacterClass(id))
    -------------------------
    pnprint("PNIACharacterClass creating 2\n")

	PNIACharacter:setMovingSpeed(0.5)
	PNIACharacter.hurry = false
	PNIACharacter.characTypeEnum = {PN_CHARAC_PIRATE = 0, PN_CHARAC_NAVY = 1, PN_CHARAC_CIVILIAN = 2}
	PNIACharacter.realCharacType = PNIACharacter.characTypeEnum.PN_CHARAC_CIVILIAN
	PNIACharacter.shownCharacType = PNIACharacter.characTypeEnum.PN_CHARAC_CIVILIAN
--	pnprint("create pathFinding\n")
	PNIACharacter.pathFinding = PNPathFinding:new_local(PNIACharacter:getCoord())
--	pnprint("pathFinding created\n")
--	pnprint("create pathFinding\n")
	PNIACharacter.pathFinding:unserializeFromFile(gameMap:getWpFile())
--	pnprint("pathFinding created\n")
	PNIACharacter.toReach = PN3DObject:new_local()
	PNIACharacter.stateEnum = {PN_IA_PASSIVE = 0, PN_IA_TRAVELLING = 1, PN_IA_FIGHTING = 2}
	PNIACharacter.state = PNIACharacter.stateEnum.PN_IA_PASSIVE
	PNIACharacter.pastStates = {}
	PNIACharacter.ennemies = {}
	
	function PNIACharacter:onInit()
	end
	
	function PNIACharacter:beSmart()
		if (self.state == self.stateEnum.PN_IA_TRAVELLING) then --ca pete ici, la 
			local distance = self:getCoord():getDistance(self.toReach:getCoord())
			if (distance <= 50.0) then
				self.pathFinding:moveNext(self.toReach)
				local distance2 = self:getCoord():getDistance(self.toReach:getCoord())
					if (distance2 <= 50.0) then
						self:restoreState()
						self:onMoveForward(false)
						return
					end
					self:setTarget(self.toReach)
					self:addTargetMode(self.TMODE_VIEW_ABS_LOCKED)
			end
		end
	end

	function PNIACharacter:moveTo(p)
		self.state = self.stateEnum.PN_IA_TRAVELLING
		self.pathFinding:moveTo(p)
		self.pathFinding:moveNext(self.toReach)
		-- setDirect and rotate
		self:setTarget(self.toReach)
		self:addTargetMode(self.TMODE_VIEW_ABS_LOCKED)
		self:onMoveForward(true)
	end

	function PNIACharacter:hear()
		--do something
	end

	function PNIACharacter:see()
		--do something
	end

	function PNIACharacter:startFight()
		--do something
	end

	function PNIACharacter:manageFight()
		--do something
	end

	function PNIACharacter:getCharacType()
		return self.shownCharacType
	end

	function PNIACharacter:setState(st)
		table.insert(self.pastStates, 0, self.state)
		self.state = st
		if (self.pastStates[0] == self.stateEnum.PN_IA_TRAVELLING) then
			self:onActionMoveForward(false)
		end
	end

	function PNIACharacter:restoreState()
--		pnprint("=> PNIACharacter:restoreState()\n")
		self.state = self.pastStates[0]
		table.remove(self.pastStates,0)
--		pnprint("<= PNIACharacter:restoreState()\n")
	end

	--temp function

	function PNIACharacter:onUpdate(deltaTime)
		self:beSmart()
		self.__index:onUpdate(deltaTime)
	end

	function PNIACharacter:onActionMoveTo(target)
		--do something
	end

	function PNIACharacter:oncollision(target, direction)
	-- Si target et direction et autre condition ok alors
		-- lance premier script self.scripts.event.collision[0]		
	end

	function PNIACharacter:onFrustrumIn(target)
		pnprint(self.id .. " sees a " .. target.className .."\n")
		if ((target:getId() ~= self.id) and (isInstanceOf(target, "PNCharacter"))) then
			self.ennemies[target:getId()] = 1
			if ((target:getCharacType() ~= self.realCharacType) and (target:getCharacType() ~= CHARACTER_TYPE.CIVILIAN)) then
				self:setTarget(target)
				self:setState(PN_IA_FIGHTING)
			end
		end
	end

	function PNIACharacter:onFrustrumOut(target)
		if (target:getId() ~= self.id) then
			if (self.ennemies[target:getId()] ~= NULL) then
				self.ennemies[target:getId()] = NULL
				--pnprint(target:getId() .. " exits frustrum of " self.id .. "\n")
			end
		end
	end

  	function PNIACharacter:onInit()
	end

	function PNIACharacter:onDestroy()
	end

	return PNIACharacter
end
