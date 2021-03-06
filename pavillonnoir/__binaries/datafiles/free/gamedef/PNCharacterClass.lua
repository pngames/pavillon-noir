COMBAT_STATE={NEUTRAL=0,
			 ATTACK=1,
			 DEFENCE=2,
			 DODGE=3
			 }

HEALTH_STATE={OK=0,
			 LIGHT=1,
			 SERIOUS=2,
			 DANGEROUS=3,
			 CRITIC=4,
			 COMA=5,
			 LETHAL=6
			 }

CHARACTER_TYPE={CIVILAN=0,
				NAVY=1,
				PIRATE=2
				}

CHARACTER_ANIM={IDLE=0,
				WALK_F=1,
				WALK_B=2,
				WALK_L=3,
				WALK_R=4,
				RUN_F=5,
				RUN_B=6,
				RUN_L=7,
				RUN_R=8,
				CROUCH=9,
				CROUCH_F=10,
				CROUCH_B=11,
				CROUCH_L=12,
				CROUCH_R=13,
				JUMP=14,
				DIE=15,
				STRIKE_HEAD=16,
				STRIKE_TORSO=17,
				STRIKE_LARM=18,
				STRIKE_RARM=19,
				STRIKE_LLEG=20,
				STRIKE_RLEG=21,
				DEAD=22,
				DEFENSE=23,
				HIT=24,
				YES=25,
				NO=26,
				}

CHARACTER_ATTITUDE={WALKING=0,
				  	RUNNING=1,
				  	CROUCHING=2,
				  	JUMPING=3
				  	}

CHARACTER_DIR_LONG={NONE=0,
					FORWARD=1,
					BACKWARD=-1
					}

CHARACTER_DIR_LATE={NONE=0,
					LEFT=1,
				  	RIGHT=-1
				    }

LOCALISATION={RANDOM = 0,
			  HEAD = 1,
			  TORSO = 2,
			  LARM = 3,
			  RARM = 4,
			  LLEG = 5,
			  RLEG = 6
			  }				    
				    
function PNCharacterClass(id)
	----------inheritance-----------------
	local OBJ = inheritFrom(PN3DSkeletonObjectClass(id))
	OBJ.className = "PNCharacter"
	--------------------------------------
	------- LIST OF STATS-----------------
	OBJ.stats=	{strength=0,
						 address=0,
						 adaptation=0,
						 awareness=0,
						 resistance=0
						}
	--------------------------------------
	-------LIST OF SKILLS-----------------
	OBJ.skills=	{h2h_combat=0, -- hand to hand
						 firearm=0,
						 slasher=0,
						 throw_weapon=0,
						 dodge=0,
						 escrime=0
						}
	--------------------------------------
	-------LIST OF ITEMS------------------
	OBJ.items = {}
	--------------------------------------
	-------LIST OF WEAPONS----------------
	OBJ.items.weapons	=	{h2h_combat=PNWeaponH2HClass("h2h")} --FIXME id de merde
	--------------------------------------
	-------LIST OF WOUNDS BY MEMBER-------
	OBJ.m_wounds=	{0,0,0,0,0,0,0}
	--------------------------------------
	OBJ.health_state = HEALTH_STATE.OK
	OBJ.comaTurns = 0
	OBJ.selected_weapon = OBJ.items.weapons.h2h_combat
	OBJ.combat_state = COMBAT_STATE.NEUTRAL
	OBJ.realCharacType = CHARACTER_TYPE.CIVILIAN
	OBJ.shownCharacType = CHARACTER_TYPE.CIVILIAN
	OBJ.stateEnum = {PN_IA_PASSIVE = 0, PN_IA_TRAVELLING = 1, PN_IA_FIGHTING = 2, PN_IA_WAIT_ANIM_END = 3, PN_IA_COMA = 4, PN_IA_DEAD = 5}
	OBJ.state = OBJ.stateEnum.PN_IA_PASSIVE
	OBJ.pastStates = {}
	OBJ.restoreAtAnimEnd = false
   	OBJ.updateLife = true
   	OBJ.goal = nil
	OBJ.startPosition = nil
	--------------------------------------
	OBJ.load_capacity = 10;
	--------------------------------------
	OBJ.seen_entities = {}
	--------------------------------------
	OBJ.view = PN3DCameraClass(OBJ.id .. "cam", false)
	OBJ.view:setTarget(OBJ);
	OBJ.view:setTargetPosition(0.0, 40.0, 0.0)
	--OBJ.view:setPositionBoneTarget("Bip01 Head")
	--OBJ.view:setViewBoneTarget("Bip01 Head")
	OBJ.view:addTargetMode(OBJ.TMODE_ORIENTATION_ABS_LOCKED)
	OBJ.view:addTargetMode(OBJ.TMODE_POSITION_ABS_LOCKED)
	
