
function PN3DSkeletonObjectClass(id)
	-- make inheritance -----
	pnprint("PN3DSkeletonObjectClass creating\n")
    local obj = {__index = PN3DSkeletonObject:new_local()}
	obj.__instance  = obj.__index
    setmetatable(obj, obj)
    tolua.inherit(obj, obj.__instance) -- make obj be recognize as PN3DSkeletonObject
	obj.className = "PN3DSkeletonObjectClass"
    -------------------------
    obj:setId(id)
    obj.id = id
    pnprint("PN3DSkeletonObjectClass creating 2\n")
    pnprint("PN3DSkeletonObjectClass creating 3\n")
    obj.className = "PN3DSkeletonObjectClass"
    pnprint("PN3DSkeletonObjectClass creating 4\n")
	pnprint("PN3DSkeletonObjectClass creating 5\n")
	
    function  obj:onLuaUpdate(deltaTime)
       -- self.__index:update(deltaTime)
       --pnprint(self.id)		
       --pnprint("onLuaUpdate\n")
       self:update(deltaTime)
    end
    
    ---------------------move events-----------------------
	function obj:onLuaActionMoveForward(state)
		--pnprint(self.id)
		--pnprint(":onLuaActionMoveForward\n")	
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_FORWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_FORWARD)
		end 
	end	

	function obj:onLuaActionMoveBackward(state)
		--pnprint(self.id)
		--pnprint(":onLuaActionMoveBackward\n")
		if (state == true) then
			self:addMovingState(PN3DObject.STATE_T_BACKWARD)
		else
			self:subMovingState(PN3DObject.STATE_T_BACKWARD)
		end 
	end
	
	function obj:onLuaActionMoveLeft(state)
		pnprint(self.id)
		--pnprint(":onLuaActionMoveLeft\n")	
		if (state == true) then
			pnprint(" key press\n")
			self:addMovingState(PN3DObject.STATE_T_LEFT)
		else
			pnprint(" key release\n")
			self:subMovingState(PN3DObject.STATE_T_LEFT)
		end 
	end	

	function obj:onLuaActionMoveRight(state)
		pnprint(self.id)
		--pnprint(":onLuaActionMoveRight\n")
		if (state == true) then
			pnprint(" key press\n")
			self:addMovingState(PN3DObject.STATE_T_RIGHT)
		else
			pnprint(" key release\n")
			self:subMovingState(PN3DObject.STATE_T_RIGHT)
		end 
	end
	
	function obj:onLuaInit()
	end
	-------------------------------------------------------
	pnprint("exit PN3DSkeletonObjectClass\n")
    return obj
end
