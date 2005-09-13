function CharacterClass(id)
	local Character = PN3DSkeletonObjectClass(id)
	Character.className = "Character"
	Character.hurry = false
	Character.pathFinding = PNPathFinding:new_local()
	Character.toReach = PN3DObject:new_local()
	Character.stateEnum = {PN_IA_PASSIVE = 0, PN_IA_TRAVELLING = 1, PN_IA_FIGHTING = 2}
	Character.state = Character.stateEnum.PN_IA_PASSIVE
	Character.pastStates = {}
	
	function Character:beSmart()
		pnprint("besmart0\n")
		pnprint(self.state)
		pnprint("\nbesmart0bis\n")
		if (self.state == self.stateEnum.PN_IA_TRAVELLING) then --ca pete ici, la 
			pnprint("besmart1\n")
			if (self:getCoord() == self.toReach:getCoord()) then
				pnprint("besmart2\n")
				self.pathFinding:moveNext(self.toReach)
				pnprint("besmart3\n")
					if (self:getCoord() == self.toReach:getCoord()) then
						pnprint("besmart4\n")
						self:restoreState()
						pnprint("besmart5\n")
						self:OnLuaActionMoveForward(false)
						pnprint("besmart6\n")
						return
					end
					-- setDirect and rotate
					pnprint("besmart7\n")
					self:setTarget(self.toReach)
					pnprint("besmart8\n")
					self:setMovingMode(self.MMODE_VIEW_ABS_LOCKED)
					pnprint("besmart9\n")
			end
		end
		pnprint("exit besmart\n")
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
		self.state = self.pastStates[0]
		table.remove(self.pastStates,0)
	end
	
	--temp function
	function Character:luaUpdate(deltaTime)
		self:beSmart()
		self:update(deltaTime)
	end 
	
	function Character:onLuaUpdate(deltaTime)
		self:luaUpdate(deltaTime)
	end
	
	function Character:OnLuaActionMoveTo(target)
		--do something
	end

	return Character	
end