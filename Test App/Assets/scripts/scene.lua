

--setmetatable(sprite, game_object);

function scene:start()
	local obj1 = sprite.create();
	local obj2 = sprite.create();

	--print(sprite.__index)
	print(obj1)
	print(obj2)

	obj1:set_color(0, 0, 0);
	obj1:add_child(obj2);
	--obj1:set_color(0, 0, 0);
end

function scene:update()

end

function scene:stop()

end