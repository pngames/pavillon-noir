function PlayerClass(id)
	-- make inheritance -----
	local Player = inheritFrom(PN3DSkeletonObjectClass(id))
	Player.className = "Player"
	-------------------------
	---------------setting camera behavior-----------------
	Player.camera = renderCam
	Player.camera:setTarget(Player)
    Player.camera:setTargetPosition(0, 600 , 600)
    Player.camera:setMovingMode(PN3DObject.MMODE_POSITION_ABS_LOCKED)
	-----------------------------------------------------------
	--------------- Rotation parameter ------------------------
	Player.yawSpeed = 0.0
	Player.pitchSpeed = 0.0
	Player.defaulRotateSpeed = 1.0
	----------------------------------------------------------
	--------------- Translations parameter -------------------	
	Player.walkingSpeed = 1.0
	Player.runningSpeed = 4.0
	
	Player.isRunning = false
	Player.actualSpeed = Player.walkingSpeed;
	-----------------------------------------------------------
	--------------- Animation parameters ---------------------- 
	Player:setAnimSpeed(4.0)
	Player:setEnableLoop(true)
	-----------------------------------------------------------
	---------------------move events-----------------------
	function Player:onActionMoveForward(state)
		pnprint(self.id)
		pnprint(":onActionMoveForward\n")
		self.__index:onActionMoveForward(state)
		Player:setMovingSpeed(self.actualSpeed)	
		if (state == true) then
			self:startAnimation(0, 0)
		else
			self:stopAnimation()
		end 
		
	end
	
	function Player:onActionMoveBackward(state)
		pnprint(self.id)
		pnprint(":onActionMoveBackward\n")
		self.__index:onActionMoveBackward(state)
		Player:setMovingSpeed(self.actualSpeed)	
		if (state == true) then
			self:startAnimation(0, 0)
		else
			self:stopAnimation()
		end 
	end

------------------------- ROTATE --------------------
	function Player:onActionRotateRight(state)
		pnprint(self.id)
		pnprint(":onActionRotateRight\n")
		self.__index:onActionRotateRight(state);		
	end	
	
	function Player:onActionRotateLeft(state)
		pnprint(self.id)
		pnprint(":onActionRotateLeft\n")
		self.__index:onActionRotateLeft(state);	
		self.yawSpeed = self.defaultRotateSpeed;
	end

	function Player:onActionRotateUp(state)
		pnprint(self.id)
		pnprint(":onActionRotateUp\n")
		self.pitchSpeed = self.defaultRotateSpeed;
		self.__index:onActionRotateUp(state);		
	end
	
	function Player:onActionRotateDown(state)
		pnprint(self.id)
		pnprint(":onActionRotateDown\n")
		self.pitchSpeed = self.defaultRotateSpeed;
		self.__index:onActionRotateDown(state);	
	end
	
	function Player:onMouseLook(xdelta, ydelta)
		pnprint(self.id)
		pnprint(":onActionMouseLook\n")
		self.yawSpeed = self.yawSpeed * xdelta
		self.pitchSpeed = self.pitchSpeed * ydelta
		self.__index:onActionRotateUp(true);
		self.__index:onActionRotateRight(true);
	end
	
	
----------------------------------------------------------		
	function Player:onUpdate(deltaTime)
		self:setRotatingYawSpeed(self.yawSpeed)
	    self:setRotatingPitchSpeed(self.pitchSpeed)
		self.yawSpeed = 0.0
		self.pitchSpeed = 0.0
		self.__index:onUpdate(deltaTime)
	end
----------------------------------------------------------
	function Player:onDestroy()
		nothing = 0
		self.camera:setMovingMode(PN3DObject.MMODE_FREE)
		self.camera:setTarget(tolua.cast(nothing, "PN3DObject"))
	end
	-------------------------------------------------------
	return Player
end