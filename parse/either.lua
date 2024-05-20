-- (...) are parsers, ie magic fns
-- that expect (file,i)
-- parses if any one of them passes
-- returns the one that passed, with an extra field variant
-- 	indicating which one was it
function either(file, i, ...)
	local parsers = table.pack(...)
	for n,parser in ipairs(parsers) do
		-- try parsing with parser
		local node = fn(parser)(file, i)()
		if node ~= nil then
			node.variant = n
			return node
		end

	end
	-- if none worked, this doesnt work
	return nil
end

-- always passes, parses nothing
function pass(file, i)
	return {i=i, j=i}
end

-- we can use this to define maybe
maybe = fn(either)(pass)