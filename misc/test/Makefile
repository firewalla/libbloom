all:
	make -C ../..
	gcc gen_payload.c ../../build/libbloom.a -o gen_payload
test:
	make -C ../..
	gcc basic.c ../../build/libbloom.a -o basic
	./basic