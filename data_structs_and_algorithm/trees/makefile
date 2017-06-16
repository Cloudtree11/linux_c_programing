
BinaryTree : BinaryTree.o DAS.o DCAQ.o
	cc -o $@ $^

BinaryTree.o : BinaryTree.c DAS.h DCAQ.h 
	cc -c $< 

DAS.o : DAS.c DAS.h
	cc -c $<

DCAQ.o : DCAQ.c DCAQ.h
	cc -c $<

.PHONY : clean
clean :
	rm *.o
