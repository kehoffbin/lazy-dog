main: main.hs
	ghc -dynamic main.hs

clean:
	rm main *.hi *.o