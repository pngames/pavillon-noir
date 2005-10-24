

local renderCamera = PN3DCamera:getRenderCam()

function renderCamera:onLuaUpdate(deltatime)
	local 
end
	
renderCamera.id = renderCamera:getId()
gameMap.all[renderCamera.id] = renderCamera
gameMap.entities.camera = {}
gameMap.entities.camera[renderCamera.id] = renderCamera
