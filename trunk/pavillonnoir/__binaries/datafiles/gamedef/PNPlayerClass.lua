function PNPlayerClass(id)
	-- make inheritance -----
	local PNPlayer = inheritFrom({className = "PNPlayer"}, PNCharacterClass(id))
	-------------------------
	---------------setting camera behavior-----------------
	PNRenderCam:setPositionTarget(PNPlayer)
	PNRenderCam:setViewTarget(PNPlayer)
   PNRenderCam:setTargetPosition(0, 300 , 1000)
   PNRenderCam:addTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
   PNRenderCam:addTargetMode(PN3DObject.TMODE_ORIENTATION_ABS_LOCKED)
   --PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_ABS_LOCKED)
	-----------------------------------------------------------
	--------------- Rotation parameter ------------------------
	PNPlayer.yawSpeed = 1.0
	PNPlayer.pitchSpeed = 1.0
	PNPlayer.defaulRotateSpeed = 1.0
	----------------------------------------------------------
	--------------- Translations parameter -------------------	
	PNPlayer.walkingSpeed = 1.0
	PNPlayer.runningSpeed = 4.0
	
	PNPlayer.isRunning = false
	PNPlayer.actualSpeed = PNPlayer.walkingSpeed;
	-----------------------------------------------------------
	--------------- Animation parameters ---------------------- 
	PNPlayer:setAnimSpeed(4.0)
	PNPlayer:setEnableLoop(true)
	-----------------------------------------------------------
	---------------------move order callback-----------------------
	function PNPlayer:onMoveForward(state)
		pnprint(self.id)
		pnprint(":onMoveForward\n")
		self.__index:onMoveForward(state)
		PNPlayer:setMovingSpeed(self.actualSpeed)	
		if (state == true) then
			self:startAnimation(0, 0)
		else
			self:stopAnimation()
		end 
		
	end
	
	function PNPlayer:onMoveBackward(state)
		pnprint(self.id)
		pnprint(":onMoveBackward\n")
		self.__index:onMoveBackward(state)
		PNPlayer:setMovingSpeed(self.actualSpeed)	
		if (state == true) then
			self:startAnimation(0, 0)
		else
			self:stopAnimation()
		end 
	end

------------------------- ROTATE --------------------
	function PNPlayer:onRotateRight(state)
		pnprint(self.id)
		pnprint(":onRotateRight\n")
		self.__index:onRotateRight(state)		
	end	
	
	function PNPlayer:onRotateLeft(state)
		pnprint(self.id)
		pnprint(":onRotateLeft\n")
		self.__index:onRotateLeft(state)	
		self.yawSpeed = self.defaultRotateSpeed;
	end

	function PNPlayer:onRotateUp(state)
		pnprint(self.id)
		pnprint(":onRotateUp\n")
		self.pitchSpeed = self.defaultRotateSpeed;
		self.__index:onRotateUp(state)		
	end
	
	function PNPlayer:onRotateDown(state)
		pnprint(self.id)
		pnprint(":onRotateDown\n")
		self.pitchSpeed = self.defaultRotateSpeed
		self.__index:onRotateDown(state)	
	end
	
	function PNPlayer:MouseLook(xdelta, ydelta)
		pnprint(self.id)
		pnprint(":MouseLook\n")
	end
	
----------------------------------------------------------		
	function PNPlayer:onUpdate(deltaTime)
		--if (isInstanceOf(self, "PN3DObject"))then
		--	pnprint("IAM PN3Dobject")
		--end
		self.__index:onUpdate(deltaTime)
	end
----------------------------------------------------------
----------------------------------------------------------		
	function PNPlayer:onInit()
        self.__index:onUpdate(deltaTime)
		pnprint(self.id .. ":onInit()\n")
	    ---------------setting camera behavior-----------------
	   -- self.view = PNRenderCam
	   -- self.view:setPositionTarget(PNPlayer)
	   -- self.view:setViewTarget(PNPlayer)
       -- self.view:setTargetPosition(0, 600 , 1000)
       -- self.view:addTargetMode(PN3DObject.TMODE_VIEW_DISTANCE_LOCKED)
		--------------------------------------------------------
	end
----------------------------------------------------------
	function PNPlayer:onDestroy()
		nothing = 0
		--self.view:setMovingMode(PN3DObject.MMODE_FREE)
		PNRenderCam:setTarget(tolua.cast(nothing, "PN3DObject"))
		--PNRenderCam:addTargetMode(PN3DObject.TMODE_VIEW_DISTANCE_ABS_LOCKED)
	end
	-------------------------------------------------------
	return PNPlayer
end