pnprint("entering ia_tests.lua\n")
if (gameMap.entities.className.PNCharacter ~= nil) then
	for id, entity in pairs(gameMap.entities.className.PNAICharacter) do
		pnprint(entity.id)
		local aPoint = PNPoint:new_local(-5000.0, 0.0, -4900.0)
		entity:moveTo(aPoint)
		pnprint("\n")
		break
	end	
end