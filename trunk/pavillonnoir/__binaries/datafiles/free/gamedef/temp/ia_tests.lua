--[[pnprint("entering ia_tests.lua\n")
if (gameMap.entities.className.PNAINavy ~= nil) then
	for id, entity in pairs(gameMap.entities.className.PNAINavy) do
		pnprint(entity:getId())
		local aPoint = PNPoint:new_local(-5000.0, 0.0, -4900.0)
		entity:moveTo(aPoint)
		pnprint("\n")
		break
	end	
end
--]]
pnprint("entering ia_tests.lua\n")
if (gameMap.entities.all ~= nil) then
	for id, entity in pairs(gameMap.entities.all) do
		if (entity:isA("PNAIPirate")) then
		if (entity.goal ~= nil) then
			pnprint(entity:getId() .. " goal= " .. entity.goal.x .. " " .. entity.goal.y .. " " .. entity.goal.z .. "\n")
		end
		if (entity:getViewTarget() ~= nil) then
			pnprint(entity:getId() .. " target= " .. entity:getViewTarget():getCoord().x .. " " .. entity:getViewTarget():getCoord().y .. " " .. entity:getViewTarget():getCoord().z .. "\n")
		end
--		local aPoint = PNPoint3f:new_local(2100.0, 20.0, -2400.0)
--		entity:moveTo(aPoint)
--		pnprint("\n")
--		break
	end	
--[[	for id, entity in pairs(gameMap.entities.className.PNAINavy) do
		pnprint(entity:getId())
		local aPoint = PNPoint3f:new_local(5750.0, 30.0, -150.0)
		entity:moveTo(aPoint)
		pnprint("\n")
		break
	end--]]
end
end