function islower(c)
	return string.byte(c) >= string.byte("a")
		and string.byte(c) <= string.byte("z")
end

function isupper(c)
	return string.byte(c) >= string.byte("A")
		and string.byte(c) <= string.byte("Z")
end

function isdigit(c)
	return string.byte(c) >= string.byte("0")
		and string.byte(c) <= string.byte("9")
end

-- flags a node to indicate its type
function flag(node, type)
	node.type = type
	return node
end

-- names start with lower, then only contain lower, digits, and _
parse_name = fn(cat)(
	fn(parse_char)(islower),
	fn(parse_chars)(function(c)
		return islower(c) or isdigit(c) or c == "_"
	end)
) | fn(join) | fn(flag)("name")

parse_type_name = fn(cat)(
	fn(parse_char)(isupper),
	fn(parse_char)(function(c)
		return isupper(c) or isdigit(c)
	end)
) | fn(join) | fn(flag)("type_name")
