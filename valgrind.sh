mv -f valgrind.txt valgrind.prev &> /dev/null

valgrind --log-file=valgrind.txt --leak-check=full --show-reachable=yes --track-origins=yes --show-leak-kinds=all \
sudo ./a.out