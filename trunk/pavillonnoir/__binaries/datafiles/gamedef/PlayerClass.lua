function PlayerClass(id)
	-- make inheritance -----
	local Player = inheritFrom(PN3DSkeletonObjectClass(id))
	Player.className = "Player"
	-------------------------
	---------------setting camera behavior-----------------
	Player.camera = PN3DCamera:getRenderCam()
	Player.camera:setTarget(Player)
    Player.camera:setTargetPosition(0, 600 , 600)
	--Player.camera:setTargetDistance(300)
    Player.camera:setMovingMode(PN3DObject.MMODE_POSITION_ABS_LOCKED)
    --Player.camera:addMovingMode(PN3DObject.MMODE_VIEW_ABS_LOCKED)
    --Player.camera:setMovingMode(PN3DObject.MMODE_VIEW_ABS_LOCKED)
    
	-------------------------------------------------------
		
	Player.walkingSpeed = 1.0
	Player.runningSpeed = 4.0
	
	Player.isRunning = false
	Player.actualSpeed = Player.walkingSpeed;
	
	Player:setAnimSpeed(4.0);
	Player:setEnableLoop(true);
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

	function Player:onActionRotateYaw(state)
		pnprint(self.id)
		pnprint(":onActionMoveBackward\n")	
		if (state == true) then
			self:startAnimation(0, 0)
		else
			self:stopAnimation()
		end 
	end

	function Player:onActionRotatePitch(state)
		pnprint(self.id)
		pnprint(":onActionMoveBackward\n")
		self.__index:onActionMoveBackward(state)	
		if (state == true) then
			self:startAnimation(0, 0)
		else
			self:stopAnimation()
		end 
	end
	
	function Player:onActionMouseLook(xdelta, ydelta)
		
	end
		
	function Player:onUpdate(deltaTime)
		self.__index:onUpdate(deltaTime)
	end
	
	function Player:onDestroy()
		nothing = 0
		self.camera:setMovingMode(PN3DObject.MMODE_FREE)
		self.camera:setTarget(tolua.cast(nothing, "PN3DObject"))
	end
	-------------------------------------------------------
	return Player
end