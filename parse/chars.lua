-- matches a single char if it fulfills pred
function parse_char(file, i, pred)
	if i<file:len() and pred(file:sub(i, i)) then
		return {i = i, j = i+1}
	end
end

-- matches chars while pred holds
function parse_chars(file, i, pred)
	local j = i
	while j<file:len() and pred(file:sub(j, j)) do
		j = j+1
	end

	return {i = i, j = j}
end

function match_regex(str, regex)
	return str:find(regex) ~= nil
end

islower = fn(match_regex)("%l").raw
