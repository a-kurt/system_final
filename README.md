To compile:
make pideShop
make hungryVeryMuch

To run the server:
./PideShop [ip] [CookthreadPoolSize] [DeliveryPoolSize] [k]

To run the client generator:
./HungryVeryMuch [ip] [numberOfClients] [p] [q]

To test memory leaks with Valgrind:
make valgrind_pideShop          (default values are 0.0.0.0	4	6	1 )
make valgrind_hungryVeryMuch    (default values are 0.0.0.0	10	10	10)

^C and ^D on client side: Order cancellation.
^C and ^D on server side: Shop shutdown.