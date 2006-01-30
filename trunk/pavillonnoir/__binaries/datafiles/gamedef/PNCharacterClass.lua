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
				STRIKE_RLEG=21
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
	OBJ.items.weapons	=	{h2h=PNWeaponH2HClass("h2h")} --FIXME id de merde
	--------------------------------------
	-------LIST OF WOUNDS BY MEMBER-------
	OBJ.m_wounds=	{0,0,0,0,0,0}
	--------------------------------------
	OBJ.health_state = HEALTH_STATE.OK
	OBJ.selected_weapon = OBJ.items.weapons.h2h
	OBJ.combat_state = COMBAT_STATE.NEUTRAL
	OBJ.realCharacType = CHARACTER_TYPE.CIVILIAN
	OBJ.shownCharacType = CHARACTER_TYPE.CIVILIAN
	--------------------------------------
	OBJ.load_capacity = 10;
	--------------------------------------
	OBJ.seen_entities = {}
	--------------------------------------
	OBJ.view = PN3DCameraClass(OBJ.id .. "cam", false)
	OBJ.view:addTargetMode(OBJ.TMODE_ORIENTATION_ABS_LOCKED)
	OBJ.view:addTargetMode(OBJ.TMODE_POSITION_ABS_LOCKED)
	OBJ.view:setTarget(OBJ);
	OBJ.view:setTargetPosition(0.0, 40.0, 0.0);
	
-------------------------------------------------------------------------------
	-----------------------------------------------------------
	--------------- Rotation parameter ------------------------
	OBJ.yawSpeed = 1.0
	OBJ.pitchSpeed = 1.0
	OBJ.defaulRotateSpeed = 1.0
	----------------------------------------------------------
	--------------- Translations parameter -------------------	
	OBJ.walkingSpeed = 0.1
	OBJ.runningSpeed = 0.4
	
	OBJ.attitude=CHARACTER_ATTITUDE.WALKING
	OBJ.dirLong= CHARACTER_DIR_LONG.NONE -- longitudinal direction
	OBJ.dirLate= CHARACTER_DIR_LATE.NONE	-- latteral direction
	OBJ.actualSpeed = OBJ.walkingSpeed
	-----------------------------------------------------------
	------------------- Jump Parameter ------------------------
	OBJ.JumpHeight= 0;
	--------------- Animation parameters ---------------------- 
	OBJ:setAnimSpeed(4.0)
	OBJ.idleTime = 0
	OBJ.waitedAnim = 0
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
    	--pnprint("==>> PNCharacter:onMoveForward()\n")
		--pnprint("speed: " .. self.actualSpeed .."\n")
		--pnprint("attitude: " .. self.attitude.."\n")
		--pnprint(self.id .. ":onMoveForward=" .. state .. "\n")
		--OBJ:setMovingSpeed(self.actualSpeed)
		self:PN3DSkeletonObject_onMoveForward(state)	
		if (state == ACTION_STATE.START) then
			self.dirLong = self.dirLong + CHARACTER_DIR_LONG.FORWARD
		else
			self.dirLong = CHARACTER_DIR_LONG.NONE
		end 
		self:launchGoodAnimation()
		--pnprint("speed: " .. self.actualSpeed .."\n")
		--pnprint("attitude: " .. self.attitude.."\n")
		--pnprint("<<== PNCharacter:onMoveForward()\n")
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to go backward and start apropriate annimation 
@param state boolean
	true -> start , false -> stop  
%--]]		
	OVERRIDE(OBJ, "onMoveBackward")	
	function OBJ:onMoveBackward(state)
		pnprint(self.id)
		pnprint(":onMoveBackward\n")
		self:PN3DSkeletonObject_onMoveBackward(state)
		--OBJ:setMovingSpeed(self.actualSpeed)	
		if (state == ACTION_STATE.START) then
			self.dirLong = self.dirLong + CHARACTER_DIR_LONG.BACKWARD
		else
			self.dirLong = CHARACTER_DIR_LONG.NONE
		end 
		self:launchGoodAnimation()
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to go Left
@param state boolean
	true -> start , false -> stop  
%--]]	
	OVERRIDE(OBJ, "onMoveLeft")	
	function OBJ:onMoveLeft(state)
		pnprint(self.id .. ":onMoveForLeft=" .. state .. "\n")
		--OBJ:setMovingSpeed(self.actualSpeed)
		self:PN3DSkeletonObject_onMoveLeft(state)	
		if (state == ACTION_STATE.START) then
			self.dirLate = self.dirLate + CHARACTER_DIR_LATE.LEFT
		else
			self.dirLate = CHARACTER_DIR_LATE.NONE
		end 
		self:launchGoodAnimation()
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to left and start apropriate animation 
@param state boolean
	true -> start , false -> stop  
