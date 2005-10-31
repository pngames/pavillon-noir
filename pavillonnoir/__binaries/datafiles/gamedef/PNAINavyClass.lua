function PNAINavyClass(id)
	pnprint("PNAINavy creating\n")
	-- make inheritance -----
	local OBJ = inheritFrom({className = "PNAINavy"}, PNAICharacterClass(id))
    -------------------------
    OBJ:setId(id)
    OBJ.id = id
    pnprint("PNAINavy creating 2\n")

	OBJ.realCharacType = CHARACTER_TYPE.NAVY
	OBJ.shownCharacType = CHARACTER_TYPE.NAVY
	OBJ.state = OBJ.stateEnum.PN_IA_PASSIVE
--------------------------------------------------------
--[[%
Called while handling a fight
%--]]
	function OBJ:manageFight()
		pnprint("LET'S FIGHT, BITCH !\n")
		if (self:getCoord():getDistance(self.getViewTarget():getCoord()) > self.selected_weapon.range) then
			self:onMoveForward(ACTION_STATE.START)
		else
			self:onMoveForward(ACTION_STATE.STOP)
		end
	end
--------------------------------------------------------
--[[%
Called when an ennemy enters the frustrum
Prepares the Character to handle a fight
%--]]
	function OBJ:startFight()
		pnprint("fightnavy\n")
		self:setState(self.stateEnum.PN_IA_FIGHTING)
		self:onMoveForward(ACTION_STATE.STOP)
		self.combat_state = COMBAT_STATE.DEFENSE
		-- anim combat, sortir l'arme toussa
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
Called at destruction
Not used yet
%--]]
	function OBJ:onDestroy()
	end
--------------------------------------------------------
	return OBJ
end