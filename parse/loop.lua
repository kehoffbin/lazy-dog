require("help")

-- parses while parser passes
-- nodes are saved in elems
function loop(file, i, parser)
	local j = i
	local elems = {}
	while true do
		local node = fn(parser)(file, j)()
		Help.print_table(node)
		if node == nil then
			return {i = i, j = j, elems = elems}
		end

		table.insert(elems, node)
		j = node.j
	end
end


function dloop(file, i, parser, delim_parser)
	local first, rest = fn(cat)(
		parser,
		fn(loop)(fn(cat)(delim_parser, parser))
	)(file, i)()

	-- if the first element is none, return an empty list 
	if first.variant == 2 then
		return {i=i, j=i, elems={}}
	end

	-- otherwise, it is our first element
	local elems = {first}

	-- now deal with the remaining ones
	for _,elem in ipairs(rest.elems) do
		table.insert(elems, elem[2])
	end

	return {
		i=i,
		j=elems[#elems].j,
		elems = elems
	}
end