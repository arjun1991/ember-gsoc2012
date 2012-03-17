-- -----------------------------------------
-- Start of handler functions
-----------------------------------------

-----------------------------------------
-- Script Entry Point
-----------------------------------------

ServerLogger = {connectors={}}


ServerLogger.widget = guiManager:createWidget()

function ServerLogger.buildWidget()
	
	ServerLogger.widget:loadMainSheet("ServerLogger.layout", "ServerLogger/")
	
	--set up some useful values
	ServerLogger.logTextWidget = ServerLogger.widget:getWindow("LogText")
	
	--subscribe event
	
	ServerLogger.widget:registerConsoleVisibilityToggleCommand("serverLogger")
	ServerLogger.widget:enableCloseButton()
	ServerLogger.widget:hide()

end

function ServerLogger.server_SendingObject(obj)
	local newLogMessage = "Sending: " .. Ember.OgreView.Gui.AtlasHelper:serialize(obj, "bach") .. "\n"
	
	log.info(newLogMessage)

	ServerLogger.logTextWidget:setText(ServerLogger.logTextWidget:getText() .. newLogMessage)
end

function ServerLogger.server_ReceivedObject(obj)
	local newLogMessage = "Received: " .. Ember.OgreView.Gui.AtlasHelper:serialize(obj, "bach") .. "\n"

	log.info(newLogMessage)

	ServerLogger.logTextWidget:setText(ServerLogger.logTextWidget:getText() .. newLogMessage)

end

function ServerLogger.ClearButton_Clicked(args)
	ServerLogger.logTextWidget:setText("")
end

function ServerLogger.LoggingEnabled_CheckStateChanged(args)
	local checkBox = CEGUI.toCheckbox(ServerLogger.widget:getWindow("LoggingEnabled"))
	if checkBox ~= nil then
		ServerLogger.cleanup()
		if checkBox:isSelected() then
			ServerLogger.sendingConnection = createConnector(emberServices:getServerService().EventSendingObject)
			ServerLogger.sendingConnection:connect(ServerLogger.server_SendingObject)
			ServerLogger.receivedConnection = createConnector(emberServices:getServerService().EventReceivedObject)
			ServerLogger.receivedConnection:connect(ServerLogger.server_ReceivedObject)
		end
	end
	return true
end

function ServerLogger.cleanup()
	if ServerLogger.sendingConnection ~= nil then
		ServerLogger.sendingConnection:disconnect()
		ServerLogger.sendingConnection = nil
	end
	if ServerLogger.receivedConnection ~= nil then
		ServerLogger.receivedConnection:disconnect()
		ServerLogger.receivedConnection = nil
	end
end

ServerLogger.buildWidget()