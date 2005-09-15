function CharacterClass(id)
	local Character = PN3DSkeletonObjectClass(id)
	Character.className = "Character"
	Character:setMovingSpeed(0.5)
	Character.hurry = false
	pnprint("create pathFinding\n")
	Character.pathFinding = PNPathFinding:new_local(Character:getCoord())
	pnprint("pathFinding created\n")
	pnprint("create pathFinding\n")
	Character.pathFinding:unserialize(gameMap:getWpFile())
	pnprint("pathFinding created\n")
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
						self:OnLuaActionMoveForward(false)
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
		self:OnLuaActionMoveForward(true)
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
		pnprint("=> Character:restoreState()\n")
		self.state = self.pastStates[0]
		table.remove(self.pastStates,0)
		pnprint("<= Character:restoreState()\n")
	end
	
	--temp function
	function Character:luaUpdate(deltaTime)
		self:beSmart()
		self:update(deltaTime)
		pnprint(self:getCoord().x)
		pnprint(self:getCoord().y)
		pnprint(self:getCoord().z)
		pnprint("\n")
	end 
	
	function Character:onLuaUpdate(deltaTime)
		self:luaUpdate(deltaTime)
	end
	
	function Character:OnLuaActionMoveTo(target)
		--do something
	end


	return Character	
end