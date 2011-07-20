function PNAINavyClass(id)
	--pnprint("PNAINavy creating\n")
	-- make inheritance -----
	local OBJ = inheritFrom(PNAICharacterClass(id))
	OBJ.className = "PNAINavy" 
    -------------------------
    OBJ:setId(id)
    OBJ.id = id
    --pnprint("PNAINavy creating 2\n")

	OBJ.realCharacType = CHARACTER_TYPE.NAVY
	OBJ.shownCharacType = CHARACTER_TYPE.NAVY
	OBJ.state = OBJ.stateEnum.PN_IA_PASSIVE
	OBJ.ennemyJustReached = false
	OBJ.elapsedTurns = 0
	OBJ.stats=	{strength=2,
						 address=7,
						 adaptation=6,
						 awareness=4,
						 resistance=7
						}
	OBJ.skills=	{h2h_combat=5,
						 firearm=7,
						 slasher=4,
						 throw_weapon=3,
						 dodge=6,
						 escrime=5
						}
	OBJ.armor = 1
--------------------------------------------------------
--[[%
Called while handling a fight
%--]]
	OVERRIDE(OBJ, "manageFight")
	function OBJ:manageFight()
		--print("==>> PNAINavy:manageFight()")
		--print(self)
	    if (self.state == PN_IA_WAIT_ANIM_END or self:getViewTarget() == nil) then
	    	return
	    end
	    local targetDistance = self:getCoord():getDistance(self:getViewTarget():getCoord())
	    if (targetDistance > 10 * self.selected_weapon.range) then
	    	self.combat_state = COMBAT_STATE.NEUTRAL
	    	self.elapsedTurns = 0
	    	self:onMoveForward(ACTION_STATE.STOP)
	    	self:setTarget(nil)
	    	self:moveTo(self.startPosition)
	    end
		if (targetDistance > self.selected_weapon.range) then
			self.combat_state = COMBAT_STATE.DEFENSE
			if (self.elapsedTurns == 0) then
				self:onMoveForward(ACTION_STATE.START)
			end
			self.ennemyJustReached = false
			self.elapsedTurns = 0
		else
			self:onMoveForward(ACTION_STATE.STOP)
			if ((2 * self.health_state) < self:getViewTarget().health_state) then
				self.combat_state = COMBAT_STATE.DODGE
			else
				self.combat_state = COMBAT_STATE.DEFENSE
			end
			if (self.elapsedTurns == 0) then
				self.ennemyJustReached = true
			end
			if ((self.ennemyJustReached == true) or ((self.elapsedTurns) >= (225 / self.stats.awareness))) then
				--attack
				self.combat_state = COMBAT_STATE.ATTACK
				gameMap:onAttack(self.id, self:getViewTarget():getId())
				self.elapsedTurns = 1
				self.ennemyJustReached = false
			else
				self.elapsedTurns = self.elapsedTurns + 1
			end
		end
	    --print("<<== PNAINavy:manageFight()")
	end
--------------------------------------------------------
--[[%
Called when an ennemy enters the frustrum
Prepares the Character to handle a fight
%--]]
	OVERRIDE(OBJ, "startFight")
	function OBJ:startFight(target)
		--pnprint("fightnavy\n")
		self:setTarget(target)
		self:setTargetMode(self.TMODE_VIEW_ABS_LOCKED)
		self:setState(self.stateEnum.PN_IA_FIGHTING)
		self:onMoveForward(ACTION_STATE.STOP)
		self.combat_state = COMBAT_STATE.NEUTRAL
		-- anim combat, sortir l'arme toussa
	end
--------------------------------------------------------
--[[%
Called at init
Not used yet
%--]]
	OVERRIDE(OBJ, "onInit")
  	function OBJ:onInit()
  		self:PNAICharacter_onInit()
	end
--------------------------------------------------------
--[[%
Called at destruction
Not used yet
%--]]
	OVERRIDE(OBJ, "manageFight")
	function OBJ:onDestroy()
		self:PNAICharacter_onDestroy()
	end
--------------------------------------------------------
	return OBJ
end
