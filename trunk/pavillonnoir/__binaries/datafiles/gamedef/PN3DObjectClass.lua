
function PN3DObjectClass(id)
	-- make inheritance -----
	pnprint("PN3DObjectClass creating\n")
    local OBJ = inheritFrom({className = "PN3DObject"}, PN3DObject:new_local(), true)
    -------------------------
    OBJ:setId(id)
    OBJ.id = id

    function  OBJ:onUpdate(deltaTime)
	  -- self.__index:update(deltaTime)
       self:update(deltaTime)
    end

	function OBJ:onMouseLook(y, x)
	end
------------------------------ MOVE -----------------------
	function OBJ:onMoveForward(state)
		pnprint("LUA PN3DObject:onMoveForward()\n")	
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function OBJ:onMoveBackward(state)
		pnprint("LUA PN3DObject:onMoveBackward()\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function OBJ:onMoveLeft(state)
		pnprint("LUA PN3DObject:onMoveLeft()\n")	
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function OBJ:onMoveRight(state)
		pnprint("LUA PN3DObject:onMoveRight()\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end
------------------------- ROTATE -----------------------------
	function OBJ:onRotateRight(state)
		pnprint("LUA PN3DObject:onRotateRight()\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_R_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_R_RIGHT)
		end 
	end
	
	function OBJ:onRotateLeft(state)
		pnprint("LUA PN3DObject:onRotateLeft()\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_R_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_R_LEFT)
		end 
	end
	
	function OBJ:onRotateUp(state)
		pnprint("LUA PN3DObject:onRotateUp()\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_R_TOP)
		else
			self:subMovingState(PN3DObject.STATE_R_TOP)
		end 
	end
	
	function OBJ:onRotateDown(state)
		pnprint("LUA PN3DObject:onRotateDown()\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_R_BACK)
		else
			self:subMovingState(PN3DObject.STATE_R_BACK)
		end 
	end
------------------------------------------------------------
	function OBJ:onInit()
	end
	
	function OBJ:onDestroy()
	end
	-------------------------------------------------------
    return OBJ
end

