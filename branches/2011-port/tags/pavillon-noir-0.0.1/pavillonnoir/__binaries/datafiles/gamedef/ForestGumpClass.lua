pnprint("ForestGumpClass creating\n")
--loadLuaScript("PN3DSkeletonObjectClass.lua");
--pnprint("ForestGumpClass 2\n")

function ForestGumpClass()
    pnprint("ForestGump creating\n")
    ForestGump = PN3DSkeletonObjectClass()
    ForestGump.className = "ForestGumpClass"
    for id, entity in pairs(gameMap.entities) do 
      if (entity.className == "DragonClass") then
    		ForestGump.target = entity  	
      end
    end
    ForestGump:setTarget(ForestGump.target)
    ForestGump:setMovingMode(ForestGump.MMODE_VIEW_ABS_LOCKED)
    ForestGump:setMovingSpeed(0.75)
    ForestGump:setAnimSpeed(3.0)
    ForestGump:setEnableLoop(true)

--    ForestGump:setMovingState(ForestGump.STATE_T_LEFT)
    ForestGump:setTargetDirection(ForestGump:getFrontDirection())
    ForestGump:setMovingState(ForestGump.STATE_T_FOREWARD)

    ForestGump:startAnimation(0, 0)
    function ForestGump:luaUpdate(deltaTime)
        self:update(deltaTime)
        dir = PNVector3f:new_local(self:getDirect())
        dir.y = 0.0
        self:setDirect(dir)
    end
     
    return ForestGump
end
