require("fn")
require("parse.chars")
require("parse.cat")
require("parse.token")

file = "hello world"
function value(node)
	return file:sub(node.i, node.j - 1)
end

return tuple(file, 1) >> fn(parse_name) >> fn(value) >> fn(print)
