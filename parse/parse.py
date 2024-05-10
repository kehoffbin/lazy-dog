from abc import abstractmethod

# a node in the node tree
# corresponds to a substring of the source file
# indexed by start and end

class Node:
	def __init__(self, start, end, file):
		self.start = start
		self.end = end
		self.file = file	


	# get the value of the substring this node corresponds to
	def value():
		return file[start:end]


# abstract base class
# for concrete sublasses ParseSomeNode
class Parse:

	# returns SomeNode or None
	# where SomeNode extends Node
	# parse file starting at index i
	@abstractmethod
	def parse(self, file, i):
		pass
