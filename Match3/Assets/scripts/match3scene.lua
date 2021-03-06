local match3field = load_script('scripts/match3/match3field.lua')

local swipe = 0.2
local drop = 0.2
local destroy = 0.2

local field = nil
local atlas = "textures.json"
local elements_config = "configs/elements.json"
local matches_config = "configs/matches.json"

local function get_background_texture(x, y)
	if math.fmod(x + y, 2) == 0 then
		return "cell-1.png"
	end
	return "cell-0.png"
end

local function create_background()
    local obj = game_object.create();
	local size = field:size()
	
	obj:set_size(size)

	for i = 1, field.colls do
		for j = 1, field.rows do
			local cell = assert(field:get_cell(i, j))

			if not cell.disabled then
				local texture = get_background_texture(i, j)
				local sprite = sprite.create(atlas, texture)
					
				sprite:set_position(field:convert_cell_to_world(i, j))
				obj:add_child(sprite)
			end
		end
	end
	
	return obj
end

function match3scene:on_touch_began()
	if self.dispatch_events then
		return false
	end

	local mouse = game.get_world_mouse_location()

	if self.collider:on_click(mouse) then
		local location = self.obj:global_to_local(mouse)
		local cell = field:convert_world_to_cell(location.x, location.y)

		self.selected = field:get_element(cell.x, cell.y, element_layer.gameplay)
		return true
	end

	return false
end

function match3scene:on_touch_ended()
	self.selected = nil
end

function match3scene:on_touch_moved()
	if self.selected then
		local mouse = game:get_world_mouse_location()
		local location = self.obj:global_to_local(mouse)
		local to = field:convert_world_to_cell(location.x, location.y)
		local selected = self.selected
		
		local dx = to.x - selected.cell.x
		local dy = to.y - selected.cell.y

		if math.abs(dx + dy) == 1 then
			local target = field:get_element(to.x, to.y, element_layer.gameplay)
			if target then
				local from = selected.cell:tile()
				local list = action_list.create()

				list:append(targeted_action.create(selected.view, action_move.move_to(field:convert_cell_to_world(to.x, to.y), swipe)))
				list:append(targeted_action.create(target.view, action_move.move_to(field:convert_cell_to_world(from.x, from.y), swipe)))
				
				local sequence = action_sequence.create()

				sequence:append(list)
				sequence:append(action_lua_callback.create(function()
					if field:swipe(from, to) then
						field:process()
					else
						local list = action_list.create()

						list:append(targeted_action.create(selected.view, action_move.move_to(field:convert_cell_to_world(from.x, from.y), swipe)))		
						list:append(targeted_action.create(target.view, action_move.move_to(field:convert_cell_to_world(to.x, to.y), swipe)))
						
						selected.view:add_component(list)
					end
				end))

				selected.view:add_component(sequence)
				self.selected = nil
			end
		end
	end
end

function match3scene:start()
    debug_log('match3scene:start()')

	field = assert(match3field.new())
	field.delegate = self

	field:load_matches(json.parse(read_file(matches_config)))
	field:load_elements(json.parse(read_file(elements_config)))
	field:load(json.parse(self.data))
	
	field:generate_field()
	field:process()

    local background = create_background()

	local size = background:get_size()
	local collider = box_collider2d.create(size.x, size.y)

	self.collider = collider
	self.batch = background
	
	self.obj:set_size(size)
	self.obj:set_position(-size.x / 2, -size.y / 2)
	self.obj:add_child(background)
	self.obj:add_component(collider)

	self.dispatch_events = false
	self.actions = {}
	self.current_action = 1
end

function match3scene:update()
	field:update()
end

function match3scene:stop()

end

function match3scene:handle_events(events)
	local action_destroy = action_list.create()
	local action_generate = action_list.create()
	local action_drop = action_list.create()

	for k, v in pairs(events) do
		if v.event == event_destroy.event then
			action_destroy:append(action_sequence.create(action_delay.create(destroy),
															action_lua_callback.create(function()
																local view = assert(v.element.view)
																view:remove_from_parent()
															end)))
		end
	end

	for k, v in pairs(events) do
		if v.event == event_generate.event then
			local view = assert(sprite.create(atlas, v.element.texture))
			local sequence = action_sequence.create()

			view:set_position(field:convert_cell_to_world(v.x, v.y))
			view:set_enabled(false)
			
			v.element.view = view

			sequence:append(action_delay.create(v.tick * drop))
			sequence:append(action_lua_callback.create(function()
				view:set_enabled(true)
			end))

			self.batch:add_child(view)
			
			action_generate:append(sequence)
		end
	end

	for k, v in pairs(events) do
		if v.event == event_drop.event then
			local sequence = action_sequence.create()
			local view = assert(v.element.view)

			for k1, v1 in pairs(v.path) do
				sequence:append(targeted_action.create(view, action_move.move_to(field:convert_cell_to_world(v1.x, v1.y), drop)))
			end

			action_drop:append(sequence)
		end
	end

	table.insert(self.actions, action_sequence.create(action_destroy, 
														action_generate, 
														action_drop, 
														action_lua_callback.create(function()
															self:on_events_finished()
														end)))
	self:run_events()
end

function match3scene:run_events()
	if not self.dispatch_events then
		self.current_action = 1
		self.dispatch_events = true
		self:run_next_events()
	end
end

function match3scene:run_next_events()
	local action = self.actions[self.current_action]
	self.obj:add_component(action)
end

function match3scene:on_events_finished()
	self.current_action = self.current_action + 1
	if self.current_action > #self.actions then
		self.actions = {}
		self.dispatch_events = false
	else
		self:run_next_events()
	end
end
