require("tokenize.token")
require("parse.node")
require("help")

local f = assert(io.open("test.he", "rb"))
local file = f:read("*all")
f:close()


file = "a,b,c,d"
local elems = tuple(file, 1)
>> fn(dloop)(parse_name, fn(parse_exact)(","))
>> fn(pr)("elems")

for _,elem in ipairs(elems) do
	print(value(elem, file))
end