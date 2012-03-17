--Shows a simple help window when moving an entity.

Mover = {}

function Mover:updateEntityText(entity)
	--if the entity has a name, use it, else use the type name
	--perhaps we should prefix the type name with an "a" or "an"?
	name = ""
	if entity:getName() ~= "" then
		name = entity:getName()
	else
		name = entity:getType():getName()
	end	
	
	local message = Ember.OgreView.Gui.HelpMessage:new_local("Entity Move", "Moving " .. name .. ". Release left mouse button to place, escape to cancel. Pressing and holding shift decreases movement speed. Mouse wheel rotates. Press ctrl to snap to other entities.", "entity move help", "moveMessage")
	Ember.OgreView.Gui.QuickHelp:getSingleton():updateText(message)
end

function Mover:StartMoving(entity, mover)
	Mover:updateEntityText(entity)
end 

function Mover:buildWidget()

	local moveManager = emberOgre:getWorld():getMoveManager()
	
	connect(Mover.connectors, moveManager.EventStartMoving, Mover.StartMoving, self)

end

function Mover:shutdown()
	disconnectAll(self.connectors)
end

connect(connectors, emberOgre.EventWorldCreated, function(world) 
	mover = {connectors={}}
	setmetatable(mover, {__index = Mover})

	mover:buildWidget(world)
	connect(mover.connectors, emberOgre.EventWorldDestroyed, function()
			mover:shutdown()
			mover = nil
		end
	)	
end
)
