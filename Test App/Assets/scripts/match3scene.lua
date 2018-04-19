
local colls = 10
local rows = 10
local cell = 64

local field_size = { x = colls * cell, y = rows * cell }

function convert_cell_to_world(x, y)
	return x * cell - field_size.x / 2, y * cell - field_size.y / 2
end

function match3scene:start()
	local field = game_object.create()
	
	field:set_size(colls * cell, rows * cell)
	
	for i = 0, colls - 1 do
		for j = 0, rows - 1 do
			local texture = "cell-0.png"  
			
			if math.fmod(i + j, 2) == 0 then
				texture = "cell-1.png"
			end
			
			local sprite = sprite.create(texture)
			sprite:set_anchor()
			sprite:set_position(convert_cell_to_world(i, j))
			field:add_child(sprite)
		end
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