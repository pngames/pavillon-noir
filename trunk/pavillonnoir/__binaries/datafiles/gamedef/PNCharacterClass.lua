
COMBAT_STATE={NEUTRAL=0,
			 ATTACK=1,
			 DEFENCE=2,
			 DODGE=3
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
				STRIKE_1=16
				}
								
CHARACTER_ATTITUDE={
					WALKING=0,
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
function PNCharacterClass(id)
	----------inheritance-----------------
	local OBJ = inheritFrom({className = "PNCharacter"}, PN3DSkeletonObjectClass(id))
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
	OBJ.m_wounds=	{head=0,
							 torso=0,
							 r_arm=0,
							 l_arm=0,
							 r_leg=0,
							 l_leg=0
							}
	--------------------------------------
	OBJ.health_state = 0
	OBJ.selected_weapon = OBJ.items.weapons.h2h
	OBJ.combat_state = COMBAT_STATE.NEUTRAL
	OBJ.realCharacType = CHARACTER_TYPE.CIVILIAN
	OBJ.shownCharacType = CHARACTER_TYPE.CIVILIAN
	--------------------------------------
	OBJ.load_capacity = 10;
	--------------------------------------
	OBJ.seen_entities = {}
	--------------------------------------
	OBJ.view = PN3DCameraClass(OBJ.id .. "cam", OBJ, false)
	OBJ.view:addTargetMode(OBJ.TMODE_ORIENTATION_ABS_LOCKED)
	OBJ.view:addTargetMode(OBJ.TMODE_POSITION_ABS_LOCKED)
	OBJ.view:setTarget(OBJ);
	OBJ.view:setTargetPosition(0.0, 100.0, 0.0);
	
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
	
	OBJ.attitude=CHARACTER_ATTITUDE.WALKING;
	OBJ.dirLong= CHARACTER_DIR_LONG.NONE; -- longitudinal direction
	OBJ.dirLate=CHARACTER_ATTITUDE.WALKING;	-- latteral direction
	OBJ.actualSpeed = OBJ.walkingSpeed;
	-----------------------------------------------------------
	--------------- Animation parameters ---------------------- 
	OBJ:setAnimSpeed(4.0)
	OBJ.idleTime = 0
-------------------------------------------------------------------------------
---------------------move order callback-----------------------
--[[%
Call when someone tell the object to go backward
@param state boolean
	true -> start , false -> stop  
%--]]	
	function OBJ:onMoveForward(state)
		pnprint(self.id .. ":onMoveForward=" .. state .. "\n")
		OBJ:setMovingSpeed(self.actualSpeed)
		self.__index:onMoveForward(state)	
		if (state == ACTION_STATE.START) then
			self.dirLong = CHARACTER_DIR_LONG.FORWARD
		else
			self.dirLong = CHARACTER_DIR_LONG.NONE
		end 
		self:launchGoodAnimation()
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to go backward and start apropriate annimation 
@param state boolean
	true -> start , false -> stop  
%--]]		
	function OBJ:onMoveBackward(state)
		pnprint(self.id)
		pnprint(":onMoveBackward\n")
		self.__index:onMoveBackward(state)
		OBJ:setMovingSpeed(self.actualSpeed)	
		if (state == ACTION_STATE.START) then
			self.dirLong = CHARACTER_DIR_LONG.BACKWARD
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
	function OBJ:onMoveLeft(state)
		pnprint(self.id .. ":onMoveForLeft=" .. state .. "\n")
		OBJ:setMovingSpeed(self.actualSpeed)
		self.__index:onMoveLeft(state)	
		if (state == ACTION_STATE.START) then
			self.dirLate = CHARACTER_DIR_LATE.LEFT
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
	function OBJ:onMoveRight(state)
		pnprint(self.id)
		pnprint(self.id .. ":onMoveForRight=" .. state .. "\n")
		self.__index:onMoveRight(state)
		OBJ:setMovingSpeed(self.actualSpeed)	
		if (state == ACTION_STATE.START) then
			self.dirLate = CHARACTER_DIR_LATE.RIGHT
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
	function OBJ:onRotateRight(state)
		pnprint(self.id)
		pnprint(":onRotateRight\n")
		self.__index:onRotateRight(state)		
	end	
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to rotate left
@param state boolean
	true -> start , false -> stop  
%--]]		
	function OBJ:onRotateLeft(state)
		pnprint(self.id)
		pnprint(":onRotateLeft\n")
		self.__index:onRotateLeft(state)	
		self.yawSpeed = self.defaultRotateSpeed;
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to rotate up
@param state boolean
	true -> start , false -> stop  
%--]]	
	function OBJ:onRotateUp(state)
		pnprint(self.id)
		pnprint(":onRotateUp\n")
		self.pitchSpeed = self.defaultRotateSpeed;
		self.__index:onRotateUp(state)		
	end
-------------------------------------------------------------------------------
--[[%
Call when someone tell the object to rotate down
@param state boolean
	true -> start , false -> stop  
%--]]	
	function OBJ:onRotateDown(state)
		pnprint(self.id)
		pnprint(":onRotateDown\n")
		self.pitchSpeed = self.defaultRotateSpeed
		self.__index:onRotateDown(state)	
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
	function OBJ:onUpdate(deltaTime)
		self.view:update(deltaTime)
		self.__index:update(deltaTime)
		self.idleTime = self.idleTime + deltaTime;
		if (self.idleTime >= 10000 and self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.NONE)then
			self:setEnableLoop(false)
			self:startAnimation(CHARACTER_ANIM.IDLE, 0)
			self.idleTime = 0
		end
	end
	
--------------------------------------------------------------------------------
    function OBJ:onRun(state)
		if (state == ACTION_STATE.START)then
		    self.attitude = CHARACTER_ATTITUDE.RUNNING
		    self.actualSpeed = self.runningSpeed
		else
		    self.attitude = CHARACTER_ATTITUDE.WALKING
		    self.actualSpeed = self.walkingSpeed
		end
		self:setMovingSpeed(self.actualSpeed)
		self:launchGoodAnimation()
    end	
--------------------------------------------------------------------------------
    function OBJ:onCrouch(state)
		if (state == ACTION_STATE.START)then
		    self.attitude = CHARACTER_ATTITUDE.CROUCHING
		    self.actualSpeed = self.walkingSpeed
		else
		    self.attitude = CHARACTER_ATTITUDE.WALKING
		    self.actualSpeed = self.walkingSpeed
		end
		self:setMovingSpeed(self.actualSpeed)
		self:launchGoodAnimation()
    end	
--------------------------------------------------------------------------------
	function OBJ:getCharacType()
		return self.shownCharactType
	end
--------------------------------------------------------------------------------
	function OBJ:launchGoodAnimation()
		self:setEnableLoop(true)
		if (self.dirLong == CHARACTER_DIR_LONG.NONE and self.dirLate == CHARACTER_DIR_LATE.NONE)then
			self:stopAnimation()
			self.idleTime = 0
			return
		elseif (self.attitude == CHARACTER_ATTITUDE.WALKING) then
			if 	   (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
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
				pnprint ("walk left\n")
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
			end 						
		elseif (self.attitude == CHARACTER_ATTITUDE.JUMPING) then
			if 	   (self.dirLong == CHARACTER_DIR_LONG.FORWARD and self.dirLate == CHARACTER_DIR_LATE.LEFT) then
				self:startAnimation(CHARACTER_ANIM.JUMP, 0)
				return		
			end 		
		end
	end
	
	return OBJ
end