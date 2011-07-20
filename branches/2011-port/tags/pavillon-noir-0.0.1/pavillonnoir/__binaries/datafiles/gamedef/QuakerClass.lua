function QuakerClass()
    pnprint("Quaker creating\n")
    Quaker = PN3DObjectClass()
    Quaker.className = "QuakerClass"
    --Quaker.__index = Quaker
    Quaker:setMovingSpeed(1.0)
    Quaker:setMovingState(Quaker.STATE_T_FORWARD)

    -- Make the Object Quake
    function Quaker:luaUpdate(deltaTime)
       mov_state = self:getMovingState()
       if mov_state == self.STATE_T_FORWARD then
         self:setMovingState(self.STATE_T_BACKWARD)
       else
         self:setMovingState(self.STATE_T_FORWARD)
       end
       --pnprint("before Quaker update\n")
       self:update(3)
       --pnprint("after Quaker update\n")
    end

    pnprint("Quaker created\n") 
    return Quaker
end
