OBJS = rsa_math.o create_keys.o main.o encrypt.o decrypt.o 
DEPS = rsa.h
CARGS = -Wall -g -c
rsa: $(OBJS)
	gcc -Wall -g $(OBJS) -lgmp -o rsa

rsa_math.o: $(DEPS)
	gcc $(CARGS) rsa_math.c -lgmp

create_keys.o: $(DEPS) 
	gcc $(CARGS) create_keys.c -lgmp

encrypt.o: $(DEPS)
	gcc $(CARGS) encrypt.c -lgmp

decrypt.o: $(DEPS)
	gcc $(CARGS) decrypt.c -lgmp

main.o: $(DEPS)
	gcc $(CARGS) main.c 

.PHONY: clean
clean:
	rm -f $(OBJS) rsa
