build:
	gcc poduri.c -o poduri
	gcc adrese.c -o adrese
	gcc lego.c -o lego
	gcc retea.c -o retea

run-p1:
	./poduri

run-p2:
	./adrese

run-p3:
	./lego

run-p4:      # nume necesar
	./retea

clean:
	rm poduri
	rm adrese
	rm lego
	rm retea