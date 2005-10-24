function PN3DCameraClass(myid, target, myisRenderCam)
    local obj = 1
    if (myisRenderCam ~= nil and myisRenderCam == true) then
         pnprint("inherit from rendercam")
        --obj = inheritFrom({className="PN3DCamera", id=myid}, PN3DCamera:getRenderCam(), true)
         obj = PN3DCamera:getRenderCam()
         obj.className="PN3DCamera"
   else
        obj = inheritFrom({className="PN3DCamera", id=myid}, PN3DCamera:new_local(target), true)
    end
    obj.isRenderCam = myisRenderCam
      
    return  obj
end