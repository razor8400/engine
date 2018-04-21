local match3field = load_script('scripts/match3/match3field.lua')
local loader = load_script('scripts/view/match3element_loader.lua')

local colls = 10
local rows = 10
local cell = 64

local field = match3field.new(colls, rows, cell)

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

function match3scene:start()
	local background = create_back_ground()

	field:generate_field()

	for i = 1, colls do
		for j = 1, rows do
			local cell = assert(field:get_cell(i, j))

			for k, v in pairs(cell.elements) do
				local view = assert(loader:load_element(v))
				view:set_position(field:convert_cell_to_world(i, j))
				background:add_child(view)
			end
		end
	end

	self.obj:add_child(background)
end

function match3scene:update()

end

function match3scene:stop()

end

function match3scene:mouse_down()

end

function match3scene:mouse_move()

end

function match3scene:mouse_up()

end