-------------------------------------------------------------------------------
	-----------------------------------------------------------
	--------------- Rotation parameter ------------------------
	OBJ.yawSpeed = 1.0
	OBJ.pitchSpeed = 1.0
	OBJ.defaulRotateSpeed = 1.0
	----------------------------------------------------------
	--------------- Translations parameter -------------------	
	OBJ.walkingSpeed = 0.05
	OBJ.runningSpeed = 0.2
	
	OBJ.attitude=CHARACTER_ATTITUDE.WALKING
	OBJ.dirLong= CHARACTER_DIR_LONG.NONE -- longitudinal direction
	OBJ.dirLate= CHARACTER_DIR_LATE.NONE	-- latteral direction
	OBJ.actualSpeed = OBJ.walkingSpeed
	OBJ:setMovingSpeed(OBJ.actualSpeed)
	-----------------------------------------------------------
	------------------- Jump Parameter ------------------------
	OBJ.JumpHeight= 0;
	--------------- Animation parameters ---------------------- 
	--OBJ:setAnimSpeed(100.0)
	OBJ.idleTime = 0
 	OBJ.waitedAnim = -1
	OBJ:setEnableLoop(CHARACTER_ANIM.WALK_F, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.WALK_B, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.WALK_R, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.WALK_L, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.RUN_F, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.RUN_B, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.RUN_L, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.RUN_R, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.CROUCH_F, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.CROUCH_B, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.CROUCH, true)		
	OBJ:setEnableLoop(CHARACTER_ANIM.IDLE, true)
	OBJ:setEnableLoop(CHARACTER_ANIM.DEAD, true)
	----------------- Fight Management ------------------------ 
	OBJ.armor = 0
	gameMap.fights[OBJ.id] = -1
	OBJ.strikeLocalisation = LOCALISATION.RANDOM
-------------------------------------------------------------------------------
---------------------move order callback-----------------------
--[[%
Call when someone tell the object to go backward
@param state boolean
	true -> start , false -> stop  
%--]]
	OVERRIDE(OBJ, "onMoveForward")	
	function OBJ:onMoveForward(state)
		self:PN3DSkeletonObject_onMoveForward(state)	
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to go backward and start apropriate annimation 
@param state boolean
	true -> start , false -> stop  
%--]]
	OVERRIDE(OBJ, "onMoveBackward")	
	function OBJ:onMoveBackward(state)
		--pnprint(self.id)
		--pnprint(":onMoveBackward\n")
		self:PN3DSkeletonObject_onMoveBackward(state)
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to go Left
@param state boolean
	true -> start , false -> stop  
%--]]	
	OVERRIDE(OBJ, "onMoveLeft")	
	function OBJ:onMoveLeft(state)
		--pnprint(self.id .. ":onMoveLeft=" .. state .. "\n")
		self:PN3DSkeletonObject_onMoveLeft(state)	
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to left and start apropriate animation 
@param state boolean
	true -> start , false -> stop  
%--]]		
	OVERRIDE(OBJ, "onMoveRight")	
	function OBJ:onMoveRight(state)
		--pnprint(self.id .. ":onMoveRight=" .. state .. "\n")
		self:PN3DSkeletonObject_onMoveRight(state)
	end
-------------------------------------------------------------------------------

