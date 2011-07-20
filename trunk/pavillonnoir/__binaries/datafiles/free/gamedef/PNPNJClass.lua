PNJDestinations = {
				PNPoint3f:new_local(2270, 6, -1100),
				PNPoint3f:new_local(3050, 6, 775),
				PNPoint3f:new_local(2200, 6, 1500),
				PNPoint3f:new_local(3350, 6, -250),
				PNPoint3f:new_local(3050, 6, 775),
				PNPoint3f:new_local(1050, 6, -250),
				PNPoint3f:new_local(2200, 6, -2450),
				PNPoint3f:new_local(1050, 6, 775),
				PNPoint3f:new_local(2200, 6, 775)
			  }

indice = 1;

function getNextIndice()
	local res  = 0
	if (indice <= 9)then
		res = indice
		indice = indice+1
	else
		res = 1
		indice = 2
	end
	pnprint("res = " .. res .. "\n[lua]")
	return res
end			  

function PNPNJClass(id)
	pnprint("PNPNJClass creating\n")
	-- make inheritance -----
	local OBJ = inheritFrom(PNAICharacterClass(id))
	OBJ.className = "PNPNJ" 
		
	
	return OBJ
end