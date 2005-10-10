pnprint("entering ia_tests.lua\n")
if (gameMap.entities.className.PNCharacterClass ~= nil) then
	for id, entity in pairs(gameMap.entities.className.PNCharacterClass) do
		pnprint(entity.id)
		local aPoint = PNPoint:new_local(-5000.0, 0.0, -4900.0)
		entity:moveTo(aPoint)
		pnprint("\n")
		break
	end	
end