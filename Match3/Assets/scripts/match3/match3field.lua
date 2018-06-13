local match3cell = load_script('scripts/match3/match3cell.lua')
local match3generator = load_script('scripts/match3/match3generator.lua')
local match3match = load_script('scripts/match3/match3match.lua')

event_generate = {
	event = "generate"
}

event_generate.new = function(element, x, y, tick)
	local e = {
		element = element,
		x = x,
		y = y,
		tick = tick
	}

	setmetatable(e, { __index = event_generate })

	return e
end

event_destroy = {
	event = "destroy"
}

event_destroy.new = function(element)
	local e = {
		element = element,
	}

	setmetatable(e, { __index = event_destroy })
	
	return e
end

event_drop = {
	event = "drop"
}

event_drop.new = function(element)
	local e = {
		element = element,
		path = {}
	}

	setmetatable(e, { __index = event_drop })

	return e
end

local match3field = {
	colls = 0,
	rows = 0,
	cell = 0,
	cells = {},
	delegate = nil
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

function match3field:generate_element(cell)
	local element = nil

	repeat
		if element ~= nil then
			cell:remove_element(element)
		end
		element = assert(match3generator:generate_element())
		cell:add_element(element)
	until match3match:find_match(self, cell.x, cell.y) == nil

	return element
end

function match3field:load_elements(elements)
	debug_log('[match3field] load_elements')

	match3generator:load_elements(elements)
end

function match3field:load_matches(matches)
	debug_log('[match3field] load_matches')

	match3match:load_matches(matches)
end

function match3field:load(data)
	assert(data)

	debug_log('[match3field] load rows:' .. data.rows .. ',' .. 'colls:' .. data.colls .. ',' .. 'cell:' .. data.cell)

	self.rows = data.rows
	self.colls = data.colls
	self.cell = data.cell

	for i = 1, data.colls do
		for j = 1, data.rows do
			local cell = match3cell.new(j, i)
			cell.field = self
			table.insert(self.cells, cell)
		end
	end

	for i = 1, #data.cells do
		local cell = assert(self.cells[i])
		local elements = data.cells[i].elements

		cell.disabled = data.cells[i].disabled
		cell.generate_elements = data.cells[i].spawn

		if elements then
			for k, v in pairs(elements) do
				local element = assert(match3generator:create_element(v))
				cell:add_element(element)
				self:add_event(event_generate.new(element, cell.x, cell.y))
			end
		end
	end

	self.send_events = true
end

function match3field:generate_field()
	for x = self.colls, 1, -1 do
		for y = self.rows, 1, -1 do
			local cell = assert(self:get_cell(x, y))

			if not cell.disabled and cell:get_element_at(element_layer.gameplay) == nil then
				local element = self:generate_element(cell)
				self:add_event(event_generate.new(element, x, y))
			end
		end
	end

	self.send_events = true
end

function match3field:swipe(a, b)
	local cell1 = assert(self:get_cell(a.x, a.y))
	local cell2 = assert(self:get_cell(b.x, b.y))

	local el1 = cell1:get_element_at(element_layer.gameplay)
	local el2 = cell2:get_element_at(element_layer.gameplay)

	local function do_swipe(el1, el2)
		el1:remove_from_cell()
		el2:remove_from_cell()

		cell1:add_element(el2)
		cell2:add_element(el1)
	end

	if el1 and el2 then
		do_swipe(el1, el2)

		if match3match:find_match(self, a.x, a.y) ~= nil or match3match:find_match(self, b.x, b.y) ~= nil then
			return true
		end

		do_swipe(el2, el1)
	end
	return false
end

function match3field:add_event(e)
	table.insert(self.events, e)
end

function match3field:events_count()
	return #self.events
end

function update_field(field)
	local drop_events = {}
	local ticks = {}

	local function on_drop_element(element, x, y)
		local e = drop_events[element]
		
		if not e then
			e = event_drop.new(element)
			field:add_event(e)
			events[element] = e
		end

		table.insert(e.path, { x = x, y = y })
		field.field_changed = true
	end

	local function drop_diagonal(x, y)
		for i = y, field.rows - 1 do
			local cell = assert(field:get_cell(x, i))

			if cell:drop_elements() then
				return false
			end

			if cell:blocked() then
				return true
			end
		end

		return false
	end

	local function find_target_cell(x, y)
		local top = field:get_cell(x, y + 1)

		if top and top:drop_elements() then
			return top
		end

		if drop_diagonal(x, y) then
			local cells = { { -1, 1 }, { 1, 1 } }

			for k, v in pairs(cells) do
				local target = field:get_cell(x + v[1], y + v[2])

				if target and target:drop_elements() then
					return target
				end
			end
		end

		return nil
	end

	local function drop_element(cell)
		if cell.disabled or cell:blocked() or cell:get_element_at(element_layer.gameplay) ~= nil then
			return false
		end

		local target = find_target_cell(cell.x, cell.y)

		if target then
			local element = assert(target:get_element_at(element_layer.gameplay))

			cell:add_element(element)
			on_drop_element(element, cell.x, cell.y)

			return true
		end

		return false
	end

	for x = 1, field.colls do
		repeat
			local drop_elements = false

			for y = 1, field.rows do
				local cell = assert(field:get_cell(x, y))

				if drop_element(cell) then
					drop_elements = true
				end

				if cell.generate_elements and cell:get_element_at(element_layer.gameplay) == nil then
					local element = field:generate_element(cell)
					local tick = ticks[target] or 0

					ticks[target] = tick + 1

					drop_elements = true

					field:add_event(event_generate.new(element, x, y + 1, tick))
					on_drop_element(element, x, y)
				end
			end
		until drop_elements

		coroutine.yield()
	end

	field.send_events = true
end

function match3field:process()
	self.field_changed = false

	local find_callback = function(matches)
		for k, v in pairs(matches) do
			for k1, v1 in pairs(v) do
				v1:remove_from_cell()
				
				self:add_event(event_destroy.new(v1))
			end
		end
		
		self.field_changed = #matches > 0	
	end

	local finish_callback = function()
		self.update_thread = coroutine.create(update_field)
	end

	self.process_thread = coroutine.create(function()
		repeat
			self.field_changed = false
			match3match:find_matches(self, find_callback, finish_callback)

			coroutine.yield()
		until not self.field_changed

		self.process_thread = nil
	end)
	
	coroutine.resume(self.process_thread)
end

function match3field:update()
	match3match:update()

	if self.update_thread then
		coroutine.resume(self.update_thread, self)
	end

	if self.send_events then
		if self.delegate then
			self.delegate:handle_events(self.events)
		end

		self.send_events = false
		self.events = {}
		self.update_thread = nil

		if self.process_thread then
			coroutine.resume(self.process_thread)
		end
	end
end

function match3field.new()
	local field = {}

	debug_log('[match3field] create field')

	field.colls = 0
	field.rows = 0
	field.cell = 0
	field.cells = {}
	field.events = {}
	field.send_events = false
	
	setmetatable(field, { __index = match3field })

	return field
end

return match3field