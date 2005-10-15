function inheritFrom(parent)
	local child = {__index = parent}
	setmetatable(child, child)
	tolua.inherit(child , parent.__instance) -- make child be recognized as parent c_instance
	return child
end
	
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
	-- entity.setOrient(orientation)
	entity:unserializeFromFile(model)
	self:spawn2(entity, id)
	return entity
end 

function gameMap:onUpdate(deltaTime)
	--pnprint("[UPDATE] start lua update\n")
--	pnprint("=> LUA GameMap: onUpdate()")
   --pnprint(deltaTime)
	for id, entity in pairs(self.entities.all) do 
		entity:onUpdate(deltaTime)
	end
--	pnprint("<= LUA GameMap: onUpdate()")
--	pnprint("[UPDATE] end lua update\n")
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

function gameMap:onActionMoveForward(id, state)
    pnprint("LUA GameMap:onActionMoveForward()\n")
    self.entities.all[id]:onActionMoveForward(state)
end	

function gameMap:onActionMoveBackward(id, state)
    pnprint("LUA GameMap:onActionMoveBackward()\n")
    self.entities.all[id]:onActionMoveBackward(state)
end		

function gameMap:onActionMoveLeft(id, state)
    pnprint("LUA GameMap:onActionMoveLeft()\n")
    self.entities.all[id]:onActionMoveLeft(state)
end	

function gameMap:onActionMoveRight(id, state)
    pnprint("LUA GameMap:onActionMoveRight()\n")
    self.entities.all[id]:onActionMoveRight(state)
end		
--camera = PN3DCamera:getRenderCam()
--camera:setMovingSpeed(1.0)
