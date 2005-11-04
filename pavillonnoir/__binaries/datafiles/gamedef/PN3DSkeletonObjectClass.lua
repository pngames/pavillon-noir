
function PN3DSkeletonObjectClass(id)
	-- make inheritance -----
	pnprint("PN3DSkeletonObjectClass creating\n")
    -------------------------
    local OBJ = inheritFrom({className = "PN3DSkeletonObject"}, PN3DSkeletonObject:new_local(), true)
    ------ tweak -- 
    OBJ.__parent.className = "PN3DObject"
    -------------------------

    OBJ:setId(id)
    OBJ.id = id
    function  OBJ:onUpdate(deltaTime)
       self:update(deltaTime)
    end
    
	function OBJ:onMouseLook(y, x)
	end
	    
    ---------------------move events-----------------------
	function OBJ:onMoveForward(state)
    	pnprint("==>> PN3DSkeletonObject:onMoveForward()\n")	
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end
		pnprint("<<== PN3DSkeletonObject:onMoveForward()\n")	 
	end	

	function OBJ:onMoveBackward(state)
		--pnprint(self.id)
		--pnprint(":onMoveBackward\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function OBJ:onMoveLeft(state)
		pnprint(self.id)
		--pnprint(":onMoveLeft\n")	
		if (state == ACTION_STATE.START) then
			pnprint(" key press\n")
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			pnprint(" key release\n")
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function OBJ:onMoveRight(state)
		pnprint(self.id)
		--pnprint(":onMoveRight\n")
		if (state == ACTION_STATE.START) then
			pnprint(" key press\n")
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			pnprint(" key release\n")
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end
	
	function OBJ:onRotateRight(state)
		pnprint("LUA OBJ:onRotateRight(()\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_R_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_R_RIGHT)
		end 
	end
	
	function OBJ:onRotateLeft(state)
		pnprint("LUA OBJ:onRotateLeft()\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_R_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_R_LEFT)
		end 
	end
	
	function OBJ:onRotateUp(state)
		pnprint("LUA obj:onRotateUp()\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_R_TOP)
		else
			self:subMovingState(PN3DObject.STATE_R_TOP)
		end 
	end
	
	function OBJ:onRotateDown(state)
		pnprint("LUA obj:onRotateDown()\n")
		if (state == ACTION_STATE.START) then
			self:addMovingState(PN3DObject.STATE_R_BACK)
		else
			self:subMovingState(PN3DObject.STATE_R_BACK)
		end 
	end
	
	function OBJ:onInit()
	end
	
	function OBJ:onDestroy()
	end
	-------------------------------------------------------
	pnprint("exit PN3DSkeletonObjectClass\n")
    return OBJ
    
end
