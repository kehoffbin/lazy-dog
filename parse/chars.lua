-- matches a single char if it fulfills pred
function parse_char(file, i, pred)
	pred = defn(pred)
	if i<=file:len() and pred(file:sub(i, i)) then
		return {i = i, j = i+1}
	end
end

-- matches chars while pred holds
function parse_chars(file, i, pred)
	pred = defn(pred)
	local j = i
	while j<=file:len() and pred(file:sub(j, j)) do
		j = j+1
	end

	return {i = i, j = j}
end

-- matches chars while pred holds
-- need at least one matching char
function parse_char_s(file, i, pred)
	local node = parse_chars(file, i, pred)

	if node.i == node.j then
		return nil
	end

	return node
end