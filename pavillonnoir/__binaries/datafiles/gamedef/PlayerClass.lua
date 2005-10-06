function PlayerClass(id)
	local Player = PN3DSkeletonObjectClass(id)
	Player.__index = Player
	Player.className = "Player"
	---------------setting camera behavior-----------------
	Player.camera = PN3DCamera:getRenderCam()
	Player.camera:setTarget(Player)
	--Dragon.
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
	
	
	    ---------------------move events-----------------------
	--function Player:onLuaActionMoveForward(state)
		--pnprint(self.id)
		--pnprint(":onLuaActionMoveForward\n")	
		--if (state == true) then
--			self:startAnimation(0, 0)
--		else
--			self:stopAnimation()
--		end 
--		self.__index:onLuaActionMoveForward(state)
--	end	

	
	-------------------------------------------------------
	return Player
end