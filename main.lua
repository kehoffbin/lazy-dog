require("fn")
require("parse.chars")
require("parse.cat")

file = "hello world"
function value(node)
	return file:sub(node.i, node.j - 1)
end

_,_,a = fn(cat)(
		fn(parse_chars)(fn(matches)("%l").raw),
		fn(parse_chars)(fn(matches)(" ").raw),
		fn(parse_chars)(fn(matches)("%l").raw)
	)(file,1)()

_,_,b = just(
	tuple(file, 1)
	>> fn(cat)(
		fn(parse_chars)(fn(matches)("%l").raw),
		fn(parse_chars)(fn(matches)(" ").raw),
		fn(parse_chars)(fn(matches)("%l").raw)
	)
)