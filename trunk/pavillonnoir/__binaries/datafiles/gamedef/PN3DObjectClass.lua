
function PN3DObjectClass()
    local obj = PN3DObject:new_local()
    obj.__index = obj
    obj.className = "PN3DObjectClass"

    function  obj:luaUpdate(deltaTime)
       self.__index:update(deltaTime)
    end


    	---------------------move events-----------------------
	function obj:OnLuaActionMoveForward(state)
		pnprint("LUA obj:OnLuaActionMoveForward()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function obj:OnLuaActionMoveBackward(state)
		pnprint("LUA obj:OnLuaActionMoveBackward()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function obj:OnLuaActionMoveLeft(state)
		pnprint("LUA obj:OnLuaActionMoveLeft()\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function obj:OnLuaActionMoveRight(state)
		pnprint("LUA obj:OnLuaActionMoveRight()\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end
	-------------------------------------------------------
    return obj
end

