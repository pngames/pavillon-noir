function CharacterClass()
	Character = PN3DSkeletonObjectClass()
	-- Character.__index = Character
	Character.hurry = false
	Character.pathFinding = PNPathFinding:new_local()
	Character.toReach = PN3DObject:new_local()
	Character.stateEnum = {PN_IA_PASSIVE = 0, PN_IA_TRAVELLING = 1, PN_IA_FIGHTING = 2}
	Character.state = Character.stateEnum.PN_IA_PASSIVE
	Character.pastStates = {}
	
	function Character:beSmart()
		if (self.state == self.stateEnum.PN_IA_TRAVELLING) then
			if (self:getCoord() == self.toReach:getCoord()) then
				self.pathFinding:moveNext(self.toReach)
					if (self:getCoord() == self.toReach:getCoord()) then
						self:restoreState()
						return
					end
					-- setDirect and rotate
					self:setTarget(self.toReach)
			end
		end
	end

	function Character:moveTo(p)
		self.state = self.stateEnum.PN_IA_TRAVELLING
		self.pathFinding:moveTo(p)
		self.pathFinding:moveNext(self.toReach)
		-- setDirect and rotate
		self:setTarget(self.toReach)
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
	
	function Character:onLuaUpdate(deltaTime)
		self:onUpdate(deltatime)
	end
	
	function Character:OnLuaActionMoveTo(target)
		
	end
	return Character	
end