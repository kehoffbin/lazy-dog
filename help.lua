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

function print_table(table)
	for i,v in pairs(table) do
		print(i, v)
	end
end