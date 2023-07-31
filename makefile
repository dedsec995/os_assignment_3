monks: monks.c
	gcc monks.c -o monks -pthread

diner: diner.c
	gcc diner.c -o diner -pthread

family: family.c
	gcc family.c -o family -pthread

runf: family.c
	gcc family.c -o family -pthread && ./family 10

rund: diner.c
	gcc diner.c -o diner -pthread && ./diner 10 > test.txt

runm: monks.c
	gcc monks.c -o monks -pthread && ./monks 10 100 > test.txt

clean:
	rm -rf family && rm -rf diner && rm -rf monks && rm -rf test.txt && clear