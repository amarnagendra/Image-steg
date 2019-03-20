SRCS=$(wildcard *.c)
TRGT=./steg.o
CFLAG= -I ../include

${TRGT} : ${SRCS}
	gcc $^ ${CFLAG} -o $@
clean:
	rm ${TRGT}
