from parse.chars import ParseChar

print(ParseChar( lambda c: c.isalnum()).parse("hello world", 0))