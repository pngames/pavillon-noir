function PN3DCameraClass(myid, target, myisRenderCam)
    local obj = 0
    if (isRenderCam ~= nil and myisRenderCam == true) then
        obj = inheritFrom({className="PN3DCamera", id=myid}, PN3DCamera:getRenderCam(), true)
    else
        obj = inheritFrom({className="PN3DCamera", id=myid}, PN3DCamera:new_local(target), true)
    end
    obj.isRenderCam = myisRenderCam
    obj.entities = {}
      
    return  obj
end