
function PN3DSkeletonObjectClass(id)
	-- make inheritance -----
	pnprint("PN3DSkeletonObjectClass creating\n")
    local obj = {__index = PN3DSkeletonObject:new_local()}
	obj.__instance  = obj.__index
    setmetatable(obj, obj)
    tolua.inherit(obj, obj.__instance) -- make obj be recognize as PN3DSkeletonObject
	obj.className = "PN3DSkeletonObject"
    -------------------------
    obj:setId(id)
    obj.id = id
    pnprint("PN3DSkeletonObjectClass creating 2\n")
    pnprint("PN3DSkeletonObjectClass creating 3\n")
    obj.className = "PN3DSkeletonObjectClass"
    pnprint("PN3DSkeletonObjectClass creating 4\n")
	pnprint("PN3DSkeletonObjectClass creating 5\n")
	
    function  obj:onUpdate(deltaTime)
       self:update(deltaTime)
    end
    
    ---------------------move events-----------------------
	function obj:onActionMoveForward(state)	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function obj:onActionMoveBackward(state)
		--pnprint(self.id)
		--pnprint(":onActionMoveBackward\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function obj:onActionMoveLeft(state)
		pnprint(self.id)
		--pnprint(":onActionMoveLeft\n")	
		if (state == true) then
			pnprint(" key press\n")
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			pnprint(" key release\n")
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function obj:onActionMoveRight(state)
		pnprint(self.id)
		--pnprint(":onActionMoveRight\n")
		if (state == true) then
			pnprint(" key press\n")
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			pnprint(" key release\n")
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end
	
	function obj:onActionRotateRight(state)
		pnprint("LUA obj:onActionRotateRight(()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_R_RIGHT)
		end 
	end
	
	function obj:onActionRotateLeft(state)
		pnprint("LUA obj:onActionRotateLeft()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_R_LEFT)
		end 
	end
	
	function obj:onActionRotateUp(state)
		pnprint("LUA obj:onActionRotateUp()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_TOP)
		else
			self:subMovingState(PN3DObject.STATE_R_TOP)
		end 
	end
	
	function obj:onActionRotateDown(state)
		pnprint("LUA obj:onActionRotateDown()\n")
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