--[[%
Call when someone tell the object to rotate right
@param state boolean
	true -> start , false -> stop  
%--]]	
	OVERRIDE(OBJ, "onRotateRight")	
	function OBJ:onRotateRight(state)
		--pnprint(self.id .. ":onRotateRight=" .. state .. "\n")
		self:PN3DSkeletonObject_onRotateRight(state)
	end	
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to rotate left
@param state boolean
	true -> start , false -> stop  
%--]]		
	OVERRIDE(OBJ, "onRotateLeft")	
	function OBJ:onRotateLeft(state)
		--pnprint(self.id)
		--pnprint(":onRotateLeft\n")
		self:PN3DSkeletonObject_onRotateLeft(state)	
		self.yawSpeed = self.defaultRotateSpeed;
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to rotate up
@param state boolean
	true -> start , false -> stop  
%--]]	
	OVERRIDE(OBJ, "onRotateUp")	
	function OBJ:onRotateUp(state)
		--pnprint(self.id)
		--pnprint(":onRotateUp\n")
		self.pitchSpeed = self.defaultRotateSpeed;
		self:PN3DSkeletonObject_onRotateUp(state)		
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to rotate down
@param state boolean
	true -> start , false -> stop  
%--]]	
	OVERRIDE(OBJ, "onRotateDown")	
	function OBJ:onRotateDown(state)
		--pnprint(self.id)
		--pnprint(":onRotateDown\n")
		self.pitchSpeed = self.defaultRotateSpeed
		self:PN3DSkeletonObject_onRotateDown(state)	
	end
-------------------------------------------------------------------------------
--[[%
Call when mouse is moved

@param xdelta integer
	the pixel delta displacement on the x axis since last mouse move
@param ydelta integer
	the pixel delta displacement on the y axis since last mouse move 
%--]]	
	function OBJ:MouseLook(xdelta, ydelta)
		--pnprint(self.id)
		--pnprint(":MouseLook\n")
	end

-------------------------------------------------------------------------------
--[[%
Call when an entity entrer in character sight
Add the entity in the seen_entities list
@param 3DObject
	the Entity entering in sight 
%--]]	
	function OBJ:onFrustrumIn(target)
		if (self.health_state < HEALTH_STATE.LETHAL and target:getId() ~= self:getId()) then
          OBJ.seen_entities[target:getId()] = target
		end
	end
-------------------------------------------------------------------------------
	function OBJ:onFrustrumOut(target)
		if (self.health_state < HEALTH_STATE.LETHAL and target:getId() ~= self:getId()) then
          OBJ.seen_entities[target:getId()] = nil
		end
	end
-------------------------------------------------------------------------------
    function OBJ:onAttack(sourceId, targetId)
		
    end
--------------------------------------------------------------------------------
    OVERRIDE(OBJ, "onInit")	
	function OBJ:onInit()
    	--pnprint("onInit()\n")
    	self:PN3DSkeletonObject_onInit()
    	self:setAnimSpeed(4.0)
    	self:setEnableLoop(CHARACTER_ANIM.WALK_F, true)
		self:setEnableLoop(CHARACTER_ANIM.WALK_B, true)
		self:setEnableLoop(CHARACTER_ANIM.WALK_R, true)
		self:setEnableLoop(CHARACTER_ANIM.WALK_L, true)
		self:setEnableLoop(CHARACTER_ANIM.RUN_F, true)
		self:setEnableLoop(CHARACTER_ANIM.RUN_B, true)
		self:setEnableLoop(CHARACTER_ANIM.RUN_L, true)
		self:setEnableLoop(CHARACTER_ANIM.RUN_R, true)
		self:setEnableLoop(CHARACTER_ANIM.CROUCH_F, true)
		self:setEnableLoop(CHARACTER_ANIM.CROUCH_B, true)
		self:setEnableLoop(CHARACTER_ANIM.CROUCH, true)		
		self:setEnableLoop(CHARACTER_ANIM.IDLE, true)
		self:setEnableLoop(CHARACTER_ANIM.DEAD, true)
    	--self.JumpHeight= (self:getMax().y - self:getMin().y ) /3
		--self.attitude = CHARACTER_ATTITUDE.WALKING
		--self.actualSpeed = self.walkingSpeed	
		self.startPosition = PNPoint3f:new_local(self:getCoord())
    end
