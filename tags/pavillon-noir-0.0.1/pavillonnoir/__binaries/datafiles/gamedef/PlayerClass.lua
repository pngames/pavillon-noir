function PlayerClass()
	Player = PN3DSkeletonObjectClass()
	Player.__index = Player
	Player.className = "Player"
	---------------setting camera behavior-----------------
	Player.camera = PN3DCamera:getRenderCam()
	Player.camera:setTarget(Player)
	Player.camera:setTargetDirection(Player:getFrontDirection())
    Player.camera:setMovingMode(PN3DObject.MMODE_VIEW_ABS_LOCKED)
	-------------------------------------------------------
	
	Player.walkingSpeed = 0.5
	Player.runningSpeed = 1.0
	
	Player.isRunning = false
	Player.actualSpeed = 0;
	Player.actualMovingState = 0;
	
end