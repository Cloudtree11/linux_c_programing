
.PHONY : all
all : demo_sigio

demo_sigio : demo_sigio.o error_functions.o tty_functions.o
	cc -o $@ $^

poll_pipes : poll_pipes.o error_functions.o get_num.o
	cc -o $@ $^

t_select : t_select.o error_functions.o get_num.o
	cc -o $@ $^

#

demo_sigio.o : demo_sigio.c
	cc -c $<

tty_functions.o : tty_functions.c tty_functions.h
	cc -c $<

poll_pipes.o : poll_pipes.c
	cc -c $<

t_select.o : t_select.c
	cc -c $<

error_functions.o : error_functions.c error_functions.h tlpi_hdr.h ename.c.inc
	cc -c $<

get_num.o : get_num.c get_num.h
	cc -c $<

.PHONY : clean
clean :
	rm *.o
