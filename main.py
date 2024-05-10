from tokenizer import tokenize

with open('test.lzy') as file_stream:
    file = file_stream.read()

tokens = tokenize(file)

for token in tokens:
    print(f"{token.token_type}: {token.value}")