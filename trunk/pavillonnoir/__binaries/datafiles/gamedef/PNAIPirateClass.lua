function PNAIPirateClass(id)
	pnprint("PNAIPirate creating\n")
	-- make inheritance -----
	local OBJ = inheritFrom(PNAICharacterClass(id))
	OBJ.className = "PNAIPirate" 
    -------------------------
    OBJ:setId(id)
    OBJ.id = id
    pnprint("PNAIPirate creating 2\n")

	OBJ.realCharacType = CHARACTER_TYPE.PIRATE
	OBJ.shownCharacType = CHARACTER_TYPE.PIRATE
	OBJ.state = OBJ.stateEnum.PN_IA_PASSIVE
	OBJ.ennemyJustReached = true
	OBJ.stats=	{strength=5,
						 address=3,
						 adaptation=6,
						 awareness=6,
						 resistance=6
						}
	OBJ.skills=	{h2h_combat=9, -- hand to hand
						 firearm=5,
						 slasher=8,
						 throw_weapon=7,
						 dodge=2,
						 escrime=2
						}
	OBJ.armor = 0
--------------------------------------------------------
--[[%
Called while handling a fight
%--]]
	OVERRIDE(OBJ, "manageFight")
	function OBJ:manageFight()
	    --print("==>> PNAIPirate:manageFight()")
	    --print(self)
	    if (self.combat_state == COMBAT_STATE.ATTACK) then
	    	return
	    end
		if (self:getCoord():getDistance(self:getViewTarget():getCoord()) > self.selected_weapon.range) then
			if (self.elapsedTurns == 0) then
				self:onMoveForward(ACTION_STATE.START)
			end
			self.ennemyJustReached = false
			self.elapsedTurns = 0
		else
			if (self.elapsedTurns == 0) then
				self:onMoveForward(ACTION_STATE.STOP)
				self.ennemyJustReached = true
			end
			if ((self.ennemyJustReached == true) or ((self.elapsedTurns) == (self.stats.awareness * 50))) then
				--attack
				self.combat_state = COMBAT_STATE.ATTACK
				gameMap:onAttack(self.id, self:getViewTarget():getId())
				self.elapsedTurns = 1
				self.ennemyJustReached = false
			else
				self.elapsedTurns = self.elapsedTurns + 1
			end
		end
		--print("<<== PNAIPirate:manageFight()")
	end
--------------------------------------------------------
--[[%
Called when an ennemy enters the frustrum
Prepares the Character to handle a fight
%--]]
	OVERRIDE(OBJ, "startFight")
	function OBJ:startFight()
		pnprint("fightpirate\n")
		self:setState(self.stateEnum.PN_IA_FIGHTING)
		self:onMoveForward(ACTION_STATE.STOP)
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
