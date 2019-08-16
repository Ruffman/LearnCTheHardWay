all:
	cc -c libex29.c
	cc -shared libex29.o -o libex29.so
	cc -Wall -g -DNDEBUG ex29.c -ldl -o ex29

tests:
	./ex29 ./libex29.so print_a_message "Hello there"
	./ex29 ./libex29.so uppercase "Hello there"
	./ex29 ./libex29.so lowercase "Hello ThErE"
	./ex29 ./libex29.so fail_on_purpose "Hello there"

clean:
	rm -f ex29
	rm -f libex29.o
	rm -f libex29.so