%--]]		
	OVERRIDE(OBJ, "onMoveRight")	
	function OBJ:onMoveRight(state)
		pnprint(self.id)
		pnprint(self.id .. ":onMoveForRight=" .. state .. "\n")
		self:PN3DSkeletonObject_onMoveRight(state)
		--OBJ:setMovingSpeed(self.actualSpeed)	
		if (state == ACTION_STATE.START) then
			self.dirLate = self.dirLate + CHARACTER_DIR_LATE.RIGHT
		else
			self.dirLate = CHARACTER_DIR_LATE.NONE
		end 
		self:launchGoodAnimation()
	end
-------------------------------------------------------------------------------

--[[%
Call when someone tell the object to rotate right
@param state boolean
	true -> start , false -> stop  
%--]]	
	OVERRIDE(OBJ, "onRotateRight")	
	function OBJ:onRotateRight(state)
		pnprint(self.id)
		pnprint(":onRotateRight\n")
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
		pnprint(self.id)
		pnprint(":onRotateLeft\n")
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
		pnprint(self.id)
		pnprint(":onRotateUp\n")
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
		pnprint(self.id)
		pnprint(":onRotateDown\n")
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
		pnprint(self.id)
		pnprint(":MouseLook\n")
	end

-------------------------------------------------------------------------------
--[[%
Call when an entity entrer in character sight
Add the entity in the seen_entities list
@param 3DObject
	the Entity entering in sight 
%--]]	
	function OBJ:onFrustrumIn(target)
		if (target:getId() ~= self.id) then
          OBJ.seen_entities[target.id] = target
		end
	end
-------------------------------------------------------------------------------
	function OBJ:onFrustrumOut(target)
		if (target:getId() ~= self.id) then
          OBJ.seen_entities[target.id] = nil
		end
	end
-------------------------------------------------------------------------------
    function OBJ:onAttack(sourceId, targetId)
		
    end
--------------------------------------------------------------------------------
    OVERRIDE(OBJ, "onInit")	
	function OBJ:onInit()
    	pnprint("onInit()\n")
    	self:PN3DSkeletonObject_onInit()
    	--self.JumpHeight= (self:getMax().y - self:getMin().y ) /3
		--self.attitude = CHARACTER_ATTITUDE.WALKING
		--self.actualSpeed = self.walkingSpeed	
    end
--------------------------------------------------------------------------------	
	OVERRIDE(OBJ, "onUpdate")	
	function OBJ:onUpdate(deltaTime)
		--pnprint("speed: " .. self.actualSpeed .."\n")
		--pnprint("attitude: " .. self.attitude.."\n")
		self.view:update(deltaTime)
		self:setMovingSpeed(self.actualSpeed)
		self.idleTime = self.idleTime + deltaTime;
		if (self.idleTime >= 10000 and self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.NONE) then
			self:setEnableLoop(false)
			--self:startAnimation(CHARACTER_ANIM.IDLE)
			self.idleTime = 0
		end
		self:PN3DSkeletonObject_onUpdate(deltaTime)
	end
	
--------------------------------------------------------------------------------
	function OBJ:onRun(state)
   		print(self)
    	pnprint("==>> "..self.className..":onRun()\n")
		pnprint("speed: " .. self.actualSpeed .."\n")
		pnprint("attitude: " .. self.attitude.."\n")
		if (state == ACTION_STATE.START)then
			pnprint("start run\n")
		    self.attitude = CHARACTER_ATTITUDE.RUNNING
		    self.actualSpeed = self.runningSpeed
		else
			pnprint("stop run\n")
		    self.attitude = CHARACTER_ATTITUDE.WALKING
		    self.actualSpeed = self.walkingSpeed
		end
		--self:setMovingSpeed(self.actualSpeed)
		self:launchGoodAnimation()
		pnprint("speed: " .. self.actualSpeed .."\n")
		pnprint("attitude: " .. self.attitude.."\n")
    	pnprint("<<== "..self.className..":onRun()\n")
    end	
--------------------------------------------------------------------------------
	function OBJ:onCrouch(state)
		if (state == ACTION_STATE.START)then
			pnprint("start crouch\n")
		    self.attitude = CHARACTER_ATTITUDE.CROUCHING
		    
		else
			pnprint("stop Crouch\n")
		    self.attitude = CHARACTER_ATTITUDE.WALKING
		end
		self.actualSpeed = self.walkingSpeed
		--self:setMovingSpeed(self.actualSpeed)
		self:launchGoodAnimation()
    end	
--------------------------------------------------------------------------------
    function OBJ:onJump(state)
		if (state == ACTION_STATE.START)then
		    self.attitude = CHARACTER_ATTITUDE.JUMPIMG
		    self.actualSpeed = self.walkingSpeed
		end
		--self:setMovingSpeed(self.actualSpeed)
		self:launchGoodAnimation()
    end	
