TARGET		=  test
CC 			=  g++ -g -pedantic 
CFLAGS 		=  -fno-stack-protector  -Wall -Wextra -Werror -std=c++17  -g
TEST_FLAGS  =  -lgtest -pthread -std=c++17  -lstdc++ -lpthread -lm
GFLAGS      = -fprofile-arcs -ftest-coverage
OS		   :=  $(shell uname -s)
PATH_TEST	= ./tests/
SKIP_D      = '*/tests/*' 


all: clean $(TARGET) 


$(TARGET): clean test_run


test_run: test_all
	./test

test_all: 
	$(CC) -o test $(GFLAGS) tests/*.cc $(TEST_FLAGS) 
	# ./test
	# make lcov

test_vector: clean
	$(CC) -o test $(GFLAGS) tests/test_main.cc tests/test_s21_vector.cc $(TEST_FLAGS)
	./test
	make lcov

test_set: clean 
	$(CC) -o test $(GFLAGS) tests/test_main.cc tests/test_s21_set.cc $(TEST_FLAGS)
	./test
	make lcov

test_map: clean 
	$(CC) -o test $(GFLAGS) tests/test_main.cc tests/test_s21_map.cc $(TEST_FLAGS)
	./test
	make lcov

test_multiset: clean 
	$(CC) -o test $(GFLAGS) tests/test_main.cc tests/test_s21_multiset.cc  $(TEST_FLAGS)
	./test
	make lcov

test_list: clean 
	$(CC) -o test $(GFLAGS) tests/test_main.cc tests/test_s21_list.cc $(TEST_FLAGS)
	./test
	make lcov

test_queue: clean 
	$(CC) -o test $(GFLAGS) tests/test_main.cc tests/test_s21_queue.cc $(TEST_FLAGS)
	./test
	make lcov

test_stack: clean 
	$(CC) -o test $(GFLAGS) tests/test_main.cc tests/test_s21_stack.cc $(TEST_FLAGS)
	./test
	make lcov

test_array: clean 
	$(CC) -o test $(GFLAGS) tests/test_main.cc tests/test_s21_array.cc $(TEST_FLAGS)
	./test
	make lcov

clean:
	rm -f test
	rm -rf report
	rm -f *.o *.a a.out
	@rm -f *.gcda  *.gcno *.gcov
	@rm -f ${PATH_TEST}*.gcda  ${PATH_TEST}*.gcno ${PATH_TEST}*.gcov
	rm -f $(WAY_OBJ)*.o
	rm -f *.a *.log *.info main
	rm -f ${PATH_TEST}test ${PATH_TEST}gcov_report ${PATH_TEST}*.info 
	rm -rf ${PATH_TEST}test.* ${PATH_TEST}gcov_report.*
	rm -rf *.dSYM


gcov_report: clean
	$(CC) -o test   tests/*.cc $(TEST_FLAGS) $(GFLAGS)
	# ./test
	make lcov

lcov: 
	# $(CC) -o test    tests/*.cc $(TEST_FLAGS) $(GFLAGS)
	# ./test
	lcov --quiet --no-recursion --capture --directory . --output-file test.info
	@lcov --quiet --no-recursion -r test.info '/usr/*' '*/v1/*'  ${SKIP_D}   -o test.info
	genhtml -o ./report/ test.info
	@rm -f *.gcda  *.gcno
	@rm -f  test.info


open:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" report/index.html
else
	xdg-open report/index.html
endif


clang:
	clang-format -n -style=google *.h
	clang-format -n -style=google tests/*.h
	clang-format -n -style=google *.h
	clang-format -n -style=google tests/*.cc 
	clang-format -n -style=google s21_containers/*.h

clangI:
	clang-format -i -style=google *.h
	clang-format -i -style=google tests/*.h
	clang-format -i -style=google *.h
	clang-format -i -style=google tests/*.cc 
	clang-format -i -style=google s21_containers/*.h

leak: 
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	CK_FORK=no valgrind --leak-check=full -s --track-origins=yes --log-file=leak.log ./test 
endif	

docker: docker_clean
	docker build -f Dockerfile  -t test_containers:cpp . # --no-cache
	docker run -t --name containers_cpp  test_containers:cpp 
	docker cp containers_cpp:/home/report/ .
	docker cp containers_cpp:/home/leak.log .
	docker rm containers_cpp
	docker rmi test_containers:cpp
	
docker_clean:
	docker rm $$(docker ps -a -q) || true
	docker rmi -f $$(docker images -q) || true
