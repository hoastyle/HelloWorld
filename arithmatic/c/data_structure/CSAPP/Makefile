# include <makefile name>, with pre "-" will run whatever

# 编译
# a: 2-10.o
OUT_DIR = build
objects = 2-10 2-12 test

all: $(objects) $(OUT_DIR)

$(OUT_DIR):
	mkdir $@

$(objects):
	gcc *.c

$(:)

# clean
.PHONY: clean
clean:
	rm -rf build/* 
