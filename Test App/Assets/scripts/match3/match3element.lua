element_type = {
    red = "red", green = "green", blue = "blue", yellow = "yellow", orange = "orange", unknown = "unknown"
}

local match3element = {
	element_type = element_type.unknown,
	cell = nil,
	view = nil
}

match3element.new = function(family)
	local element = {
		element_type = family
	}

	debug_log('[match3element] new element_type:' .. family)

	setmetatable(element, { __index = match3element })

	return element
end

return match3element