--------------------------------------------------------------------------------	
	OVERRIDE(OBJ, "onUpdate")	
	function OBJ:onUpdate(deltaTime)
		--pnprint("speed: " .. self.actualSpeed .."\n")
		--pnprint("attitude: " .. self.attitude.."\n")
		
	--	self:setMovingSpeed(self.actualSpeed)
	--	self.idleTime = self.idleTime + deltaTime;
	--	if (self.idleTime >= 10000 and self:getMovingState() == 0) then
	--		self:setEnableLoop(false)
	--		self.idleTime = 0
	--	end

		self:PN3DSkeletonObject_onUpdate(deltaTime)
		self:launchGoodAnimation()
		
		self.view:prepareUpdate()
		self.view:update(deltaTime)
	end
	
--------------------------------------------------------------------------------
	function OBJ:onRun(state)
   		--print(self)
    	--pnprint("==>> "..self.className..":onRun()\n")
		--pnprint("speed: " .. self.actualSpeed .."\n")
		--pnprint("attitude: " .. self.attitude.."\n")
		if (state == ACTION_STATE.START)then
			--pnprint("start run\n")
		    self.attitude = CHARACTER_ATTITUDE.RUNNING
		    self.actualSpeed = self.runningSpeed
		else
			--pnprint("stop run\n")
		    self.attitude = CHARACTER_ATTITUDE.WALKING
		    self.actualSpeed = self.walkingSpeed
		end
		self:setMovingSpeed(self.actualSpeed)
		--self:launchGoodAnimation()
		--pnprint("speed: " .. self.actualSpeed .."\n")
		--pnprint("attitude: " .. self.attitude.."\n")
    	--pnprint("<<== "..self.className..":onRun()\n")
    end	
--------------------------------------------------------------------------------
	function OBJ:onCrouch(state)
		if (state == ACTION_STATE.START)then
			--pnprint("start crouch\n")
		    self.attitude = CHARACTER_ATTITUDE.CROUCHING
		    
		else
			--pnprint("stop Crouch\n")
		    self.attitude = CHARACTER_ATTITUDE.WALKING
		end
		self.actualSpeed = self.walkingSpeed
		self:setMovingSpeed(self.actualSpeed)
    end	
--------------------------------------------------------------------------------
    function OBJ:onJump(state)
		if (state == ACTION_STATE.START)then
		    self.attitude = CHARACTER_ATTITUDE.JUMPIMG
		    self.actualSpeed = self.walkingSpeed
		end
		--self:setMovingSpeed(self.actualSpeed)
    end	
--------------------------------------------------------------------------------
--[[%
Called on a behaviour change
Sets a new state impliying a new behaviour for the character
Adds the old state on a stack to retrieve it later
%--]]
	--OVERRIDE(OBJ, "setState")
	function OBJ:setState(st)
		--pnprint("=> PNCharacter:setState()\n")
		if (self.state ~= st) then
			--pnprint("states stack size = " .. table.getn(self.pastStates).. "\n")
			--pnprint(self.state .. " --> " .. st .. "\n")
			table.insert(self.pastStates, 0, self.state)
			self.state = st
			if (self.pastStates[0] == self.stateEnum.PN_IA_TRAVELLING) then
				self:onMoveForward(ACTION_STATE.STOP)
			end
		end
		--pnprint("<= PNCharacter:setState()\n")
	end
--------------------------------------------------------
--[[%
Called when a behaviour is not needed anymore
Sets the character's behaviour to the previous state on the stack
%--]]
	--OVERRIDE(OBJ, "restoreState")
	function OBJ:restoreState()
		--pnprint("=> PNCharacter:restoreState()\n")
		--pnprint("states stack size = " .. table.getn(self.pastStates).. "\n")
		--pnprint(self.state .. " --> " .. self.pastStates[0] .. "\n")
		self.state = self.pastStates[0]
		table.remove(self.pastStates, 0)
		if (self.state == self.stateEnum.PN_IA_TRAVELLING and self.goal ~= nil) then
			self:moveTo(self.goal)
		end
		--pnprint("<= PNCharacter:restoreState()\n")
	end
