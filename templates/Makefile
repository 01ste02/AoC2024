.PHONY: all cleanpart1 cleanpart2 part1 part2 clean

CC=gcc -O3 -g
RUN=valgrind --leak-check=full --show-leak-kinds=all

all:	clean part1 part2

part1:	cleanpart1
	@echo "Part 1"
	$(CC) part1.c -o part1.out
	$(RUN) ./part1.out > part1.output
	cat part1.output

part2:	cleanpart2
	@echo "Part 2"
	$(CC) part2.c -o part2.out
	$(RUN) ./part2.out > part2.output
	cat part2.output

clean:
	@echo "Cleaning"
	rm *.out
	rm part*.output

cleanpart1:
	@echo "Cleaning part 1"
	rm -f part1.out
	rm -f part1.output

cleanpart2:
	@echo "Cleaning part 2"
	rm -f part2.out
	rm -f part2.output
