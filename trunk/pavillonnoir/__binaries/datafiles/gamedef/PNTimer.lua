function PNTimerClass
    local OBJ = {}

    OBJ.time = 0;
    OBJ.scheduledTasks = {}
    
    function OBJ:onUpdate(deltaTime)
        self.time = self.time + deltaTime
        local id = 1;
        while (id <= table.getn(self.scheduledTasks)) do
            local task = self.scheduledTasks[id]
            if (task.s + task.r >= self.time) then
                task.f(task.e)
                if task.l == true then 
                    task.s = self.time
                else
                    table.remove(self.scheduledTasks, id)
                    id = id-1;
                end
            end
            id = id + 1
        end
        
    end

    function OBJ:addTask(entity, func, remainTime, loop)
        table.insert(self.scheduledTasks, {e=entity, f=func, s=self.time, r=remainTime, l=loop})
    end
end

