-- (...) are parsers, ie magic fns
-- that expect (file,i)
-- parses only if they parse in sequence
function cat(file, i, ...)
	local parsers = table.pack(...)
	local j = i
	elems = {}
	for _,parser in ipairs(parsers) do
		-- defn parser just in case
		node = defn(parser)(file, j)
		if node == nil then
			return nil
		end

		table.insert(elems, node)
		j = node.j
	end
	return table.unpack(elems)
end

-- joins many nodes into one, discarding the arguments
function join(...)
	local nodes = table.pack(...)
	return {
		i = nodes[1].i,
		j = nodes[#nodes].j
	}
end