function PlayerClass(id)
	-- make inheritance -----
	local Player = inheritFrom(PN3DSkeletonObjectClass(id))
	Player.className = "Player"
	-------------------------
	---------------setting camera behavior-----------------
	Player.camera = PN3DCamera:getRenderCam()
	Player.camera:setTarget(Player)
   Player.camera:setTargetPosition(0, 300 , 300)
	--Player.camera:setTargetDistance(300)
   Player.camera:setMovingMode(PN3DObject.MMODE_POSITION_ABS_LOCKED)
   --Player.camera:setMovingMode(PN3DObject.MMODE_VIEW_ABS_LOCKED)
    
	-------------------------------------------------------
		
	Player.walkingSpeed = 0.5
	Player.runningSpeed = 1.0
	
	Player.isRunning = false
	Player.actualSpeed = 0;
	Player.actualMovingState = 0;
	
	Player:setAnimSpeed(4.0);
	Player:setEnableLoop(true);
	---------------------move events-----------------------
	function Player:onLuaActionMoveForward(state)
		pnprint(self.id)
		pnprint(":onLuaActionMoveForward\n")
		self.__index:onLuaActionMoveForward(state)	
		if (state == true) then
			self:startAnimation(0, 0)
		else
			self:stopAnimation()
		end 
		
	end
	
	function Player:onLuaActionMoveBackward(state)
		pnprint(self.id)
		pnprint(":onLuaActionMoveBackward\n")
		self.__index:onLuaActionMoveBackward(state)	
		if (state == true) then
			self:startAnimation(0, 0)
		else
			self:stopAnimation()
		end 
	end

	function Player:onLuaUpdate(deltaTime)
		pnprint(self.id)
		pnprint(":onLuaActionMoveBackward\n")
		self.__index:onLuaUpdate(deltaTime)
	end
	
	-------------------------------------------------------
	return Player
end