--------------------------------------------------------
--[[%
Called when an ennemy enters the frustrum
Prepares the Character to handle a fight
%--]]
	function OBJ:startFight(target)
	end
--------------------------------------------------------
--[[%
Called at the end of a Fight Action
%--]]
    function OBJ:onDamage(damage, localisation, source)
		--pnprint(self.id .. " gets " .. damage .. " at localisation " .. localisation .. " as damage\n")
		self.m_wounds[localisation] = self.m_wounds[localisation] + damage
		if (self.m_wounds[localisation] > self.health_state) then
			self.health_state = self.m_wounds[localisation]
			self.updateLife = true
		end
		if (self.health_state >= HEALTH_STATE.COMA) then
			--Anim Death
			self:setTarget(nil)
			self:setMovingState(PN3DObject.STATE_NONE)
			gameMap:sendEventFromLua(self, 17) -- DeathEvent
			self:waitForAnimEnd(CHARACTER_ANIM.DIE)
			--pnprint(self.id .. " is dead (or coma) !\n")
		elseif ((self.state ~= self.stateEnum.PN_IA_FIGHTING) or self:getViewTarget() == nil) then
			self:startFight(source)
		end
	end
--------------------------------------------------------
--[[%
Launches an Animation and waits for its end
%--]]
	function OBJ:waitForAnimEnd(anim)
		--pnprint(self.id .. ":waitForAnimEnd(" .. anim .. ")\n")
		self.waitedAnim = anim
		self:startAnimation(anim)
		self:setState(self.stateEnum.PN_IA_WAIT_ANIM_END)
	end
--------------------------------------------------------
--[[%
Checks if waited Animation is the one that ended
%--]]
	function OBJ:checkAnimEnd(anim)
		--pnprint("=> PNAICharacter:checkAnimEnd(" .. anim .. ") and waited: " .. self.waitedAnim .. "\n")
		if (self.waitedAnim == anim) then
			if (self.health_state >= HEALTH_STATE.LETHAL) then --if is dead
				self:setState(self.stateEnum.PN_IA_DEAD)
				--pnprint("Actually he really is dead\n")
			elseif (self.health_state == HEALTH_STATE.COMA) then
				self:setState(self.stateEnum.PN_IA_COMA)
				--pnprint("Actually it only is a coma\n")
			else
				self:restoreState()
				if (self.restoreAtAnimEnd == true) then
					self:restoreState()
					self.restoreAtAnimEnd = false
				end
				if (self.state == self.stateEnum.PN_IA_FIGHTING and ((self.combat_state == COMBAT_STATE.ATTACK) or (self.combat_state == COMBAT_STATE.DEFENSE))) then -- if is fighting
					self.combat_state = COMBAT_STATE.NEUTRAL
				end
			end
			self.waitedAnim = -1
		end
		--pnprint("<= PNAICharacter:checkAnimEnd\n")
	end
--------------------------------------------------------------------------------
--[[%
Lets some turns in coma then the characters gain one life level
%--]]
	function OBJ:manageComa()
		if (self.comaTurns >= 500 / self.stats.awareness) then
			self.comaTurns = 0
			for locname, locval in pairs(LOCALISATION) do
				if (locval > 0) then
					--pnprint("repairing ? at ".. locname .. " " .. locval .. " " .. self.m_wounds[locval] .. "\n")
					if (self.m_wounds[locval] >= HEALTH_STATE.COMA) then
						--pnprint("repaired !\n")
						self.m_wounds[locval] = HEALTH_STATE.CRITIC
					end
				end
			end
			gameMap:isAlive(self.id)
			self.health_state = HEALTH_STATE.CRITIC
			self.combat_state = COMBAT_STATE.NEUTRAL
			self.elapsedTurns = 0
			self:restoreState()
			if (self.state == self.stateEnum.PN_IA_FIGHTING) then
				self:restoreState()
			end
			for id, entity in pairs(self.seen_entities) do
				self:onFrustrumIn(entity)
			end
			if (self.state == self.stateEnum.PN_IA_PASSIVE) then
				self:moveTo(self.startPosition)
			end

			self.updateLife = true
			self:setEnabled(CHARACTER_ANIM.DEAD, false)
		else
			self.comaTurns = self.comaTurns + 1
		end
	end
