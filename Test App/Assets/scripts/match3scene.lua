local match3field = load_script('scripts/match3/match3field.lua')
local loader = load_script('scripts/view/match3element_loader.lua')

local colls = 10
local rows = 10
local cell = 64

local field = match3field.new(colls, rows, cell)
local bounds = { -field:size().x / 2, - field:size().y / 2, field:size().x / 2, field:size().y / 2 }

local function get_cell_texture(x, y)
	if math.fmod(x + y, 2) == 0 then
		return "cell-1.png"
	end
	return "cell-0.png"  
end

local function create_back_ground()
	local obj = game_object.create()

	obj:set_size(field:size())

	for i = 1, colls do
		for j = 1, rows do
			local texture = get_cell_texture(i, j)
			local sprite = sprite.create(texture)
						
			sprite:set_position(field:convert_cell_to_world(i, j))
			obj:add_child(sprite)
		end
	end

	return obj
end

function match3scene:on_touch_began()
	local mouse = game:get_world_mouse_location()
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

				list:append(targeted_action.create(selected.view, action_move.move_to(field:convert_cell_to_world(to.x, to.y), 0.3)))
				list:append(targeted_action.create(target.view, action_move.move_to(field:convert_cell_to_world(from.x, from.y), 0.3)))
				
				local sequence = action_sequence.create()

				sequence:append(list)
				sequence:append(action_lua_callback.create(function()
					if field:swipe(from, to) then
						
					else
						local list = action_list.create()

						list:append(targeted_action.create(selected.view, action_move.move_to(field:convert_cell_to_world(from.x, from.y), 0.3)))		
						list:append(targeted_action.create(target.view, action_move.move_to(field:convert_cell_to_world(to.x, to.y), 0.3)))
						
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
	local background = create_back_ground()

	field:generate_field()

	for i = 1, colls do
		for j = 1, rows do
			local cell = assert(field:get_cell(i, j))

			for k, v in pairs(cell.elements) do
				local view = assert(loader:load_element(v))
				view:set_position(field:convert_cell_to_world(cell.x, cell.y))
				background:add_child(view)
			end
		end
	end

	local size = background:get_size()
	local collider = box_collider2d.create(size.x, size.y)

	self.collider = collider

	self.obj:set_size(size)
	self.obj:set_position(-size.x / 2, -size.y / 2)
	self.obj:add_child(background)
	self.obj:add_component(collider)
end

function match3scene:update()

end

function match3scene:stop()

end

