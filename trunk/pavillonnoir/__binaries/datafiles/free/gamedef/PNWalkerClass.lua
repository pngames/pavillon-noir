PNJDestinations = {
				PNPoint3f:new_local(2270, 6, -1100),
				PNPoint3f:new_local(3050, 6, 775),
				PNPoint3f:new_local(1050, 6, 775),
				PNPoint3f:new_local(2200, 6, 1500),
				PNPoint3f:new_local(3350, 6, -250),
				PNPoint3f:new_local(1050, 6, -250),
				PNPoint3f:new_local(2200, 6, -250),
				PNPoint3f:new_local(1000, 6, 100),
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

function PNWalkerClass(id)
	pnprint("PNPNJClass creating\n")
	-- make inheritance -----
	local OBJ = inheritFrom(PNPNJClass(id))
	OBJ.className = "PNWalker" 
	
	OVERRIDE(OBJ, "onInit")
	function OBJ:onInit()
		self:PNPNJ_onInit()
		self:moveTo(PNJDestinations[math.random(1,9)])
	end
	
	OVERRIDE(OBJ, "onUpdate")
	function OBJ:onUpdate(deltatTime)
		self:PNPNJ_onUpdate(deltatTime)
		if (self:getCoord().x > 3600) then
			self:moveTo(PNJDestinations[2])
		end
		if (self.state == self.stateEnum.PN_IA_PASSIVE)	then
			self:moveTo(PNJDestinations[math.random(1,9)])
		end
	end
	
	OVERRIDE(OBJ, "getItem")
	function OBJ:getItem(item)

	end
	
	
	return OBJ
end
