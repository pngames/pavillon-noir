
COMBAT_STATE={NEUTRAL=0,
			 ATTACK=1,
			 DEFENCE=2,
			 DODGE=3
			 }

function PNCharacterClass(id)
	----------inheritance-----------------
	local PNCharacter = inheritFrom({className = "PNCharacter"}, PN3DSkeletonObjectClass(id))
	--------------------------------------
	------- LIST OF STATS-----------------
	PNCharacter.stats=	{strength=0,
						 address=0,
						 adaptation=0,
						 awareness=0,
						 resistance=0
						}
	--------------------------------------
	-------LIST OF SKILLS-----------------
	PNCharacter.skills=	{h2h_combat=0,
						 firearm=0,
						 slasher=0,
						 throw_weapon=0,
						 dodge=0,
						 escrime=0
						}
	--------------------------------------
	-------LIST OF ITEMS------------------
	PNCharacter.items = {}
	--------------------------------------
	-------LIST OF WEAPONS----------------
	PNCharacter.items.weapons	=	{h2h=0}
	--------------------------------------
	-------LIST OF WOUNDS BY MEMBER-------
	PNCharacter.m_wounds=	{head=0,
							 torso=0,
							 r_arm=0,
							 l_arm=0,
							 r_leg=0,
							 l_leg=0
							}
	--------------------------------------
	PNCharacter.heal_state = 0
	PNCharacter.selected_arm = PNCharacter.items.weapons.h2h	
	PNCharacter.combat_state = COMBAT_STATE.NEUTRAL
	--------------------------------------
	PNCharacter.load_capacity = 10;
	--------------------------------------
	PNCharacter.seen_entities = {}
	--------------------------------------

	PNCharacter.view = PN3DCameraClass(PNCharacter.id .. "cam", self, false)

-------------------------------------------------------------------------------	
	function PNCharacter:onFrustrumIn(target)
		if (target:getId() ~= self.id) then
          PNCharacter.seen_entities[target.id] = gameMap.entities.all[targetId]  
		end
	end
-------------------------------------------------------------------------------
	function PNCharacter:onFrustrumOut(target)
		if (target:getId() ~= self.id) then
          PNCharacter.seen_entities[target.id] = nil
		end
	end
-------------------------------------------------------------------------------
    function PNCharacter:onAttack(sourceId, targetId)
        
    end
--------------------------------------------------------------------------------

	return PNCharacter
end