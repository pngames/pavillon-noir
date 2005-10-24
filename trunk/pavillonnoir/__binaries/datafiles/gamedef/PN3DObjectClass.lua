
function PN3DObjectClass(id)
	-- make inheritance -----
	pnprint("PN3DObjectClass creating\n")
    local obj = inheritFrom({className = "PN3DObject"}, PN3DObject:new_local(), true)
    -------------------------
    obj:setId(id)
    obj.id = id

    function  obj:onUpdate(deltaTime)
	  -- self.__index:update(deltaTime)
       self:update(deltaTime)
    end


------------------------------ MOVE -----------------------
	function obj:onMoveForward(state)
		pnprint("LUA obj:onMoveForward()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function obj:onMoveBackward(state)
		pnprint("LUA obj:onMoveBackward()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function obj:onMoveLeft(state)
		pnprint("LUA obj:onMoveLeft()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function obj:onMoveRight(state)
		pnprint("LUA obj:onMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end
------------------------- ROTATE -----------------------------
	function obj:onRotateRight(state)
		pnprint("LUA obj:onRotateRight()\n")
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
------------------------------------------------------------
	function obj:onInit()
	end
	
	function obj:onDestroy()
	end
	-------------------------------------------------------
    return obj
end

