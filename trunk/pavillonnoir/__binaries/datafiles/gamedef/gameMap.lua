ACTION_STATE = 	{STOP=0,
				 START=1
				}

	
gameMap = getGameMap()
tolua:takeownership(gameMap)
gameMap.entities = {}	
gameMap.entities.all = {}
gameMap.entities.className = {}
gameMap.fights = {}
gameMap.timer = PNTimerClass()
gameMap.die = PNDieClass()
-------------------------------------------------------------------------------

function gameMap:spawn2(entity, id)
	pnprint("==>> gameMap:spawn2\n")
	print(entity)
	--self.entities[id] = entity
	if (entity.id ~= "") then 
		self.entities.all[entity.id] = entity
	end
	if (self.entities.className[entity.className] ~= nil) then
		self.entities.className[entity.className][id] = entity
	else
		self.entities.className[entity.className] = {}
		self.entities.className[entity.className][id] = entity
	end
	self:addToMap2(entity, id)
    pnprint("<<== gameMap:spawn2\n")
    pnprint("[LUA exit function] gameMap:spawn2\n")
end 
-------------------------------------------------------------------------------

function gameMap:clear()
	pnprint("[LUA enter function] gameMap:clear\n")
    pnprint("\n")
	--local id
	--local entity
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
-------------------------------------------------------------------------------

function gameMap:spwan(entity, id, position, orientation, model)
	entity:setCoord(position)
	entity:unserializeFromPath(model)
	self:spawn2(entity, id)
	return entity
end 
-------------------------------------------------------------------------------

function gameMap:onUpdate(deltaTime)
--	pnprint("=> LUA GameMap: onUpdate()")
	--local id
	--local entity
	self.timer:onUpdate(deltaTime);
	PNRenderCam:onUpdate(deltaTime)
	for id, entity in pairs(self.entities.all) do
	    --print("==>> gameMap:updateLua()")
	    --print(entity)
	    --print(entity.className)
	    entity:onUpdate(deltaTime)
		--print("<<== gameMap:updateLua()\n\n")
	end
	    --print("#######################################################\n")
--	pnprint("<= LUA GameMap: onUpdate()")
end
-------------------------------------------------------------------------------

function gameMap:onInit()
	pnprint("LUA GameMap: onInit()\n")
	--local id
	--local entity
	for id, entity in pairs(self.entities.all) do 
      pnprint(id)
      pnprint("\n")
      self.entities.all[id]:onInit()
      pnprint("\n")
	end
end
-------------------------------------------------------------------------------

function gameMap:onReset()
    pnprint("LUA GameMap: onReset()\n")
end
-------------------------------------------------------------------------------

function gameMap:onNewGame()
    pnprint("LUA GameMap: onNewGame()\n")
end
-------------------------------------------------------------------------------

function gameMap:onStartGame()
    pnprint("LUA GameMap: onStartGame()\n")
end
-------------------------------------------------------------------------------

function gameMap:onPauseGame()
    pnprint("LUA GameMap: onPauseGame()\n")
end
-------------------------------------------------------------------------------

function gameMap:onLeaveGame()
    pnprint("LUA GameMap: onLeaveGame()\n")
end
-------------------------------------------------------------------------------

function gameMap:onLoadMap()
    pnprint("LUA GameMap: onLoadMap()\n")
end
-------------------------------------------------------------------------------

function gameMap:onMoveForward(srcId, targId, state)
    --pnprint("LUA GameMap:onMoveForward()\n")
    --pnprint("TargetId"..targId.."\n")
    if (targId == "")then
    	PNRenderCam:onMoveForward(state)
    else
    	self.entities.all[targId]:onMoveForward(state)
    end
end	
-------------------------------------------------------------------------------

function gameMap:onMoveBackward(srcId, targId, state)
    --pnprint("LUA GameMap:onMoveBackward()\n")
    if (targId == "")then
    	PNRenderCam:onMoveBackward(state)
    else
    	self.entities.all[targId]:onMoveBackward(state)
    end
end		
-------------------------------------------------------------------------------

