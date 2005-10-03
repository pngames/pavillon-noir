	
gameMap = getGameMap()
tolua:takeownership(gameMap)
gameMap.entities = {}	
gameMap.entities.all = {}
gameMap.entities.className = {}

function gameMap:spawn2(entity, id)
	pnprint("[LUA enter function] gameMap:spawn2\n")
	--self.entities[id] = entity
	if (self.entities.className[entity.className] ~= nil) then
		self.entities.className[entity.className][id] = entity
	else
		self.entities.className[entity.className] = {}
		self.entities.className[entity.className][id] = entity
	end
    self:addToMap2(entity, id)
   pnprint("[LUA exit function] gameMap:spawn2\n")
end 

function gameMap:clear()
	pnprint("[LUA enter function] gameMap:clear\n")
    pnprint("\n")
	for id, entity in pairs(self.entities.all) do 
      pnprint(id)
      pnprint("\n")
      self.entities.all[id] = nil
      pnprint("\n")
	end
    self.entities = {}
   pnprint("[LUA exit function] gameMap:clear\n")
end 

function gameMap:spwan(entity, id, position, orientation, model)
	entity:setCoord(position)
	-- entity.setOrient(orientation)
	entity:unserializeFromFile(model)
	self:spawn2(entity, id)
	return entity
end 

function gameMap:onLuaUpdate(deltaTime)
--	pnprint("=> LUA GameMap: onUpdate()")
   --pnprint(deltaTime)
	for id, entity in pairs(self.entities.all) do 
		entity:onLuaUpdate(deltaTime)
	end
--	pnprint("<= LUA GameMap: onUpdate()")
end

function gameMap:onInit()
	pnprint("LUA GameMap: onInit()\n")
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

function gameMap:onLuaActionMoveForward(id, state)
    pnprint("LUA GameMap:onLuaActionMoveForward()\n")
    self.entities.all[id]:onLuaActionMoveForward(state)
end	

function gameMap:onLuaActionMoveBackward(id, state)
    pnprint("LUA GameMap:onLuaActionMoveBackward()\n")
    self.entities.all[id]:onLuaActionMoveBackward(state)
end		

function gameMap:onLuaActionMoveLeft(id, state)
    pnprint("LUA GameMap:onLuaActionMoveLeft()\n")
    self.entities.all[id]:onLuaActionMoveLeft(state)
end	

function gameMap:onLuaActionMoveRight(id, state)
    pnprint("LUA GameMap:onLuaActionMoveRight()\n")
    self.entities.all[id]:onLuaActionMoveRight(state)
end		
--camera = PN3DCamera:getRenderCam()
--camera:setMovingSpeed(1.0)
