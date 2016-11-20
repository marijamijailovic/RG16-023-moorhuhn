moorhuhn: main.c
	gcc main.c -o moorhuhn -lGL -lGLU -lglut -Wall -lm -g

clean:
	rm main
	rm *.0
	rm *~
