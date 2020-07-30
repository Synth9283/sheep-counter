target := main
flags := -w `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -l SDL2 -l SDL2_mixer

all: $(target)

$(target): $(target).c
	gcc $(flags) $< -o main

clean:
	rm -fv $(target)

