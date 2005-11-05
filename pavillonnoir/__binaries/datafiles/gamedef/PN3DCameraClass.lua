function PN3DCameraClass(myid, myisRenderCam)
    local OBJ = nil
    if (myisRenderCam ~= nil and myisRenderCam == true) then
        pnprint("inherit from rendercam")
        OBJ = inheritFrom(PN3DCamera:getRenderCam())
    else
        OBJ = inheritFrom(PN3DCamera:new_local())
    end
    OBJ.className="PN3DCamera"
    OBJ.id = myid
    OBJ.isRenderCam = myisRenderCam
    return  OBJ
end