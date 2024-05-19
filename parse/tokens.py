from .parse import Parse, Node
from .cat import cat
from .chars import ParseChar, ParseChars

# identifier
class ParseIdent:
	def parse(self, file, i):
		return cat(
			ParseChar(str.islower),
			ParseChars(
				lambda c: c.islower() 	
							or c.isdigit()\
							or c == '_'
			)
		).parse(file, i)

# string literal
class ParseNumLiteral:
	def parse(self, file, i):
		return cat(
			ParseChar(str.isdigit),
			ParseChars(str.isdigit)
		).parse(file, i)
