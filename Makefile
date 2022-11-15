small_kvs:
	gcc -o small_kvs small_kvs.c
clean:
	rm -rf small_kvs
	rm -rf tags
	rm -rf *.files
	rm -rf *.out
tags:
	ctags -R
cscope:
	find . \( -name '*.c' -o -name '*.h' \) -print > cscope.files
	cscope -i cscope.files
