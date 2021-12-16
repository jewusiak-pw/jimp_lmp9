all: bin-dir
	cc -Wall --pedantic src/*.c -o bin/gauss


debug: bin-dir
	cc -Wall --pedantic -ggdb src/*.c -o bin/gauss

bin-dir:
	@mkdir -p bin

test-dir:
	@mkdir -p bin/tests

test-os: test-dir all
	@bin/gauss dane/A-os dane/B-os > bin/tests/output-os ;\
	excd=$$? ; \
	if [ $$excd -eq 3 ]; \
	then \
	  echo "Test macierzy osobliwej: OK (exit code: $$excd)";\
	else \
	  echo "Test macierzy osobliwej: BLAD! (exit code: $$excd)";\
	fi


test-1: test-dir all
	@bin/gauss dane/d1A dane/d1b > bin/tests/output-t1; \
	excd=$$? ; \
    res=$$(diff -b bin/tests/output-t1 dane/w1) ; \
    if [ -z "$$res" ]; \
    then \
      echo "Test 1: OK (exit code: $$excd)"; \
    else \
      echo "Test 1: BLAD! (exit code: $$excd)  Szczegoly:"; \
      echo $$res ; \
    fi


test-2: test-dir all
	@bin/gauss dane/d2A dane/d2b > bin/tests/output-t2; \
	excd=$$? ; \
    res=$$(diff -b bin/tests/output-t2 dane/w2) ; \
    if [ -z "$$res" ]; \
    then \
      echo "Test 2: OK (exit code: $$excd)"; \
    else \
      echo "Test 2: BLAD! (exit code: $$excd)  Szczegoly:"; \
      echo $$res ; \
    fi


test-3: test-dir all
	@bin/gauss dane/d3A dane/d3b > bin/tests/output-t3; \
	excd=$$? ; \
    res=$$(diff -b bin/tests/output-t3 dane/w3) ; \
    if [ -z "$$res" ]; \
    then \
      echo "Test 3: OK (exit code: $$excd)"; \
    else \
      echo "Test 3: BLAD! (exit code: $$excd)  Szczegoly:"; \
      echo $$res ; \
    fi



test-4: test-dir all
	@bin/gauss dane/d4A dane/d4b > bin/tests/output-t4; \
	excd=$$? ; \
    if [ $$excd -eq 4 ]; \
    then \
      echo "Test 4: OK (exit code: $$excd)"; \
    else \
      echo "Test 4: BLAD! (exit code: $$excd)"; \
      echo $$res ; \
    fi



test: test-os test-1 test-2 test-3 test-4
