Performance = {connectors={}}

Performance.widget = guiManager:createWidget()
Performance.mainText = nil

function Performance.buildWidget()
	Performance.widget:loadMainSheet("Performance.layout", "Performance/")
	
	local window = Performance.widget:getWindow("TextBox")
	Performance.mainText = CEGUI.toMultiLineEditbox(window)
	
--	Ember::OgreView::getSingleton().EventStartErisPoll.connect(sigc::mem_fun(*this, &Performance::startErisPolling));
--	Ember::OgreView::getSingleton().EventEndErisPoll.connect(sigc::mem_fun(*this, &Performance::endErisPolling));

	connect(Performance.connectors, emberOgre.EventTerrainManagerCreated, Performance.terrainManagerCreated)
	connect(Performance.connectors, emberOgre.EventMotionManagerCreated, Performance.motionManagerCreated)
	connect(Performance.connectors, emberOgre.EventTerrainManagerDestroyed, Performance.terrainManagerDestroyed)
	connect(Performance.connectors, emberOgre.EventMotionManagerDestroyed, Performance.motionManagerDestroyed)
	
	connect(Performance.connectors, emberServices:getServerService().GotView, Performance.gotView)
	connect(Performance.connectors, emberServices:getServerService().DestroyedView, Performance.destroyedView)
	
	
	connect(Performance.connectors, Performance.widget.EventFrameStarted, Performance.framestarted)
	
	
	Performance.widget:registerConsoleVisibilityToggleCommand("performance")
	Performance.widget:enableCloseButton()
	Performance.widget:hide()
end

function Performance.terrainManagerCreated(terrainManager)
	Performance.terrainManager = terrainManager
end

function Performance.motionManagerCreated(motionManager)
	Performance.motionManager = motionManager
end

function Performance.terrainManagerDestroyed()
	Performance.terrainManager = nil
end

function Performance.motionManagerDestroyed()
	Performance.motionManager = nil
end

function Performance.gotView(view)
	Performance.view = view
end

function Performance.destroyedView()
	Performance.view = nil
end

function Performance.framestarted(timeSinceLastFrame)
	if (Performance.widget:getMainWindow():isVisible()) then
		local statString
		local stats = emberOgre:getRenderWindow():getStatistics()
		
		--statString = "Current FPS: " .. string.format("%i", stats.lastFPS)
		statString = "FPS: " .. string.format("%i", stats.avgFPS)
		statString = statString .. "\nTriangle count: " .. string.format("%i", stats.triangleCount)
		if Performance.view then
			statString = statString .. "\nSightqueue: " .. Performance.view:lookQueueSize()
		end
		if Performance.motionManager then
			local motionInfo = Performance.motionManager:getInfo()
			statString = statString .. "\nAnimated: " .. motionInfo.AnimatedEntities
			statString = statString .. "\nMoving: " .. motionInfo.MovingEntities
		end
		--ss << "Time in eris: " << getAverageErisTime() * 100 << "% \n"
		
		if Performance.terrainManager ~= nil then
			statString = statString .. "\n" .. Performance.terrainManager:getAdapter():getDebugInfo()
		end
	
		Performance.mainText:setText(statString)
	end

end

Performance.buildWidget()

