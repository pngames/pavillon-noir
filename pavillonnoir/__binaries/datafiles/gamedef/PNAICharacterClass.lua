function PNAICharacterClass(id)
	pnprint("PNAICharacterClass creating\n")
	-- make inheritance -----
	local OBJ = inheritFrom({className = "PNAICharacter"}, PNCharacterClass(id))
    -------------------------
    OBJ:setId(id)
    OBJ.id = id
    pnprint("PNCharacterClass creating 2\n")

	OBJ:setMovingSpeed(0.5)
	OBJ.hurry = false
	OBJ.realCharacType = CHARACTER_TYPE.CIVILIAN
	OBJ.shownCharacType = CHARACTER_TYPE.CIVILIAN
--	pnprint("create pathFinding\n")
	OBJ.pathFinding = PNPathFinding:new_local(OBJ:getCoord())
--	pnprint("pathFinding created\n")
--	pnprint("create pathFinding\n")
	OBJ.pathFinding:unserializeFromFile(gameMap:getWpFile())
--	pnprint("pathFinding created\n")
	OBJ.toReach = PN3DObject:new_local()
	OBJ.stateEnum = {PN_IA_PASSIVE = 0, PN_IA_TRAVELLING = 1, PN_IA_FIGHTING = 2}
	OBJ.state = OBJ.stateEnum.PN_IA_PASSIVE
	OBJ.pastStates = {}
	OBJ.ennemies = {}
--------------------------------------------------------
--[[%
Called at the update
Calls a Behaviour Function depending on the state in which the character is
%--]]		
	function OBJ:beSmart()
		if (self.state == self.stateEnum.PN_IA_TRAVELLING) then
			self:manageTravel()
		
		elseif (self.state == self.stateEnum.PN_IA_FIGHTING) then
			self:manageFight()
		end
	end
--------------------------------------------------------
--[[%
Behaviour Function
Called during PathFinding to resolve the travel
%--]]
	function OBJ:manageTravel()
		local distance = self:getCoord():getDistance(self.toReach:getCoord())
			if (distance <= 50.0) then
				self.pathFinding:moveNext(self.toReach)
				local distance2 = self:getCoord():getDistance(self.toReach:getCoord())
					if (distance2 <= 50.0) then
						self:restoreState()
						self:onMoveForward(ACTION_STATE.STOP)
						return
					end
				self:setTarget(self.toReach)
				self:setTargetMode(self.TMODE_VIEW_ABS_LOCKED)
			end
	end
--------------------------------------------------------
--[[%
Called while handling a fight
%--]]
	function OBJ:manageFight()
	end
--------------------------------------------------------
--[[%
Called on a MoveTo event
Prepares the character to handle the PathFinding
%--]]
	function OBJ:moveTo(p)
		self.state = self.stateEnum.PN_IA_TRAVELLING
		self.pathFinding:moveTo(p)
		self.pathFinding:moveNext(self.toReach)
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
	function OBJ:startFight()
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
Returns the type of the character that is visible to others
%--]]
	function OBJ:getCharacType()
		return self.shownCharacType
	end
--------------------------------------------------------
--[[%
Called on a behaviour change
Sets a new state impliying a new behaviour for the character
Adds the old state on a stack to retrieve it later
%--]]
	function OBJ:setState(st)
		table.insert(self.pastStates, 0, self.state)
		self.state = st
		if (self.pastStates[0] == self.stateEnum.PN_IA_TRAVELLING) then
			self:onMoveForward(ACTION_STATE.STOP)
		end
	end
--------------------------------------------------------
--[[%
Called when a behaviour is not needed anymore
Sets the character's behaviour to the previous state on the stack
%--]]
	function OBJ:restoreState()
--		pnprint("=> PNCharacter:restoreState()\n")
		self.state = self.pastStates[0]
		table.remove(self.pastStates,0)
--		pnprint("<= PNCharacter:restoreState()\n")
	end
--------------------------------------------------------
--[[%
Called at every loop
%--]]
	function OBJ:onUpdate(deltaTime)
		self:beSmart()
		self:update(deltaTime)
	end
--------------------------------------------------------
--[[%
Called on a collision event
Not yet implemented
%--]]
	function OBJ:onCollision(target, direction)
	-- Si target et direction et autre condition ok alors
		-- lance premier script self.scripts.event.collision[0]		
	end
--------------------------------------------------------
--[[%
Called when an object enters the frustrum of the character
If it is detected as an ennemy, the character switches to the fighting mode
%--]]
	function OBJ:onFrustrumIn(target)
		self.__index:onFrustrumIn(target)
		pnprint(self.id .. " viewing " .. target:getId() .. "\n")
		if ((target:getId() ~= self.id) and (isInstanceOf(target, "PNCharacter"))) then
			pnprint("ennemy spotted\n")
			self.ennemies[target:getId()] = 1
			if ((target:getCharacType() ~= self.realCharacType) and (target:getCharacType() ~= CHARACTER_TYPE.CIVILIAN)) then
				self:setTarget(target)
				self:startFight()
			end
		end
	end
--------------------------------------------------------
--[[%
Called when an object enters the frustrum of the character
%--]]
	function OBJ:onFrustrumOut(target)
		if (target:getId() ~= self.id) then
			if (self.ennemies[target:getId()] ~= NULL) then
				self.ennemies[target:getId()] = NULL
			end
		end
	end
--------------------------------------------------------
--[[%
Called at init
Not used yet
%--]]
  	function OBJ:onInit()
	end
--------------------------------------------------------
--[[%
Call at destruction
Not used yet
%--]]
	function OBJ:onDestroy()
	end
--------------------------------------------------------
	return OBJ
end
