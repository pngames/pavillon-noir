
function PN3DSkeletonObjectClass(id)
	pnprint("PN3DSkeletonObjectClass creating\n")
    local obj = PN3DSkeletonObject:new_local()
    obj:setId(id)
    obj.id = id
    pnprint("PN3DSkeletonObjectClass creating 2\n")
    obj.__index = obj
    pnprint("PN3DSkeletonObjectClass creating 3\n")
    obj.className = "PN3DSkeletonObjectClass"
    pnprint("PN3DSkeletonObjectClass creating 4\n")
	if (obj.id ~= "") then 
		gameMap.entities[obj.id] = obj
	end
	pnprint("PN3DSkeletonObjectClass creating 5\n")
	
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
