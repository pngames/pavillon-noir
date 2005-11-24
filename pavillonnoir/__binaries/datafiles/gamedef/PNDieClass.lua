function PNDieClass()
	pnprint("PNDieClass creating\n")
    local OBJ = nil
    OBJ.className="PNDieClass"
	-- Seed's init based on the system's time
	math.randomseed( os.time() )
    
		function OBJ:getVal()
			-- Returns pseudo random value between 1 and 6
			-- 3 random are made du to warning in lua's doc: 
			-- "beware! The first random number you get is not really 'randomized' (at least in Windows 2k).
			-- To get better pseudo-random number just pop some random number before using them for real"
			math.random(6)
			math.random(6)
			return (math.random(6));
		end    
	
	return  OBJ
end

