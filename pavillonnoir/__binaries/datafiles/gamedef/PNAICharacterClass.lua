function PNAICharacterClass(id)
	pnprint("PNAICharacterClass creating\n")
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
    pnprint("PNCharacterClass creating 2\n")

	OBJ:setMovingSpeed(0.5)
	OBJ.hurry = false
	OBJ.realCharacType = CHARACTER_TYPE.CIVILIAN
	OBJ.shownCharacType = CHARACTER_TYPE.CIVILIAN
--	pnprint("create pathFinding\n")
	OBJ.pathFinding = PNPathFinding:new_local(OBJ:getCoord())
--	pnprint("pathFinding created\n")
--	pnprint("create pathFinding\n")
	OBJ.pathFinding:unserializeFromPath(gameMap:getWpFile())
--	pnprint("pathFinding created\n")
	OBJ.toReach = PN3DObject:new_local()
	OBJ.stateEnum = {PN_IA_PASSIVE = 0, PN_IA_TRAVELLING = 1, PN_IA_FIGHTING = 2, PN_IA_WAIT_ANIM_END = 3, PN_IA_COMA}
	OBJ.state = OBJ.stateEnum.PN_IA_PASSIVE
	OBJ.elapsedTurns = 0
	OBJ.pastStates = {}
	OBJ.ennemies = {}
	OBJ:setTarget(nil)
--	pnprint("PNCharacterClass creating 3\n")
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
		if (distance <= 10.0) then
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
		pnprint("moveto: " .. p.x .. " " .. p.y .. " " .. p.z .. "\n")
		self.state = self.stateEnum.PN_IA_TRAVELLING
		self.pathFinding:moveTo(p)
		self.pathFinding:moveNext(self.toReach)
		local fdistance = self:getCoord():getFlatDistance(self.toReach:getCoord())
		if (fdistance <= 10.0) then
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
	function OBJ:startFight()
	    print("==>> PNAICharacter:startFight()")
	    print(self)
	    print("<<== PNAICharacter:startFight()")
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
		pnprint("=> PNCharacter:restoreState()\n")
		self.state = self.pastStates[0]
		table.remove(self.pastStates,0)
		pnprint("<= PNCharacter:restoreState()\n")
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
		pnprint(self.id .. " viewing " .. target:getId() .. "\n")
		if ((target:getId() ~= self.id) and (isInstanceOf(target, "PNCharacter"))) then
			pnprint("J'ai cru voir un rominet !\n")
			self.ennemies[target:getId()] = 1
			if ((target:getCharacType() ~= self.realCharacType) and (target:getCharacType() ~= CHARACTER_TYPE.CIVILIAN) and (self:getViewTarget() == nil)) then
				pnprint("Mais oui, j'ai bien vu un rominet !\n")
				self:setTarget(target)
				self:setTargetMode(self.TMODE_VIEW_ABS_LOCKED)
				self:startFight()
			end
		end
	end
--------------------------------------------------------
--[[%
Called when an object enters the frustrum of the character
%--]]
	OVERRIDE(OBJ, "onFrustrumOut")
	function OBJ:onFrustrumOut(target)
		self:PNCharacter_onFrustrumOut(target)
		pnprint(self.id .. " NOT viewing " .. target:getId() .. "\n")
		if (target:getId() ~= self.id) then
			if (self.ennemies[target:getId()] ~= NULL) then
				self.ennemies[target:getId()] = NULL
			end
		end
	end
--------------------------------------------------------
--[[%
Called at the end of a Fight Action
%--]]
	OVERRIDE(OBJ, "onDamage")
	function OBJ:onDamage(damage, localisation)
		pnprint(self.id .. " gets " .. damage .. " at localisation " .. localisation .. " as damage\n")
		self.m_wounds[localisation] = self.m_wounds[localisation] + damage
		if (self.m_wounds[localisation] > self.health_state) then
			self.health_state = self.m_wounds[localisation]
		end
		if (self.health_state == HEALTH_STATE.COMA) then
			self:setState(self.stateEnum.PN_IA_COMA)
			--Anim Coma
		elseif (self.health_state >= HEALTH_STATE.LETHAL) then
			--Anim Death
			self:startAnimation(CHARACTER_ANIM.DIE)
			self:setState(self.stateEnum.PN_IA_COMA)
			gameMap:sendEventFromLua(self, 17) -- DeathEvent
			pnprint(self.id .. "is dead !\n")
		end
		
	end
--------------------------------------------------------
--[[%
Launches an Animation and waits for its end
%--]]
	OVERRIDE(OBJ, "waitForAnimEnd")
	function OBJ:waitForAnimEnd(anim)
		pnprint(self.id .. ":waitForAnimEnd(" .. anim .. ")\n")
		self.waitedAnim = anim
		self:startAnimation(anim)
		self:setState(self.stateEnum.PN_IA_WAIT_ANIM_END)
	end
--------------------------------------------------------
--[[%
Checks if waited Animation is the one that ended
%--]]
	OVERRIDE(OBJ, "checkAnimEnd")
	function OBJ:checkAnimEnd(anim)
		pnprint("=> PNAICharacter:checkAnimEnd(" .. anim .. ") and waited: " .. self.waitedAnim .. "\n")
		if ((self.state == self.stateEnum.PN_IA_WAIT_ANIM_END) and (self.waitedAnim == anim)) then
			self:restoreState()
			if (self.state == self.stateEnum.PN_IA_FIGHTING and (self.combat_state == COMBAT_STATE.ATTACK)) then
				self.combat_state = COMBAT_STATE.NEUTRAL
			end
		end
		pnprint("<= PNAICharacter:checkAnimEnd\n")
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
Not used yet
%--]]
	function OBJ:isDead(deadId)
		pnprint("=> " .. self.id .. ":isDead(" .. deadId .. ")\n")
		if (self:getViewTarget():getId() == deadId) then
			local newTargetId = -1
			for id in self.ennemies do
				if ((newTargetId == -1) or (self:getCoord():getDistance(gameMap.entities.all[newTargetId]:GetCoord()) > self:getCoord():getDistance(gameMap.entities.all[id]:GetCoord()))) then
					newTargetId = id
				end
			end
			if (newTargetId ~= -1) then
				self:setTarget(gameMap.entities.all[newTargetId])
			else
				self:setTarget(nil)
				self:restoreState()
			end
			if (self.ennemies[deadId] ~= NULL) then
				self.ennemies[deadId] = NULL
			end
		end
		pnprint("<= " .. self.id .. ":isDead(" .. deadId .. ")\n")
	end
--------------------------------------------------------
	return OBJ
end
