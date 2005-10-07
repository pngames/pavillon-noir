function PlayerClass(id)
	-- make inheritance -----
	local Player = {__index = PN3DSkeletonObjectClass(id)}
	setmetatable(Player, Player)
	tolua.inherit(Player , Player.__insatnce) -- make Player be recognize as PN3DSkeletonObject    
	Player.className = "Player"
	-------------------------
	---------------setting camera behavior-----------------
	Player.camera = PN3DCamera:getRenderCam()
	Player.camera:setTarget(Player)
	Player.camera:setTargetDirection(Player:getFrontDirection())
	Player.camera:setTargetDistance(10)
    --Player.camera:setMovingMode(PN3DObject.MMODE_DISTANCE_ABS_LOCKED)
    Player.camera:setMovingMode(PN3DObject.MMODE_VIEW_ABS_LOCKED)
    
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

	
	-------------------------------------------------------
	return Player
end