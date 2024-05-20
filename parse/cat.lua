-- (...) are parsers, ie magic fns
-- that expect (file,i)
-- parses only if they parse in sequence
function cat(file, i, ...)
	local parsers = table.pack(...)
	local j = i
	elems = {}
	for _,parser in ipairs(parsers) do
		node = parser(file, j)()
		if node == nil then
			return nil
		end

		table.insert(elems, node)
		j = node.j
	end
	return table.unpack(elems)
end