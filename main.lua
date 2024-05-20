require("parse.token")
require("help")

local f = assert(io.open("test.lzy", "rb"))
local file = f:read("*all")
f:close()

function value(node)
	return file:sub(node.i, node.j - 1)
end

tokens = tuple(file, 1) >> fn(loop)(parse_token)
for _, token in ipairs(tokens.elems) do
	print(token.type, value(token))
end
