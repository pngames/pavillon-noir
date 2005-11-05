function PNAIPirateClass(id)
	pnprint("PNAIPirate creating\n")
	-- make inheritance -----
	local OBJ = inheritFrom({className = "PNAIPirate"}, PNAICharacterClass(id))
    -------------------------
    OBJ:setId(id)
    OBJ.id = id
    pnprint("PNAIPirate creating 2\n")

	OBJ.realCharacType = CHARACTER_TYPE.PIRATE
	OBJ.shownCharacType = CHARACTER_TYPE.PIRATE
	OBJ.state = OBJ.stateEnum.PN_IA_PASSIVE
--------------------------------------------------------
--[[%
Called while handling a fight
%--]]
	OVERRIDE(OBJ, "manageFight")
	function OBJ:manageFight()
		pnprint("pirate managing fight\n")
		if (self:getCoord():getDistance(self:getViewTarget():getCoord()) > self.selected_weapon.range) then
			self:onMoveForward(ACTION_STATE.START)
		else
			self:onMoveForward(ACTION_STATE.STOP)
		end
		--pnprint("fight managed\n")
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
		self.combat_state = COMBAT_STATE.ATTACK
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
