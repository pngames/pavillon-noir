--[[function inheritFrom(child, parent, c_instance)
	child.__parent = parent
	setmetatable(child, {__index = parent})
	if (c_instance ~= nil and c_instance == true)then
		child.__instance = parent
	end
	tolua.inherit(child , child.__instance) -- make child be recognized as parent c_instance
	
	return child
end
--]]

function inheritFrom(obj)
	if (gameMap ~= nil and gameMap.spawn ~= nil and obj.className ~= nil)then
		gameMap:spawn(obj, obj:getId())
	end
		
	local grdParent = obj.__parent or nil
	obj.__parent = {className = obj.className,
	                   __parent = grdParent,
	                   isA = obj.isA or function(self, className) return nil end
	                  }
    
    function obj:isA(className)
		if (self.className == className) then
			return true
		elseif (self.className ~= nil and self.__parent.isA ~= nil) then
			return self.__parent:isA(className)
		end
	    return false	
    end
    
	return obj
end

function isInstanceOf(obj, class)
	return obj:isA(class)	
end

function OVERRIDE(last, functionName)
	last[last.__parent.className.."_"..functionName] =  last[functionName]
	--last[functionName] = nil
end


uid = 0;
function getUID()
	 local suid = "lua_id_"..uid
	uid = uid+1
	return suid
end 