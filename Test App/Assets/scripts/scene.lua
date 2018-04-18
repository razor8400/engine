
function scene:start()

end

function scene:update()

end

function scene:stop()

end

function scene:mouse_down()
	print(self.mouse.x .. ',' .. self.mouse.y)
end

function scene:mouse_move()
	print(self.mouse.x .. ',' .. self.mouse.y)
end

function scene:mouse_up()
	print(self.mouse.x .. ',' .. self.mouse.y)
end