
local match3cell =  {
	x = 0,
	y = 0,
	field = nil,
	elements = nil
}

function match3cell:element_index(element)
	for k, v in pairs(self.elements) do
		if v == element then
			return k
		end
	end
	return -1
end

function match3cell:add_element(element)
	element.cell = self
	table.insert(self.elements, element)
end

function match3cell:remove_element(element)
	local index = self:element_index(element)

	element.cell = nil
	table.remove(self.elements, index)
end

function match3cell.new(x, y)
	local cell = {
		x = x, y = y,
		elements = {}
	}

	debug_log('[match3cell] new x:' .. x .. ',' .. 'y:' .. y)

	setmetatable(cell, { __index = match3cell })

	return cell
end

return match3cell