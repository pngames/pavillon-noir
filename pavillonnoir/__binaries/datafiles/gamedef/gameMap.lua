	
gameMap = getGameMap()
tolua:takeownership(gameMap)
gameMap.entities = {}	
gameMap.entities.all = {}
gameMap.entities.className = {}

function gameMap:spawn2(entity, id)
	pnprint("[LUA enter function] gameMap:spawn2\n")
	--self.entities[id] = entity
	if (entity.id ~= "") then 
		gameMap.entities.all[entity.id] = entity
	end
	if (self.entities.className[entity.className] ~= nil) then
		self.entities.className[entity.className][id] = entity
	else
		self.entities.className[entity.className] = {}
		self.entities.className[entity.className][id] = entity
	end
    self:addToMap2(entity.__instance, id)
   pnprint("[LUA exit function] gameMap:spawn2\n")
end 

function gameMap:clear()
	pnprint("[LUA enter function] gameMap:clear\n")
    pnprint("\n")
	for id, entity in pairs(self.entities.all) do 
      pnprint(id)
      pnprint("\n")
      self.entities.all[id]:onDestroy()
      pnprint("\n")
	end
	self.entities = nil
	collectgarbage()
   pnprint("[LUA exit function] gameMap:clear\n")
end 

function gameMap:spwan(entity, id, position, orientation, model)
	entity:setCoord(position)
	entity:unserializeFromFile(model)
	self:spawn2(entity, id)
	return entity
end 

function gameMap:onUpdate(deltaTime)
--	pnprint("=> LUA GameMap: onUpdate()")
	for id, entity in pairs(self.entities.all) do 
		entity:onUpdate(deltaTime)
	end
	PNRenderCam:onUpdate(deltaTime)
--	pnprint("<= LUA GameMap: onUpdate()")
end

function gameMap:onInit()
	pnprint("LUA GameMap: onInit()\n")
	for id, entity in pairs(self.entities.all) do 
      pnprint(id)
      pnprint("\n")
      self.entities.all[id]:onInit()
      pnprint("\n")
	end
end

function gameMap:onReset()
    pnprint("LUA GameMap: onReset()\n")
end

function gameMap:onNewGame()
    pnprint("LUA GameMap: onNewGame()\n")
end

function gameMap:onStartGame()
    pnprint("LUA GameMap: onStartGame()\n")
end

function gameMap:onPauseGame()
    pnprint("LUA GameMap: onPauseGame()\n")
end

function gameMap:onLeaveGame()
    pnprint("LUA GameMap: onLeaveGame()\n")
end

function gameMap:onLoadMap()
    pnprint("LUA GameMap: onLoadMap()\n")
end

function gameMap:onMoveForward(srcId, targId, state)
    pnprint("LUA GameMap:onMoveForward()\n")
    self.entities.all[targId]:onMoveForward(state)
end	

function gameMap:onMoveBackward(srcId, targId, state)
    pnprint("LUA GameMap:onMoveBackward()\n")
    self.entities.all[targId]:onMoveBackward(state)
end		

function gameMap:onMoveLeft(srcId, targId, state)
    pnprint("LUA GameMap:onMoveLeft()\n")
    self.entities.all[targId]:onMoveLeft(state)
end	

function gameMap:onMoveRight(srcId, targId, state)
    pnprint("LUA GameMap:onMoveRight()\n")
    self.entities.all[targId]:onMoveRight(state)
end

function gameMap:onMouseMove(xdelta, ydelta)
   -- pnprint("gameMap:onMouseMove()\n")  
    PNRenderCam:onMouseLook(xdelta, ydelta) 
end

function gameMap:onFrustrumIn(sourceId, targetId)
    self.entities.all[sourceId]:onFrustrumIn(self.entities.all[targetId])
end 

function gameMap:onFrustrumOut(sourceId, targetId)
    self.entities.all[sourceId]:onFrustrumIn(self.entities.all[targetId])
end 


	
--camera = PN3DCamera:getRenderCam()
--camera:setMovingSpeed(1.0)
