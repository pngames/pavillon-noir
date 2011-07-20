function PNForgeronClass(id)
	pnprint("PNForgeronClass creating\n")
	-- make inheritance -----
	local OBJ = inheritFrom(PNPNJClass(id))
	OBJ.className = "PNForgeron" 
	
	function OBJ:onUse()
		gameMap.player:getItem(gameMap.entities.className.PNSaberWeapon[1])
	end
	
	
	return OBJ
end
