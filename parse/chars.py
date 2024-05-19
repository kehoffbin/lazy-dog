from .parse import Parse, Node

# matches a single character iff it fulfills pred
class ParseChar(Parse):
	def __init__(self, pred):
		self.pred = pred


	def parse(self, file, i):
		if i < len(file) and self.pred(file[i]):
			return Node(i, i+1, file)
		else:
			return None

# matches characters while pred is true
class ParseChars(Parse):
	def __init__(self, pred):
		self.pred = pred


	def parse(self, file, i):
		start = i
		while i < len(file) and self.pred(file[i]):
			i += 1
		
		return Node(start, i, file)