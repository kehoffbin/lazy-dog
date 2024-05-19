require("fn")
require("parse.chars")

file = "hello world"
function value(node)
	return file:sub(node.i, node.j - 1)
end


return tuple(file,1)
	>> fn(parse_chars)(islower)
	>> fn(value)
	>> fn(print)