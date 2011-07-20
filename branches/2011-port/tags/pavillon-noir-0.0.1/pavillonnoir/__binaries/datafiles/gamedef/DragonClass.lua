pnprint("DragonClass creating\n")
--loadLuaScript("PN3DSkeletonObjectClass.lua");
--pnprint("DragonClass 2\n")

function DragonClass()
    pnprint("Dragon creating\n")
    Dragon = PN3DSkeletonObjectClass()
    Dragon.__index = Dragon
    Dragon.className = "DragonClass"
    Dragon.target = PN3DObjectClass()
    Dragon.target:setCoord(0.0, 0.0, 0.0)
    Dragon:setTarget(Dragon.target)
    Dragon:setMovingMode(Dragon.MMODE_VIEW_ABS_LOCKED)
    Dragon:setMovingSpeed(1.0)
    Dragon:setAnimSpeed(2.5)
    Dragon:setEnableLoop(true)

--  Dragon:setMovingState(Dragon.STATE_T_LEFT)
	frontDirection = Dragon:getFrontDirection()
	local backDirection = PNNormal3f:new_local(frontDirection)
	backDirection:multiply(-1)
    Dragon:setTargetDirection(backDirection)
    Dragon:setMovingState(Dragon.STATE_T_RIGHT)

    Dragon:startAnimation(0, 0)
    function Dragon:luaUpdate(deltaTime)
        self:update(deltaTime)
    end
     
    return Dragon
end



