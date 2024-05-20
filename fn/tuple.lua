-- a tuple is a list with the property is_tuple set to true

-- checks if a value is a tuple
function is_tuple(t)
	return type(t)=="table" and t.is_tuple == true
end

-- turns args into tuple via
-- case 1: tuple(a, b, ...) = [a, b, ...]
-- case 2: tuple(a) = a
function tuple(...)
	local args = table.pack(...)
	-- case 1
	if args.n ~= 1 then
		args.is_tuple = true
		return args
	end

	return args[1]
end

-- detupleizes by
-- case 1: just(a, b, ...) = a, b, ...
-- case 2: just([a, b, ...]) = a, b, ...
-- case 3: just(a) = a
function just(...)
	-- pack the args so that we can get their number
	local args = table.pack(...)
	-- case 1
	if args.n ~= 1 then
		return table.unpack(args)
	end

	-- focus on just the only one
	local x = args[1]

	-- case 2
	if is_tuple(x) then
		return table.unpack(x)
	end

	-- case 3
	return x
end