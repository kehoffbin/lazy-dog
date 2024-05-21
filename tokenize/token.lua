require("fn.fn")
require('parse.cat')
require('parse.either')
require('parse.loop')
require('parse.node')
require('tokenize.chars')

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

-- turns string into dictionary with each character set to true
local function dictify(str)
	local dict = {}
	for i = 1,str:len() do
		dict[str:sub(i,i)] = true
	end
	return dict
end

local sociable_symbols = dictify(".'!#$%&\\*+-/:;<=>?@[]^_`|~")
local solitary_symbols = dictify("()[]{},")

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

-- type names start with upper, then only contain alnums
parse_type_name = fn(cat)(
	fn(parse_char)(isupper),
	fn(parse_chars)(function(c)
		return isupper(c) or islower(c) or isdigit(c)
	end)
) | fn(join) | fn(flag)("type_name")

parse_symbol = fn(either)(
	fn(parse_char)(fn(lookup)(solitary_symbols)),
	fn(parse_char_s)(fn(lookup)(sociable_symbols))
) | fn(flag)("symbol")

parse_num = fn(parse_char_s)(isdigit) | fn(flag)("num")

parse_white_gap = fn(parse_chars)(function (c)
	return c == " " or c == "\t" or c == "\n"
end) | fn(flag)("white_gap")

parse_token = fn(cat)(
	parse_white_gap,
	fn(either)(parse_name, parse_type_name, parse_symbol, parse_num)
) | fn(table.pack) | fn(pr)(2)

-- parses if the next token matches x exactly
function parse_exact(file, i, x)
	local node = fn(parse_token)(file, i)()
	if node ~= nil and value(node, file) == x then
		return node
	end

	return nil
end
