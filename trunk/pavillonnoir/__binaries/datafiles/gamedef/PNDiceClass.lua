function PNDiceClass()
	pnprint("PNDice creating\n")
    local OBJ = nil
    OBJ.className="PNDiceClass"
	-- Seed init based on system's time
	math.randomseed( os.time() )
    
    function OBJ:getVal()
    -- Returns pseudo random value between 1 and 6
		return (math.random(6));
	end    
	
	return  OBJ
end

