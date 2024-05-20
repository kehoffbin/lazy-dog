-- various helper functions
Help={}

-- concatenate lists l1 and l2
function Help.concat_lists(l1, l2)
	local result = {}
	for i,v in ipairs(l1) do 
		result[i] = v
	end

	for i,v in ipairs(l2) do 
		result[i+#l1] = v
	end

	return result
end

local function print_table_tree(table, prefix)
	if type(table) ~= "table" then
		print(prefix .. tostring(table))
		return
	end
	for i,v in pairs(table) do
		print(prefix .. tostring(i))
		print_table_tree(v, " "..prefix)
	end
end

function Help.print_table(table)
	print_table_tree(table, "")
	print("")
	return table
end

