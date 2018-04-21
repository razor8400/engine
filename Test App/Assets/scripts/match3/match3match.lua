local config = load_script('scripts/match3/match3config.lua')

local match_size = 5

local match3match =  {
	matches = {

	}
}

local function print_match(match)
	local string = ''
	for x = 0, match_size - 1 do 
		string = string .. '\n'
		for y = 1, match_size do
			string = string .. (match[x * match_size + y]) .. ','
		end
	end
	debug_log(string)
end

local function rotate_match(match)
	local m = {}
	for x = 0, match_size - 1 do
		for y = 1, match_size do
			local i = x * match_size + y
			local j = (match_size * match_size) - y * match_size + (x + 1)
			m[i] = match[j]
		end
	end
	return m
end

local function crop_match(match)
	local m = {}
	
	local max_x = 0
	local max_y = 0

	for x = 0, match_size - 1 do
		local w = 0
		for y = 1, match_size do
			if match[x * match_size + y] ~= 0 then
				w = w + 1
			end
		end

		if w > max_x then
			max_x = w
		end
	end

	for x = 1, match_size do
		local h = 0
		for y = 0, match_size - 1 do
			if match[y * match_size + x] ~= 0 then
				h = h + 1
			end
		end

		if h > max_y then
			max_y = h
		end
	end

	return match
end

function match3match:load_config()
	for i = #config, 1, -1 do
		local match = config[i].match
		local rotations = config[i].rotations
		for j = 1, rotations do
			match = rotate_match(match)
			table.insert(self.matches, match)
		end
	end

	for k, v in pairs(self.matches) do
		local match = crop_match(v)
		print_match(match)
	end
end

function match3match:check_match(field, x, y)
	for k, v in pairs(self.matches) do
		for i = 1, match_size do
			for j = 1, match_size do
				local x1 = x - 1 + i
				local y1 = y - 1 + j
				
				--debug_log(x1 .. ',' .. y1)
			end
		end
	end

	return nil
end

function match3match:find_matches(field)
	local matches = {}

	for x = 1, field.colls do
		for y = 1, field.rows do
			if self:check_match(field, x, y) then
				table.insert(match, matches)
			end
		end
	end

	return matches
end

return match3match