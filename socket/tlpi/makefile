
.PHONY : all
all : id_echo_sv id_echo_cl

id_echo_sv : id_echo_sv.o error_functions.o become_daemon.o inet_sockets.o
	cc -o $@ $^

id_echo_cl : id_echo_cl.o error_functions.o inet_sockets.o
	cc -o $@ $^

t_getservbyname : t_getservbyname.o error_functions.o
	cc -o $@ $^

is_seqnum_cl : is_seqnum_cl.o error_functions.o read_line.o get_num.o
	cc -o $@ $^

is_seqnum_sv : is_seqnum_sv.o error_functions.o read_line.o get_num.o
	cc -o $@ $^

i6d_ucase_cl : i6d_ucase_cl.o error_functions.o
	cc -o $@ $^

i6d_ucase_sv : i6d_ucase_sv.o error_functions.o
	cc -o $@ $^

ud_ucase_cl : ud_ucase_cl.o error_functions.o
	cc -o $@ $^

ud_ucase_sv : ud_ucase_sv.o error_functions.o
	cc -o $@ $^

us_xfr_sv : us_xfr_sv.o error_functions.o get_num.o
	cc -o $@ $^

us_xfr_cl : us_xfr_cl.o error_functions.o get_num.o
	cc -o $@ $^

#

become_daemon.o : become_daemon.c become_daemon.h

id_echo_sv.o : id_echo_sv.c id_echo.h
	cc -c $<

id_echo_cl.o : id_echo_cl.c id_echo.h
	cc -c $<

t_getservbyname.o : t_getservbyname.c tlpi_hdr.h
	cc -c $<

inet_sockets.o : inet_sockets.c inet_sockets.h
	cc -c $<

is_seqnum_sv.o : is_seqnum_sv.c is_seqnum.h
	cc -c $<

is_seqnum_cl.o : is_seqnum_cl.c is_seqnum.h
	cc -c $<

read_line.o : read_line.c read_line.h
	cc -c $<

i6d_ucase_sv.o : i6d_ucase_sv.c i6d_ucase.h
	cc -c $<

i6d_ucase_cl.o : i6d_ucase_cl.c i6d_ucase.h
	cc -c $<

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
