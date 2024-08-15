all:	pideShop	hungryVeryMuch	valgrind_pideShop	valgrind_hungryVeryMuch

pideShop:	pideShop.c
	gcc	-g	-o	PideShop	pideShop.c	-lpthread -lm

hungryVeryMuch:	hungryVeryMuch.c
	gcc	-g	-o	HungryVeryMuch	hungryVeryMuch.c -lm

valgrind_pideShop:	PideShop
	valgrind	--leak-check=full	\
										--show-leak-kinds=all	\
										--track-origins=yes	\
										--verbose	\
										--log-file=valgrind-out.txt	\
										./PideShop	0.0.0.0	4	6	1

valgrind_hungryVeryMuch:	HungryVeryMuch
	valgrind	--leak-check=full	\
										--show-leak-kinds=all	\
										--track-origins=yes	\
										--verbose	\
										--log-file=valgrind-out2.txt	\
										./HungryVeryMuch	0.0.0.0	10	10	10

clean:
	rm	-f	PideShop	HungryVeryMuch	valgrind-out.txt	valgrind-out2.txt
