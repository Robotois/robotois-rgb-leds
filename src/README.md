# Test the C++ Library

In the file `test.cpp` it is provided a simple test for the RGB module. The rest consists in varying the color of all LEDs with the function `allOn`, next we test the `turnOn`, then we test the `allBlink` function, following by the `blink` function.

To run the test follow these steps:

* Compile the sources with the following command: `make all`

* The previous command will generate an executable file named `runner`, which you can run as follows: `sudo ./runner`.

* To remove the compiled `*.o` files and the dist file `runner`, execute the following line: `make clean`.
