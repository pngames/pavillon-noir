
COMBAT_STATE={NEUTRAL=0,
			 ATTACK=1,
			 DEFENCE=2,
			 DODGE=3
			 }
CHARACTER_TYPE={CIVILAN=0,
				NAVY=1,
				PIRATE=2
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
	PNCharacter.health_state = 0
	PNCharacter.selected_arm = PNCharacter.items.weapons.h2h
	PNCharacter.combat_state = COMBAT_STATE.NEUTRAL
	PNCharacter.realCharacType = CHARACTER_TYPE.CIVILIAN
	PNCharacter.shownCharacType = CHARACTER_TYPE.CIVILIAN
	--------------------------------------
	PNCharacter.load_capacity = 10;
	--------------------------------------
	PNCharacter.seen_entities = {}
	--------------------------------------
	PNCharacter.view = PN3DCameraClass(PNCharacter.id .. "cam", PNCharacter, false)
	PNCharacter.view:addTargetMode(PNCharacter.TMODE_ORIENTATION_ABS_LOCKED)
	PNCharacter.view:addTargetMode(PNCharacter.TMODE_POSITION_ABS_LOCKED)
	PNCharacter.view:setTarget(PNCharacter);
	PNCharacter.view:setTargetPosition(0.0, 100.0, 0.0);
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
	function PNCharacter:onUpdate(deltaTime)
		self.view:update(deltaTime)
		self.__index:update(deltaTime)
	end

	function PNCharacter:getCharacType()
		return self.shownCharactType
	end

	return PNCharacter
end