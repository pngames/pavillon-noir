
if gameMap ~= nil && gameMap.entities ~= nil && gameMap.entities.Character ~= nil then
	for local entity in ipairs(self.entities.all) do 
      pnprint(entity.id)
		local aPoint = PNPoint:new_local(4900.0, 0.0, 4900.0)
		entity:moveTo(aPoint)
      pnprint("\n")
	end	
end