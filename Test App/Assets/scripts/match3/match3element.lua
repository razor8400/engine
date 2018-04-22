element_type = {
    red = "red", green = "green", blue = "blue", yellow = "yellow", orange = "orange", unknown = "unknown"
}

element_layer = {
	underground = "underground",
	background = "background",
	gameplay = "gameplay",
	blockers = "blockers",
	top = "top"
}

local match3element = {
	element_type = element_type.unknown,
	element_layer = element_layer.underground,
	cell = nil,
	view = nil
}

match3element.new = function(family, layer)
	local element = {
		element_type = family,
		element_layer = layer
	}

	debug_log('[match3element] new type:' .. element.element_type .. ', ' .. 'layer:' .. element.element_layer)

	setmetatable(element, { __index = match3element })

	return element
end

return match3element

