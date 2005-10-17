	--pnprint("renderCam creating\n")
	-- make inheritance -----
	--pnprint("renderCam creating\n")
    renderCam  = {__index = PN3DCamera:getRenderCam()}
	renderCam.__instance  = renderCam.__index
    setmetatable(renderCam, renderCam)
    tolua.inherit(renderCam, renderCam.__instance) -- make obj be recognize as PN3DSkeletonObject
	renderCam.className = "renderCam"
    -------------------------
    -------------------------
    renderCam:setId("renderCam")
    renderCam.id = "renderCam"

	renderCam.yawSpeed = 0.0
    renderCam.pitchSpeed = 0.0
    renderCam.RollSpeed = 0.0
    renderCam.lastYdelta = 0.0
    renderCam.lastXdelta = 0.0
    renderCam.smoothLevel = 5
    renderCam.lastXMouseValues = {}
    table.insert(renderCam.lastXMouseValues, 0,0)
    renderCam.lastYMouseValues = {}
    table.insert(renderCam.lastYMouseValues, 0,0)
------------------------------ MOVE -----------------------
	function renderCam:onActionMoveForward(state)
		pnprint("LUA renderCam:onActionMoveForward()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function renderCam:onActionMoveBackward(state)
		pnprint("LUA renderCam:onActionMoveBackward()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function renderCam:onActionMoveLeft(state)
		pnprint("LUA renderCam:onActionMoveLeft()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function renderCam:onActionMoveRight(state)
		pnprint("LUA renderCam:onActionMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end
------------------------- ROTATE -----------------------------
	function renderCam:onActionRotateRight(state)
		pnprint("LUA renderCam:onActionRotateRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_R_RIGHT)
		end 
	end
	
	function renderCam:onActionRotateLeft(state)
		pnprint("LUA renderCam:onActionRotateLeft()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_R_LEFT)
		end 
	end
	
	function renderCam:onActionRotateUp(state)
		pnprint("LUA renderCam:onActionRotateUp()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_TOP)
		else
			self:subMovingState(PN3DObject.STATE_R_TOP)
		end 
	end
	
	function renderCam:onActionRotateDown(state)
		pnprint("LUA renderCam:onActionRotateDown()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_BACK)
		else
			self:subMovingState(PN3DObject.STATE_R_BACK)
		end 
	end
	
	function renderCam:onMouseLook(xdelta, ydelta)
		pnprint("renderCam:onActionMouseLook\n")
		local obj = self:getPositionTarget()		
		local yd -- = (ydelta+self.lastYdelta)/2
		local xd -- = (xdelta+self.lastXdelta)/2 
		----------------- smooth---------------------------------
		local size = table.getn(self.lastXMouseValues)
		if (size == self.smoothLevel) then
			table.remove(self.lastXMouseValues)
			table.remove(self.lastYMouseValues)
		end
		table.insert(self.lastXMouseValues, 0 ,xdelta)
		table.insert(self.lastYMouseValues, 0 ,ydelta)
		size = table.getn(self.lastXMouseValues)
		xd = 0
		yd = 0
		for id = 0, size-1  do
			pnprint("id:" .. id .. " value:" .. self.lastXMouseValues[id] .."\n" )
			xd = xd + self.lastXMouseValues[id] 
			yd = yd + self.lastYMouseValues[id]  
		end
		xd = xd /size
		yd = yd /size
		pnprint("\nsize: " .. size .. "\nxd: " .. xd .. "\nyd: " .. yd .. "\nxdelta: " .. xdelta .. "\nydelta: " .. ydelta .. "\n")
		----------------------------------------------------------
		self:rotatePitchRadians(math.rad(yd))
		if ((obj ~= nil) and (obj:getId() == "Player")) then
			obj:rotateYawRadians(math.rad(xd))
		end
	    self:rotateYawRadians(math.rad(xd))
		--self.lastYdelta = yd
		--self.lastXdelta = xd
	end
	
	function renderCam:onUpdate(deltaTime)
		--self:update(deltaTime)
	end
------------------------------------------------------------
	function renderCam:onInit()
	end
	
	function renderCam:onDestroy()
	end
	-------------------------------------------------------
