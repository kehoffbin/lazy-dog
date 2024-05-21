require("help")
function value(node, file)
	return file:sub(node.i, node.j - 1)
end