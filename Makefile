small_kvs:
	gcc -o small_kvs small_kvs.c
clean:
	rm -rf small_kvs
	rm -rf tags
tags:
	ctags -R
