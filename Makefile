default: clean
	gcc *.c

clean: 
	@rm -f a.out
	@rm -f out

run: default
	./a.out

mem: default
	valgrind --leak-check=full ./a.out 2> out
