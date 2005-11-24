	--pnprint("PNRenderCam creating\n")
	
	-- make inheritance -----
    PNRenderCam  = PN3DCameraClass("PNRenderCam", true)
----------------------------------------------------------
    PNRenderCam:setId("PNRenderCam")
    PNRenderCam.id = "PNRenderCam"

	PNRenderCam.yawSpeed = 0.0
    PNRenderCam.pitchSpeed = 0.0
    PNRenderCam.RollSpeed = 0.0
    PNRenderCam.lastYdelta = 0.0
    PNRenderCam.lastXdelta = 0.0
    PNRenderCam.smoothLevel = 5
    PNRenderCam.lastXMouseValues = {}
    table.insert(PNRenderCam.lastXMouseValues, 1,0)
    PNRenderCam.lastYMouseValues = {}
    table.insert(PNRenderCam.lastYMouseValues, 1,0)
------------------------------ MOVE -----------------------
	function PNRenderCam:onMoveForward(state)
		-- pnprint("LUA PNRenderCam:onMoveForward()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function PNRenderCam:onMoveBackward(state)
		-- pnprint("LUA PNRenderCam:onMoveBackward()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function PNRenderCam:onMoveLeft(state)
		-- pnprint("LUA PNRenderCam:onMoveLeft()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function PNRenderCam:onMoveRight(state)
		-- pnprint("LUA PNRenderCam:onMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end
------------------------- ROTATE -----------------------------
	function PNRenderCam:onRotateRight(state)
		-- pnprint("LUA PNRenderCam:onRotateRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_R_RIGHT)
		end 
	end
	
	function PNRenderCam:onRotateLeft(state)
		-- pnprint("LUA PNRenderCam:onRotateLeft()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_R_LEFT)
		end 
	end
	
	function PNRenderCam:onRotateUp(state)
		-- pnprint("LUA PNRenderCam:onRotateUp()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_TOP)
		else
			self:subMovingState(PN3DObject.STATE_R_TOP)
		end 
	end
	
	function PNRenderCam:onRotateDown(state)
		-- pnprint("LUA PNRenderCam:onRotateDown()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_BACK)
		else
			self:subMovingState(PN3DObject.STATE_R_BACK)
		end 
	end
	
	function PNRenderCam:onMouseLook(xdelta, ydelta)
		
      if (isInstanceOf(self, "PN3DCamera") == true and self.isRenderCam == false) then 
         -- pnprint("PNRenderCam:MouseLook\n")
      end
      	
    	--self:subTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
    	--PNRenderCam:addTargetMode(PN3DObject.TMODE_DISTANCE_ABS_LOCKED)
    	--PNRenderCam:addTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
		local obj = self:getPositionTarget()		
		yd = 0.0
		xd = 0.0
		----------------- smooth---
		local size = table.getn(self.lastXMouseValues)
		if (size == self.smoothLevel) then
			table.remove(self.lastXMouseValues)
			table.remove(self.lastYMouseValues)
		end
		table.insert(self.lastXMouseValues, 1 ,xdelta)
		table.insert(self.lastYMouseValues, 1 ,ydelta)
		size = table.getn(self.lastXMouseValues)
		for index = 1, size  do
			--pnprint("index:" .. index .. "x value:" .. self.lastXMouseValues[index] .."\n")
			--pnprint("index:" .. index .. "\n")
			xd = xd + self.lastXMouseValues[index] 
			yd = yd + self.lastYMouseValues[index]  
		end
		xd = xd /size
		yd = yd /size
		--pnprint("\nsize: " .. size .. "\nxd: " .. xd .. "\nyd: " .. yd .. "\nxdelta: " .. xdelta .. "\nydelta: " .. ydelta .. "\n")
		----------------------------
		self:rotatePitchRadians(math.rad(yd))
		--if ((obj ~= nil) and (obj:getId() == "Player")) then
         --pnprint("player rotate\n")
		--	obj:rotateYawRadians(math.rad(xd))
		--end
        -- pnprint("PNRenderCamera: rotate\n")
	    self:rotateYawRadians(math.rad(xd))
	    
    	--self:addTargetMode(PN3DObject.TMODE_VIEW_LOCKED)
    	--PNRenderCam:addTargetMode(PN3DObject.TMODE_DISTANCE_ABS_LOCKED)
    	--PNRenderCam:addTargetMode(PN3DObject.TMODE_POSITION_ABS_LOCKED)
		--self.lastYdelta = yd
		--self.lastXdelta = xd
	end
	
	function PNRenderCam:onUpdate(deltaTime)
		--self:update(deltaTime)
	end
------------------------------------------------------------
	function PNRenderCam:onInit()
	end
	
	function PNRenderCam:onDestroy()
	end
	-------------------------------------------------------
