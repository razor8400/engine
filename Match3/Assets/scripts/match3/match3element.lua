element_type = {
    red = "red", green = "green", blue = "blue", yellow = "yellow", orange = "orange", unknown = "unknown"
}

element_layer = {
	underground = "underground",
	ground = "background",
	gameplay = "gameplay",
	blockers = "blockers",
	top = "top"
}

local elements = {

}

local match3element = {

}

match3element.new = function(family)
	local config = assert(elements[family])

	local element = {
		element_type = config.element_type,
		element_layer = config.element_layer,
		handle_input = config.handle_input,
		droppable = config.droppable,
		cell = nil,
		view = nil,
		path = {}
	}

	setmetatable(element, { __index = match3element })

	return element
end

match3element.load_config = function(config)
	assert(config)

	elements = {}

	for k, v in pairs(config.elements) do
		local element = {}
		element.element_type = v.type
		element.element_layer = v.layer
		element.handle_input = v.handle_input
		element.dropable = v.dropable
		element.texture = v.texture
		elements[v.type] = element
	end
end

function match3element:remove_from_cell()
	if self.cell then
		self.cell:remove_element(self)
	end
end

return match3element

