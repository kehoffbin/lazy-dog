require("fn")
require("parse.chars")
require("parse.cat")
require("parse.token")
require("parse.either")

file = "hello world"
function value(node)
	return file:sub(node.i, node.j - 1)
end

return tuple(file, 1) >> fn(maybe)(parse_type_name) >> fn(pr)('type') >> fn(print)
