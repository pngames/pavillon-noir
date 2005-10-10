
function PN3DObjectClass(id)
	-- make inheritance -----
	pnprint("PN3DObjectClass creating\n")
    local obj = {__index = PN3DObject:new_local()}
	obj.__instance  = obj.__index
    setmetatable(obj, obj)
    tolua.inherit(obj, obj.__instance) -- make obj be recognize as PN3DSkeletonObject
	obj.className = "PN3DObjectClass"
    -------------------------
    obj:setId(id)
    obj.id = id

    function  obj:onLuaUpdate(deltaTime)
	  -- self.__index:update(deltaTime)
       self:update(deltaTime)
    end


    	---------------------move events-----------------------
	function obj:onLuaActionMoveForward(state)
		pnprint("LUA obj:onLuaActionMoveForward()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function obj:onLuaActionMoveBackward(state)
		pnprint("LUA obj:onLuaActionMoveBackward()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function obj:onLuaActionMoveLeft(state)
		pnprint("LUA obj:onLuaActionMoveLeft()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function obj:onLuaActionMoveRight(state)
		pnprint("LUA obj:onLuaActionMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end
	
	function obj:onLuaInit()
	end
	
	-------------------------------------------------------
    return obj
end

