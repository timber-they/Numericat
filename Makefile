.PHONY:all
all:
	cd Backend && make
	cd Frontend && make
.PHONY:clean
clean:
	cd Backend && make clean
	cd Frontend && make clean
