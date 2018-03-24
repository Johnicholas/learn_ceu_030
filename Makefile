
hello: hello_plus_env.c
	gcc -o hello hello_plus_env.c

hello_plus_env.c: hello.c types.h main.c
	ceu --env --env-ceu=hello.c --env-types=types.h --env-main=main.c --env-output=hello_plus_env.c

hello.c: hello.ceu
	ceu --ceu --ceu-line-directives=false --ceu-input=hello.ceu --ceu-output=hello.c

.PHONY: clean
clean:
	rm hello hello_plus_env.c hello.c
