
function PN3DObjectClass(id)
	-- make inheritance -----
	pnprint("PN3DObjectClass creating\n")
    local obj = {__index = PN3DObject:new_local()}
	obj.__instance  = obj.__index
    setmetatable(obj, obj)
    tolua.inherit(obj, obj.__instance) -- make obj be recognize as PN3DSkeletonObject
	obj.className = "PN3DObject"
    -------------------------
    obj:setId(id)
    obj.id = id

    function  obj:onUpdate(deltaTime)
	  -- self.__index:update(deltaTime)
       self:update(deltaTime)
    end


    	---------------------move events-----------------------
	function obj:onActionMoveForward(state)
		pnprint("LUA obj:onActionMoveForward()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function obj:onActionMoveBackward(state)
		pnprint("LUA obj:onActionMoveBackward()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function obj:onActionMoveLeft(state)
		pnprint("LUA obj:onActionMoveLeft()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function obj:onActionMoveRight(state)
		pnprint("LUA obj:onActionMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end

	function obj:onActionRotateYawRight(state)
		pnprint("LUA obj:onActionMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_R_RIGHT)
		end 
	end
	
	function obj:onActionRotateYawLeft(state)
		pnprint("LUA obj:onActionMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_R_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_R_LEFT)
		end 
	end

	function obj:onInit()
	end
	
	function obj:onDestroy()
	end
	-------------------------------------------------------
    return obj
end

