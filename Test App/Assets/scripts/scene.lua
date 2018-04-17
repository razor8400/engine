

--setmetatable(sprite, game_object);

function scene:start()
	local obj1 = sprite.create("hui.png");
	local obj2 = game_object.create();

	--print(sprite.__index)
	print(obj1)
	print(obj2)
	print(self.obj)

	obj1:set_position(10, 10);
	obj2:set_position(obj1:get_position());
	local position = obj2:get_position();
	print(position)
	print(position.x .. ', ' .. position.y);
	
	--obj1.hui = function()
		--print("HUI")
	--end
	
	--obj1:hui()

	--obj1:set_color(self.obj, self.obj, 4);
	obj1:add_child(obj2);
	self.obj:add_child(obj1)
	print(self)
	--obj1:set_color(0, 0, 0);
end

function scene:update()

end

function scene:stop()

end