require('match3element')

local colls = 10
local rows = 10
local cell = 64

local field_size = { x = colls * cell, y = rows * cell }
local elements = {}

function convert_cell_to_world(x, y)
	return x * cell - field_size.x / 2, y * cell - field_size.y / 2
end

function get_cell_texture(x, y)
	if math.fmod(x + y, 2) == 0 then
		return "cell-1.png"
	end
	return "cell-0.png"  
end

function match3scene:start()
	local field = game_object.create()
	
	field:set_size(colls * cell, rows * cell)
					print(match3element.red)
			print(match3element[1])
	for i = 0, colls - 1 do
		for j = 0, rows - 1 do
			local texture = get_cell_texture(i, j)
			local sprite = sprite.create(texture)
			local elem = match3element.create()
			
			elem.element_type = match3element[math.random(5)]
			
			table.insert(elements, elem)
						
			sprite:set_anchor()
			sprite:set_position(convert_cell_to_world(i, j))
			field:add_child(sprite)
		end
	end
	
	for k, v in pairs(elements) do
		print(v.element_type)
	end
	
	self.obj:add_child(field)
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