function PN3DCameraClass(myid, myisRenderCam)
    local OBJ = 1
    if (myisRenderCam ~= nil and myisRenderCam == true) then
         pnprint("inherit from rendercam")
        --OBJ = inheritFrom({className="PN3DCamera", id=myid}, PN3DCamera:getRenderCam(), true)
         OBJ = PN3DCamera:getRenderCam()
         OBJ.className="PN3DCamera"
   else
        OBJ = inheritFrom({className="PN3DCamera", id=myid}, PN3DCamera:new_local(), true)
    end
    OBJ.isRenderCam = myisRenderCam
      
    return  OBJ
end