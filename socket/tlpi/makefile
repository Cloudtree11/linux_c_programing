
.PHONY : all
all : ud_ucase_cl ud_ucase_sv

ud_ucase_cl : ud_ucase_cl.o error_functions.o
	cc -o $@ $^

ud_ucase_sv : ud_ucase_sv.o error_functions.o
	cc -o $@ $^

us_xfr_sv : us_xfr_sv.o error_functions.o get_num.o
	cc -o $@ $^

us_xfr_cl : us_xfr_cl.o error_functions.o get_num.o
	cc -o $@ $^

ud_ucase_sv.o : ud_ucase_sv.c ud_ucase.h
	cc -c $<

ud_ucase_cl.o : ud_ucase_cl.c ud_ucase.h
	cc -c $<

us_xfr_sv.o : us_xfr_sv.c us_xfr.h
	cc -c $<

us_xfr_cl.o : us_xfr_cl.c us_xfr.h
	cc -c $<

error_functions.o : error_functions.c error_functions.h tlpi_hdr.h ename.c.inc
	cc -c $<

get_num.o : get_num.c get_num.h
	cc -c $<

.PHONY : clean
clean :
	rm *.o
