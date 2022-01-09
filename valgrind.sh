mv -f valgrind.txt valgrind.prev &> /dev/null

sudo valgrind --log-file=valgrind.txt --leak-check=full --show-reachable=yes --track-origins=yes \
--show-leak-kinds=all ./bar