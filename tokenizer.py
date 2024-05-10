from dataclasses import dataclass

@dataclass
class Token:
    token_type :str
    value :str
    start :int
    end :int
    line :int

    @staticmethod
    def spacing(value, line):
        return Token("spacing", value, -1, -1, line)
    
    def is_symbol(_value):
        return token_type == 'symbol' and value == _value

    def is_spacing(_value):
        return token_type == 'symbol' and value == _value

# convert a file string into a list of tokens
def tokenize(file):
    return tokenize_lines(file.split('\n'))

def tokenize_lines(lines):
    tokens = []
    last_indent = 0

    for i, line in enumerate(lines):
        # ignore empty lines or commented out lines
        if line.strip() == '' or line.lstrip().startswith('#'):
            continue

        # add indent tokens if necessary
        our_indent = indent(line)
        if our_indent > last_indent:
            tokens += [Token.spacing(">", line)]*(our_indent - last_indent)
        if our_indent < last_indent:
            tokens += [Token.spacing("<", line)]*(last_indent - our_indent)        
        last_indent = our_indent

        # add tokens of the line
        tokens += tokenize_line(i, line)

        # add eol token
        tokens.append(Token.spacing("|", i))

    return tokens

# calculates tab indent of line
def indent(line):
    for i in range(len(line)):
        if line[i] != '\t':
            return i
    return len(line)


def tokenize_line(i, line):
    tokens = []

    j = 0
    while True:
        # get the next token
        # add an extra space for safety
        token = next_token(j, line + " ")

        # stop if there are no more tokens
        if token == None:
            break

        # set the line number
        token.line = i

        # continue at the end of the token
        j = token.end
        tokens.append(token)
    return tokens


# returns the next Token starting at position i
def next_token(j, line):
    # skip whitespace
    # an index error means we reached the end of the line
    try:
        j = scan_whitespace(j, line)
    except IndexError:
        return None

    # check for each token type,
    # whether we found a token
    for token_type in ["ident", "type_ident", "string", "num", "symbol"]:
        # call scan_token_type method
        end = globals()["scan_"+token_type](j, line)
        
        if end == j:
            continue

        return Token(token_type, line[j:end], j, end, -1)
    raise Exception(f"unexpected character: {line[j]}")

def scan_whitespace(j, line):
    while line[j] in [' ', '\n', '\t']:
        j += 1
    return j

def scan_ident(j, line):
    if not line[j].islower():
        return j

    while line[j].islower() or line[j].isdigit() \
                            or line[j] == '_':
        j += 1
    return j

def scan_type_ident(j, line):
    if not line[j].isupper():
        return j

    while line[j].isalnum():
        j += 1
    return j

def scan_string(j, line):
    if line[j] != '\"':
        return j
    j += 1
    while line[j] != '\"':
        j += 1
    return j+1

symbol_chars = "!$%&'()*+,-./:;<=>?@[\\]^_{|}~"

def scan_symbol(j, line):
    while line[j] in symbol_chars:
        j += 1
    return j

def scan_num(j, line):
    while line[j].isdigit():
        j += 1
    return j


