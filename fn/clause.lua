parse_clause = fn(loop)(parse_block) | fn(flag)("clause")
parse_block = fn(either)(
	parse_name,
	fn(cat)(
		fn(parse_exact)("("),
		fn(loop)(parse_clause),
		fn(parse_exact)(")")
	)
)