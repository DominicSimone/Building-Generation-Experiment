
default: clean
	gcc *.c

clean: 
	@rm -f a.out

run: default
	./a.out

mem: default
	valgrind ./a.out
