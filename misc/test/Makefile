all:
	make -C ../..
	gcc gen_payload.c ../../build/libbloom.a -o gen_payload
	gcc test_bloom.c ../../build/libbloom.a -o test_bloom
test:
	make -C ../..
	gcc basic.c ../../build/libbloom.a -o basic
	./basic