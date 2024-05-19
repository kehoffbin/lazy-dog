from .parse import Parse, Node

# cats multiple parses together
def cat(*parsers):
	return ParseCat(parsers)

# parses only if all parsers when catted together parse
class ParseCat(Parse):
	def __init__(self, parsers):
		self.parsers = parsers

	def parse(self, file, i):
		start = i
		results = []

		for parser in self.parsers:
			result = parser.parse(file, i)
			if result == None:
				return None

			results.append(result)
			i = result.end
		return Cat(result, start, i, file)

class Cat(Node):
	def __init__(self, nodes, start, end, file):
		Node.__init__(self, start, end, file)
		self.nodes = nodes