function gameMap:onMoveLeft(srcId, targId, state)
    --pnprint("LUA GameMap:onMoveLeft()\n")
    if (targId == "")then
    	PNRenderCam:onMoveLeft(state)
    else
    	self.entities.all[targId]:onMoveLeft(state)
    end
end	
-------------------------------------------------------------------------------

function gameMap:onMoveRight(srcId, targId, state)
    --pnprint("LUA GameMap:onMoveRight()\n")
    if (targId == "")then
    	PNRenderCam:onMoveRight(state)
    else
    	self.entities.all[targId]:onMoveRight(state)
    end
end
-------------------------------------------------------------------------------

function gameMap:onRotateLeft(srcId, targId, state)
    --pnprint("LUA GameMap:onRotateLeft()\n")
    if (targId == "")then
    	PNRenderCam:onRotateLeft(state)
    else
    	self.entities.all[targId]:onRotateLeft(state)
    end
end	
-------------------------------------------------------------------------------

function gameMap:onRotateRight(srcId, targId, state)
    --pnprint("LUA GameMap:onRotateRight()\n")
    if (targId == "")then
    	PNRenderCam:onRotateRight(state)
    else
    	self.entities.all[targId]:onRotateRight(state)
    end
end
-------------------------------------------------------------------------------

function gameMap:onMouseMove(xdelta, ydelta)
   -- pnprint("gameMap:onMouseMove()\n")
	--local id
	--local entity
	 
    PNRenderCam:onMouseLook(xdelta, ydelta) 
	for id, entity in pairs(self.entities.all) do 
		entity:onMouseLook(xdelta, ydelta)
	end 
end
-------------------------------------------------------------------------------

function gameMap:onRun(srcId, targId, state)
    --pnprint("==>>GameMap:onRun()\n")
    if (self.entities.all[targId].onRun ~= nil)then
    	self.entities.all[targId]:onRun(state)
    end
    --pnprint("<<==GameMap:onRun()\n")
end
-------------------------------------------------------------------------------

function gameMap:onCrouch(srcId, targId, state)
    --pnprint("LUA GameMap:onCrouch()\n")
    if (self.entities.all[targId].onCrouch ~= nil) then 
    	self.entities.all[targId]:onCrouch(state)
    end
end
-------------------------------------------------------------------------------

function gameMap:onFrustrumIn(sourceId, targetId)
    self.entities.all[sourceId]:onFrustrumIn(self.entities.all[targetId])
end
-------------------------------------------------------------------------------

function gameMap:onFrustrumOut(sourceId, targetId)
    self.entities.all[sourceId]:onFrustrumOut(self.entities.all[targetId])
end
-------------------------------------------------------------------------------

