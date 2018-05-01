local match3cell = load_script('scripts/match3/match3cell.lua')
local match3generator = load_script('scripts/match3/match3generator.lua')
local match3match = load_script('scripts/match3/match3match.lua')

local match3field = {
	colls = 0,
	rows = 0,
	cell = 0,
	cells = {}
}

local function round(x)
	return math.ceil(x)
end

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
	return { x = (x - 1) * self.cell, y = (y - 1) * self.cell }
end

function match3field:convert_world_to_cell(x, y)
	return { x = round(x / self.cell), y = round(y / self.cell) }
end

function match3field:get_element(x, y, layer)
	local cell = self:get_cell(x, y)
	if cell then
		return cell:get_element_at(layer)
	end
	return nil
end

function match3field:generate_field()
	match3match:load_config()

	for x = self.colls, 1, -1 do
		for y = self.rows, 1, -1 do
			local cell = assert(self:get_cell(x, y))
			local element = nil

			repeat
				if element ~= nil then
					cell:remove_element(element)
				end
				element = assert(match3generator:generate_element())
				cell:add_element(element)
			until match3match:check_match(self, x, y) == nil
		end
	end
end

function match3field:swipe(a, b)
	local cell1 = assert(self:get_cell(a.x, a.y))
	local cell2 = assert(self:get_cell(b.x, b.y))

	local el1 = cell1:get_element_at(element_layer.gameplay)
	local el2 = cell2:get_element_at(element_layer.gameplay)

	if el1 and el2 then
		cell1:add_element(el2)
		cell2:add_element(el1)

		if match3match:check_match(self, a.x, a.y) ~= nil or match3match:check_match(self, b.x, b.y) ~= nil then
			return true
		end

		cell1:add_element(el1)
		cell2:add_element(el2)
	end
	return false
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