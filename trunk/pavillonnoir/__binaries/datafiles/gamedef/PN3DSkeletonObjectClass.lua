
function PN3DSkeletonObjectClass(id)
	-- make inheritance -----
	pnprint("PN3DSkeletonObjectClass creating\n")
    -------------------------
    local obj = inheritFrom({className = "PN3DSkeletonObject"}, PN3DSkeletonObject:new_local(), true)
    ------ tweak -- 
    obj.__index.className = "PN3DObject"
    -------------------------

    obj:setId(id)
    obj.id = id
    function  obj:onUpdate(deltaTime)
       self:update(deltaTime)
    end
    
    ---------------------move events-----------------------
	function obj:onMoveForward(state)	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function obj:onMoveBackward(state)
		--pnprint(self.id)
		--pnprint(":onMoveBackward\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function obj:onMoveLeft(state)
		pnprint(self.id)
		--pnprint(":onMoveLeft\n")	
		if (state == true) then
			pnprint(" key press\n")
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			pnprint(" key release\n")
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function obj:onMoveRight(state)
		pnprint(self.id)
		--pnprint(":onMoveRight\n")
		if (state == true) then
			pnprint(" key press\n")
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			pnprint(" key release\n")
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end
	
	function obj:onRotateRight(state)
		pnprint("LUA obj:onRotateRight(()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_R_RIGHT)
		end 
	end
	
	function obj:onRotateLeft(state)
		pnprint("LUA obj:onRotateLeft()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_R_LEFT)
		end 
	end
	
	function obj:onRotateUp(state)
		pnprint("LUA obj:onRotateUp()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_TOP)
		else
			self:subMovingState(PN3DObject.STATE_R_TOP)
		end 
	end
	
	function obj:onRotateDown(state)
		pnprint("LUA obj:onRotateDown()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_BACK)
		else
			self:subMovingState(PN3DObject.STATE_R_BACK)
		end 
	end
	
	function obj:onInit()
	end
	
	function obj:onDestroy()
	end
	-------------------------------------------------------
	pnprint("exit PN3DSkeletonObjectClass\n")
    return obj
    
end