function gameMap:fightAction(sourceId)
	pnprint("=> gameMap:fightAction()\n")
	local targetId = self.fights[sourceId]
	local source = self.entities.all[sourceId]
	local target = self.entities.all[targetId]
	pnprint(sourceId .. " attacking " .. targetId .. "\n")

	nbAS = source:getNBFightSuccess()
	nbDS = target:getNBFightSuccess()
	local localisation = 0
	local strikeAnim = CHARACTER_ANIM.STRIKE_HEAD
	if (source.strikeLocalisation == LOCALISATION.RANDOM) then
		localisation = self.die:getVal(6)
	else
		localisation = source.strikeLocalisation
		nbAS = nbAS - 1
	end
	-- set strikeAnim to corresponding location
	if (localisation == LOCALISATION.HEAD) then
		strikeAnim = CHARACTER_ANIM.STRIKE_HEAD
	elseif (localisation == LOCALISATION.TORSO) then
		strikeAnim = CHARACTER_ANIM.STRIKE_HEAD -- torso
	elseif (localisation == LOCALISATION.LARM) then
		strikeAnim = CHARACTER_ANIM.STRIKE_HEAD -- larm
	elseif (localisation == LOCALISATION.RARM) then
		strikeAnim = CHARACTER_ANIM.STRIKE_HEAD -- rarm
	elseif (localisation == LOCALISATION.LLEG) then
		strikeAnim = CHARACTER_ANIM.STRIKE_HEAD -- lleg
	elseif (localisation == LOCALISATION.RLEG) then
		strikeAnim = CHARACTER_ANIM.STRIKE_HEAD -- rleg
	end
		
	pnprint("nbAtackerSucces=" .. nbAS .. "nbDefenderSuccess=" .. nbDS .. "\n")
	local success = nbAS - nbDS
	local sAnim = 0
	local tAnim = 0

	if ((target.combat_state == COMBAT_STATE.ATTACK) and (self.fights[targetId] == sourceId)) then
		pnprint(targetId .. " tries to counter!\n")
		if (success > 0) then
			target:onDamage(success + source.stats[source.selected_weapon.skill] + source.selected_weapon.modifier - target.armor, localisation, source)
			--anim
			sAnim = strikeAnim
			tAnim = CHARACTER_ANIM.JUMP
		else
			source:onDamage(-success + target.stats[target.selected_weapon.skill] + target.selected_weapon.modifier - source.armor, self.die:getVal(6), target)
			--anim
			sAnim = CHARACTER_ANIM.JUMP
			tAnim = strikeAnim
		end

	elseif (target.combat_state == COMBAT_STATE.DODGE) then
		pnprint(targetId .. " tries to dodge!\n")
		if (success > 0) then
			target:onDamage(success + source.stats[source.selected_weapon.skill] + source.selected_weapon.modifier - target.armor, localisation,source)
			--anim
			sAnim = strikeAnim
			tAnim = CHARACTER_ANIM.JUMP
		else
			--anim
			sAnim = strikeAnim
			tAnim = CHARACTER_ANIM.CROUCH
			target.elapsedTurns = 1 --Cannot attack right after
		end

	elseif (target.combat_state == COMBAT_STATE.DEFENSE) then
		pnprint(targetId .. " defending!\n")
		sAnim = strikeAnim
		if (success > 0) then
			target:onDamage(success + source.stats[source.selected_weapon.skill] + source.selected_weapon.modifier - target.armor, localisation, source)
			--anim
			tAnim = CHARACTER_ANIM.JUMP
		else
			tAnim = CHARACTER_ANIM.CROUCH_L
			--anim
		end

	else
		pnprint(targetId .. " gonna get it loud!\n")
		target:onDamage(nbAS + source.stats[source.selected_weapon.skill] + source.selected_weapon.modifier - target.armor, localisation, source)
		sAnim = strikeAnim
		tAnim = CHARACTER_ANIM.JUMP
	end

	self.fights[sourceId] = -1
	if (self.fights[targetId] == sourceId) then
		self.fights[targetId] = -1
	end
	if (source.health_state < HEALTH_STATE.COMA) then
		source:waitForAnimEnd(sAnim)
	end
	if (target.health_state < HEALTH_STATE.COMA) then
		target:waitForAnimEnd(tAnim)
	end
	--source.combat_state = COMBAT_STATE.NEUTRAL
	--target.combat_state = COMBAT_STATE.NEUTRAL
	pnprint("<= gameMap:fightAction()\n")
end
-------------------------------------------------------------------------------
function gameMap:onAttack(sourceId, targetId)
	--local id
	--local entity
	pnprint(sourceId .. " wants to attack " .. targetId .. "\n")
	self.fights[sourceId] = targetId
	if (self.fights[targetId] ~= sourceId) then
		--pnprint("addTask\n")
		self.timer:addTask(self, "fightAction", 100, false, sourceId)
	else
		self.entities.all[sourceId].strikeLocalisation = LOCALISATION.RANDOM
	end
end
-------------------------------------------------------------------------------
function gameMap:onPrimaryAttack(srcId, targId, state)	
    pnprint("gameMap:onPrimaryAttack:   TargetId '"..targId.."'\n")
	if (targId ~= "" and self.entities.all[targId].onPrimaryAttack ~= nil)then
    	self.entities.all[targId]:onPrimaryAttack(state)
    end
end
-------------------------------------------------------------------------------
function gameMap:onDeath(deadId)
	pnprint("=> GameMap:onDeath(" .. deadId .. ")\n")
	for id, entity in pairs(self.entities.className.PNAICharacter) do
		pnprint(id .. "\n")
		if (id ~= deadId) then
			entity:isDead(deadId)
		end
	end
	pnprint("<= GameMap:onDeath(" .. deadId .. ")\n")
end