--------------------------------------------------------------------------------
--[[%
Returns the type of the character that is visible to others
%--]]
	function OBJ:getCharacType()
		return self.shownCharacType
	end
--------------------------------------------------------------------------------
--[[%
Launch the good annimation regarding the state of the Character
%--]]
	function OBJ:launchGoodAnimation()
		if (self:getMovingState() ~= 0)then
			self.idleTime = 0
		end	

		self:setEnabled(CHARACTER_ANIM.WALK_F, self:testMovingState(PN3DObject.STATE_T_FORWARD) and (self.attitude == CHARACTER_ATTITUDE.WALKING))
		self:setEnabled(CHARACTER_ANIM.WALK_B, self:testMovingState(PN3DObject.STATE_T_BACKWARD) and (self.attitude == CHARACTER_ATTITUDE.WALKING))
		self:setEnabled(CHARACTER_ANIM.WALK_L, self:testMovingState(PN3DObject.STATE_T_LEFT) and (self.attitude == CHARACTER_ATTITUDE.WALKING))
		self:setEnabled(CHARACTER_ANIM.WALK_R, self:testMovingState(PN3DObject.STATE_T_RIGHT) and (self.attitude == CHARACTER_ATTITUDE.WALKING))
		
		self:setEnabled(CHARACTER_ANIM.RUN_F, self:testMovingState(PN3DObject.STATE_T_FORWARD) and (self.attitude == CHARACTER_ATTITUDE.RUNNING))
		self:setEnabled(CHARACTER_ANIM.RUN_B, self:testMovingState(PN3DObject.STATE_T_BACKWARD) and (self.attitude == CHARACTER_ATTITUDE.RUNNING))
		self:setEnabled(CHARACTER_ANIM.RUN_L, self:testMovingState(PN3DObject.STATE_T_LEFT) and (self.attitude == CHARACTER_ATTITUDE.RUNNING))
		self:setEnabled(CHARACTER_ANIM.RUN_R, self:testMovingState(PN3DObject.STATE_T_RIGHT) and (self.attitude == CHARACTER_ATTITUDE.RUNNING))
			
		self:setEnabled(CHARACTER_ANIM.CROUCH_F, self:testMovingState(PN3DObject.STATE_T_FORWARD) and (self.attitude == CHARACTER_ATTITUDE.CROUCHING))
		self:setEnabled(CHARACTER_ANIM.CROUCH_B, self:testMovingState(PN3DObject.STATE_T_BACKWARD) and (self.attitude == CHARACTER_ATTITUDE.CROUCHING))
		self:setEnabled(CHARACTER_ANIM.CROUCH_L, self:testMovingState(PN3DObject.STATE_T_LEFT) and (self.attitude == CHARACTER_ATTITUDE.CROUCHING))
		self:setEnabled(CHARACTER_ANIM.CROUCH_R, self:testMovingState(PN3DObject.STATE_T_RIGHT) and (self.attitude == CHARACTER_ATTITUDE.CROUCHING))
			
		self:setEnabled(CHARACTER_ANIM.CROUCH, (self:getMovingState() == 0) and (self.attitude == CHARACTER_ATTITUDE.CROUCHING))
		self:setEnabled(CHARACTER_ANIM.IDLE, (self:getMovingState() == 0) and (self.attitude ~= CHARACTER_ATTITUDE.CROUCHING) and (OBJ.state == OBJ.stateEnum.PN_IA_PASSIVE) and (self.state ~= HEALTH_STATE.COMA))
		--self:setEnabled(CHARACTER_ANIM.DEAD, (self:getMovingState() == 0) and (self.state == self.stateEnum.PN_IA_COMA or self.state == self.stateEnum.PN_IA_DEAD))
	end 
