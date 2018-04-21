local match3cell = load_script('scripts/match3/match3cell.lua')
local match3generator = load_script('scripts/match3/match3generator.lua')
local match3match = load_script('scripts/match3/match3match.lua')

local match3field = {
	colls = 0,
	rows = 0,
	cell = 0,
	cells = {}
}

function match3field:get_cell(x, y)
	if x >= 1 and x <= self.colls and y >= 1 and y <= self.rows then
		return self.cells[(y - 1) * self.colls + x]
	end

	return nil
end

function match3field:size()
	return { x = self.colls * self.cell, y = self.rows * self.cell }
end

function match3field:convert_cell_to_world(x, y)
	local size = self:size()
	return (x - 1) * self.cell - size.x / 2 + self.cell / 2, (y - 1) * self.cell - size.y / 2 + self.cell / 2
end

function match3field:generate_field()
	match3match:load_config()

	for x = 1, self.colls do
		for y = 1, self.rows do
			local cell = assert(self:get_cell(x, y))
			local element = nil

			repeat
				if element ~= nil then
					cell:remove_element(element)
				end
				element = assert(match3generator:generate_element())
				cell:add_element(element)
				local match = match3match:check_match(self, x, y)
			until match3match:check_match(self, x, y) == nil
		end
	end
end

function match3field.new(colls, rows, cell)
	local field = {}

	debug_log('[match3field] new rows:' .. rows .. ',' .. 'colls:' .. colls)

	field.colls = colls
	field.rows = rows
	field.cell = cell
	field.cells = {}
	
	setmetatable(field, { __index = match3field })

	for i = 1, colls do
		for j = 1, rows do
			local cell = match3cell.new(j, i)
			cell.field = field
			table.insert(field.cells, cell)
			assert(field:get_cell(j, i))
		end
	end

	return field
end

return match3field