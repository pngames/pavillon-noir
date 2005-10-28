pnprint("entering ia_tests.lua\n")
if (gameMap.entities.className.PNAINavy ~= nil) then
	for id, entity in pairs(gameMap.entities.className.PNAINavy) do
		pnprint(entity:getId())
		local aPoint = PNPoint:new_local(-5000.0, 0.0, -4900.0)
		entity:moveTo(aPoint)
		pnprint("\n")
		break
	end	
end
