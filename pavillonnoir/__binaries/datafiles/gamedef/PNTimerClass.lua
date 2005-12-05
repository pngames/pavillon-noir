function PNTimerClass()
    local OBJ = {}

    OBJ.time = 0
    OBJ.scheduledTasks = {}

    function OBJ:onUpdate(deltaTime)
    	--pnprint("=>Timer:onUpdate\n")
        self.time = self.time + deltaTime
        local id = 0
        while id < table.getn(self.scheduledTasks) do
            local task = self.scheduledTasks[id + 1]
        	--pnprint("taskTime is " .. task.s+task.r .. " and timerTime is " .. self.time .. "\n")
            if (task.s+task.r <= self.time) then
            	--pnprint("found a Task !\n")
                task.e[task.f](task.e, task.p)
                if task.l == true then 
                    task.s = self.time
                else
                    table.remove(self.scheduledTasks, id + 1)
                    id = id-1
                end
            end
            id = id + 1
        end
    	--pnprint("<=Timer:onUpdate\n")
    end

    function OBJ:addTask(entity, func, remainTime, loop, params)
    	--pnprint("=>Timer:addTask\n")
        table.insert(self.scheduledTasks, {e=entity, f=func, s=self.time, r=remainTime, l=loop, p=params})
    	--pnprint("<=Timer:addTask\n")
    end

    return OBJ
end
