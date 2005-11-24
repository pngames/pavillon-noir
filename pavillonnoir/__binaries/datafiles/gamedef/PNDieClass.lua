function PNDieClass()
	pnprint("PNDieClass creating\n")
    local OBJ = nil
    OBJ.className="PNDieClass"
	-- Seed init based on system's time
	math.randomseed( os.time() )
    
    function OBJ:getVal()
    -- Returns pseudo random value between 1 and 6
		return (math.random(6));
	end    
	
	return  OBJ
end

