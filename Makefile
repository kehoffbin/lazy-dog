main: main.hs Parser.hs Token.hs
	ghc -dynamic main.hs

clean:
	rm main *.hi *.o