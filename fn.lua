-- puts functions into tables
-- to allow metatable magic
require("help")

-- our metatable
Fn = {}

-- turns regular boring old function into magical function
function fn(f)
	-- if f is already magical, do nothing
	if getmetatable(f) == Fn then
		return f
	end

	-- if f is not a function,
	-- make it a constant function
	if type(f) ~= "function" then
		local x = f
		f = function()
			return x
		end
	end

	-- otherwise, turn it into a table
	-- and set the appropriate metatable
	local f = {raw=f}
	setmetatable(f, Fn)
	return f
end

-- turns arguments into a tuple
-- a tuple is just a list with .is_tuple = true
function tuple(...)
	local t = table.pack(...)
	t.is_tuple = true
	return t
end

-- checks if a value is a tuple
function is_tuple(t)
	return type(t)=="table" and t.is_tuple
end

-- make post call syntax possible
-- ie x >> fn(f) is f(x)
function Fn.__shr(args, f)
	-- tupleize args if necessary
	if not is_tuple(args) then
		args = tuple(args)
	end

	-- untupleize args
	return f.raw(table.unpack(args))
end

-- bind values to f
-- ie fn(f)(x) is the function y => f(x,y)
function Fn.__call(f, ...)
	local args1 = table.pack(...)
	-- if no arguments were provided, evaluate f instead
	if args1.n == 0 then
		return f.raw()
	end

	return function(...)
			local args2 = table.pack(...)
			local args = Help.concat_lists(args2, args1)
			return f.raw(table.unpack(args))
	end >> fn(fn)
end

function id(...)
	return ...
end
