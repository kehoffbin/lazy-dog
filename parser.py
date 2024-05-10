from dataclasses import dataclass

@dataclass
class Block:
	clauses :list
	end: int

@dataclass 
class Clause:
	# contains blocks or tokens
	elements :list
	end :int

# turns a list of tokens into a block
def parse(_tokens):
	global tokens
	tokens = _tokens

	return Block(get_block(0))

# gets the block starting at token i
def get_block(i):
	pass

# gets the clause starting at token i
def get_clause(i):
	elements = []

	while True:
		# consider end of clause
		if tokens[i].value == '|':
			# if the end of clause was given by the user,
			# end the clause right here
			if tokens[i].token_type == 'symbol':
				return Clause(elements, i)
			
			# so we reached an end of line

			# if the next lines are indented, add them as blocks
			# to the current clause 
			if tokens[i+1].value == '>' and tokens[i+1].token_type == 'spacing':
				elements += get_indent(i)


# turn indented lines into blocks
"""
a
	b
		c
	d
	e
f
== a (b |> c) (d) (e) | f
"""
def get_indent(i):
	blocks = []

	# relative indent
	indent = 0
	
	# the start of the current block/line
	start = i
	j = i
	while True:
		# put the entire line into the block
		while tokens[j].token_type != 'spacing':
			j += 1
		
		# the line should end in an end of line
		if tokens[j].value != '|':
			raise Exception("This should be an end of line")
		j += 1

		# check the indent of the next line
		while tokens[j].token_type == 'spacing':
			if tokens[j].value == '>':
				indent += 1
			if tokens[j].value == '<':
				indent -= 1
		
		# if the indent is positive, we just put the next line
		# into the current block
		if indent > 0:
			continue

		# otherwise, the current block ends
		if indent <= 0:
			# now actually parse it as block
			blocks.append(get_block(start, j))
		
		# mark this as the beginning of the next block
		start = j

		# if the indent is negative,
		# we are done
		if indent < 0:
			return blocks