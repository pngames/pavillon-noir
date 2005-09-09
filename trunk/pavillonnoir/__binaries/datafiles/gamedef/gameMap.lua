	
gameMap = getGameMap()
tolua:takeownership(gameMap)
gameMap.entities = {}
	

function gameMap:spawn2(entity, id)
	pnprint("[LUA enter function] gameMap:spawn2\n")
	--self.entities[id] = entity
	
    self:addToMap2(entity, id)
   pnprint("[LUA exit function] gameMap:spawn2\n")
end 

function gameMap:clear()
	pnprint("[LUA enter function] gameMap:clear\n")
    pnprint("\n")
	for id, entity in pairs(self.entities) do 
      pnprint(id)
      pnprint("\n")
      self.entities[id] = nil
      pnprint("\n")
	end
    self.entities = {}
   pnprint("[LUA exit function] gameMap:clear\n")
end 

function gameMap:spwan(entity, id, position, orientation, model)
	entity:setCoord(position)
	-- entity.setOrient(orientation)
	entity:unserialize(model)
	self:spawn2(entity, id)
	return entity
end 

function gameMap:onUpdate(deltaTime)
   --pnprint("LUA GameMap: onUpdate()")
   --pnprint(deltaTime)
	for id, entity in pairs(self.entities) do 
		entity:luaUpdate(deltaTime)
	end
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

function gameMap:OnLuaActionMoveForward(id, state)
    pnprint("LUA GameMap:OnLuaActionMoveForward()\n")
    self.entities[id]:OnLuaActionMoveForward(state)
end	

function gameMap:OnLuaActionMoveBackward(id, state)
    pnprint("LUA GameMap:OnLuaActionMoveBackward()\n")
    self.entities[id]:OnLuaActionMoveBackward(state)
end		

function gameMap:OnLuaActionMoveLeft(id, state)
    pnprint("LUA GameMap:OnLuaActionMoveLeft()\n")
    self.entities[id]:OnLuaActionMoveLeft(state)
end	

function gameMap:OnLuaActionMoveRight(id, state)
    pnprint("LUA GameMap:OnLuaActionMoveRight()\n")
    self.entities[id]:OnLuaActionMoveRight(state)
end		
--camera = PN3DCamera:getRenderCam()
--camera:setMovingSpeed(1.0)
