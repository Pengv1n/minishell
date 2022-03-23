all:
	gcc -I src/ -I libft/ src/*.c libft/*.c -lreadline