--------------------------------------------------------------------------------
--[[%
Overriden in PNAICharacterClass
%--]]
    function OBJ:onDamage(damage, localisation)
	end
--------------------------------------------------------------------------------
--[[%
Returns the type of the character that is visible to others
%--]]
	function OBJ:getCharacType()
		return self.shownCharacType
	end
--------------------------------------------------------------------------------
	function OBJ:launchGoodAnimation()
		--[[
		self:setEnableLoop(true)
		if (self.attitude == CHARACTER_ATTITUDE.WALKING) then
			--pnprint ("walk\n")
			if (self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.NONE)then
				self:startAnimation(CHARACTER_ANIM.IDLE, 0)
				self.idleTime = 0
				print("toto")
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.WALK_L, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.RIGHT) then
				self:startAnimation(CHARACTER_ANIM.WALK_R, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.NONE) then
				self:startAnimation(CHARACTER_ANIM.WALK_F, 0)
				return	
			elseif (self.dirLong == CHARACTER_DIR_LONG.BACKWARD and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.WALK_L, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.BACKWARD and self.dirLate == CHARACTER_DIR_LATE.RIGHT) then
				self:startAnimation(CHARACTER_ANIM.WALK_R, 0)
				return	
			elseif (self.dirLong == CHARACTER_DIR_LONG.BACKWARD and self.dirLate == CHARACTER_DIR_LATE.NONE) then
				self:startAnimation(CHARACTER_ANIM.WALK_B, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.RIGHT) then
				self:startAnimation(CHARACTER_ANIM.WALK_R, 0)
				return	
			elseif (self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.WALK_L, 0)
				return		
			end 
		elseif (self.attitude == CHARACTER_ATTITUDE.RUNNING) then
		    pnprint ("Run\n")
			if 	   (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.RUN_L, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.RIGHT) then
				self:startAnimation(CHARACTER_ANIM.RUN_R, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.NONE) then
				self:startAnimation(CHARACTER_ANIM.RUN_F, 0)
				return	
			elseif (self.dirLong == CHARACTER_DIR_LONG.BACKWARD and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.RUN_L, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.BACKWARD and self.dirLate == CHARACTER_DIR_LATE.RIGHT) then
				self:startAnimation(CHARACTER_ANIM.RUN_R, 0)
				return	
			elseif (self.dirLong == CHARACTER_DIR_LONG.BACKWARD and self.dirLate == CHARACTER_DIR_LATE.NONE) then
				self:startAnimation(CHARACTER_ANIM.RUN_B, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.RIGHT) then
				self:startAnimation(CHARACTER_ANIM.RUN_R, 0)
				return	
			elseif (self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.RUN_L, 0)
				return		
			end 		
		elseif (self.attitude == CHARACTER_ATTITUDE.CROUCHING) then
		    pnprint ("Crouch\n")
			if 	   (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.CROUCH_L, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.RIGHT) then
				self:startAnimation(CHARACTER_ANIM.CROUCH_R, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.NONE) then
				self:startAnimation(CHARACTER_ANIM.CROUCH_F, 0)
				return	
			elseif (self.dirLong == CHARACTER_DIR_LONG.BACKWARD and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.CROUCH_L, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.BACKWARD and self.dirLate == CHARACTER_DIR_LATE.RIGHT) then
				self:startAnimation(CHARACTER_ANIM.CROUCH_R, 0)
				return	
			elseif (self.dirLong == CHARACTER_DIR_LONG.BACKWARD and self.dirLate == CHARACTER_DIR_LATE.NONE) then
				self:startAnimation(CHARACTER_ANIM.CROUCH_B, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.RIGHT) then
				self:startAnimation(CHARACTER_ANIM.CROUCH_R, 0)
				return	
			elseif (self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.CROUCH_L, 0)
				return
			elseif (self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.NONE) then
				self:startAnimation(CHARACTER_ANIM.CROUCH, 0)
				return		
			end 						
		elseif (self.attitude == CHARACTER_ATTITUDE.JUMPING) then
			if 	   (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.JUMP, 0)
				return		
			end 		
		end

--]]end
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
			pnprint("distance is set\n")
			distance = self:getCoord():getDistance(self:getViewTarget():getCoord())
		end
		local range = self.selected_weapon.range
		pnprint(self:getId() .. " -> ")
		--pnprint(self:getViewTarget():getId())
		pnprint(" d=" .. distance .. "\n")
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
Launches an Animation and waits for its end
%--]]
	function OBJ:waitForAnimEnd(anim)
	end
--------------------------------------------------------
--[[%
Checks if waited Animation is the one that ended
%--]]
	function OBJ:checkAnimEnd(anim)
	end
--------------------------------------------------------
	return OBJ
end