--------------------------------------------------------
--[[%
Add comment here
%--]]
	function OBJ:updateJump()
		
	end
--------------------------------------------------------
--[[%
Launches an Animation and waits for its end
%--]]
	function OBJ:getNBFightSuccess()
		-- Success Modifier
		local MDsuccess = 0
		if (self.health_state == HEALTH_STATE.SERIOUS) then
			MDsuccess = -1
		elseif (self.health_state == HEALTH_STATE.DANGEROUS) then
			MDsuccess = -2
		elseif (self.health_state == HEALTH_STATE.CRITIC) then
			MDsuccess = -4
		end

		-- Number of dice
		local nbDice = self.stats[self.selected_weapon.skill] + self.selected_weapon.modifier
		local nbS = 0
		--pnprint("competence=" .. self.stats[self.selected_weapon.skill] .. " modifier=" .. self.selected_weapon.modifier .. " nbDice=" .. nbDice .. "\n")
	
		-- Success Modifiers
		local distance = 0;
		if (self:getViewTarget() ~= nil) then
			--pnprint("distance is set\n")
			distance = self:getCoord():getDistance(self:getViewTarget():getCoord())
		end
		local range = self.selected_weapon.range
		--pnprint(self:getId() .. " -> ")
		--pnprint(self:getViewTarget():getId())
		--pnprint(" d=" .. distance .. "\n")
		if ((self.selected_weapon.type ~= firearm) and (self.selected_weapon.type ~= throw_weapon)) then
			if (distance < range) then
				-- nb success
				for i = 1, nbDice do
					--pnprint(self.id .. " throwing a die !\n")
					if ((gameMap.die:getVal(10) + MDsuccess) <= self.skills[self.selected_weapon.type]) then
						--pnprint("\tsuccess !\n")
						nbS = nbS + 1
					end
				end
			end
		end

		return nbS
	end

--------------------------------------------------------
--[[%
Select New Weapon from inventory
%--]]
	function OBJ:selectWeapon(typename)
		--print(self.selected_weapon:getId() .. " " .. typename)
		if (self.selected_weapon.type ~= "h2h_combat") then
			self.selected_weapon:setVisible(false)
		end
		self.selected_weapon = self.items.weapons[typename]		
		--print(self.selected_weapon:getId() .. " " .. typename)
		self.selected_weapon:setVisible(true)
	end			
--------------------------------------------------------
--[[%
Called at the getItem and put it on inventory
%--]]
	function OBJ:getItem(item)
		--print("function OBJ:getItem(item)")
		self.items[item:getId()] = item
		item.isHold = true
		--item:setVisible(false)
		if (item:isA("PNWeapon") and self.items.weapons[item.type] == nil)then
			item:setVisible(true)
			--print("function OBJ:getItem(item)2")
			self.items.weapons[item.type] = item
			item:setPositionTarget(self)
			item:setPositionBoneTarget("Bip01 R Finger12")
	        item:addTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
	        item:setViewTarget(self)
			item:setViewBoneTarget("Bip01 R Finger12")      
	        item:addTargetMode(PN3DObject.TMODE_ORIENTATION_ABS_LOCKED)        
			local orient = PNQuatf:new_local()
			orient:fromDegrees(90.0, 0.0, 0.0)
			item:setTargetOrientation(orient)
			item.isHold = true
			self:selectWeapon(item.type)
			return true
		else
			--item:setVisible(false)
		end 
		return true
	end
-------------------------------------------------------------------------------
--[[%
Called at the getItem and put it on inventory
%--]]
	function OBJ:giveItemTo(character, item)
		self.items[item.getId()] = nil
		character:getItem(item)
		return true
	end
----------------------------------------------------------------------------------
--[[%
Called at the Defense Action
%--]]
	function OBJ:onDefense(state)	
		print("[LUA] onDefense "..state)
	end
-------------------------------------------------------------------------------
--[[%
Called at the Use Action
%--]]
	function OBJ:onUse(state)	
	
	end
-------------------------------------------------------------------------------
	return OBJ
end