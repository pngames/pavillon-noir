function inheritFrom(child, parent, c_instance)
	child.__index = parent
	setmetatable(child, child)
	if (c_instance ~= nil and c_instance == true)then
		child.__instance = parent
	end
	tolua.inherit(child , child.__instance) -- make child be recognized as parent c_instance
	
	return child
end

function isInstanceOf(obj, class)
	if (obj ~= nil and obj.className ~= nil) then
		--pnprint (obj.className.. "is instance of 1" .. class .. "\n")
		if (obj.className == class) then
			--pnprint ("is insatnce of 2 \n")
			return true
		else
			--pnprint ("is insatnce of 3 \n")
			return isInstanceOf(obj.__index, class)
		end
	end
	--pnprint ("is insatnce of 4 \n")
	return false	
end
