
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
	OBJ.items.weapons	=	{h2h=0}
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
	OBJ.walkingSpeed = 1.0
	OBJ.runningSpeed = 4.0
	
	OBJ.isRunning = false
	OBJ.actualSpeed = OBJ.walkingSpeed;
	-----------------------------------------------------------
	--------------- Animation parameters ---------------------- 
	OBJ:setAnimSpeed(4.0)
	OBJ:setEnableLoop(true)
-------------------------------------------------------------------------------
---------------------move order callback-----------------------
--[[%
Call when someone tell the object to go backward
@param state boolean
	true -> start , false -> stop  
%--]]	
	function OBJ:onMoveForward(state)
		pnprint(self.id)
		pnprint(":onMoveForward\n")
		self.__index:onMoveForward(state)
		OBJ:setMovingSpeed(self.actualSpeed)	
		if (state == true) then
			self:startAnimation(0, 0)
		else
			self:stopAnimation()
		end 
		
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
		if (state == true) then
			self:startAnimation(0, 0)
		else
			self:stopAnimation()
		end 
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
	function OBJ:onFrustrumIn(target)
		if (target:getId() ~= self.id) then
          OBJ.seen_entities[target.id] = gameMap.entities.all[targetId]
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
	end

	function OBJ:getCharacType()
		return self.shownCharactType
	end

	
	return OBJ
end