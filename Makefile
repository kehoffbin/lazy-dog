main: main.hs Parser.hs
	ghc -dynamic main.hs

clean:
	rm main *.hi *.o