function PNDieClass()
	pnprint("PNDieClass creating\n")
    local OBJ = {}
    OBJ.className="PNDieClass"
	-- Seed's init based on the system's time
	math.randomseed( os.time() )
	math.random(10)
	math.random(10)
    
		function OBJ:getVal(nbFaces)
			-- Returns pseudo random value between 1 and 10
			-- 3 random are made du to warning in lua's doc: 
			-- "beware! The first random number you get is not really 'randomized' (at least in Windows 2k).
			-- To get better pseudo-random number just pop some random number before using them for real"
			return (math.random(nbFaces))
		end    
	
	return  OBJ
end

