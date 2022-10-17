1. Реализовать классическое перемножение матриц и умножение матрицы на вектор на C/C++ с разным порядком циклов (25\%) (Сделано на основании курса по C++)
2.  Разбейте на модули, со статической линковкой скомпилируйте текст, подготовьте Makefile, проверьте флаги -g,  -O3 (Сделано)
3. Измерьте времена исполнения для размеров $N = 500, 512, 1000, 1024, 2000, 2048
-g
N = 500 Time taken 1412382 microseconds
N = 512 Time taken 1718341 microseconds
N = 1000 Time taken 19312960 microseconds
N = 1024 Time taken 19537998 microseconds
N = 2000 Time taken 185145996 microseconds
N = 2048 Time taken 204470478 microseconds
-O3
N = 500 Time taken 1436496 microseconds
N = 512 Time taken 1648158 microseconds
N = 1000 Time taken 19286930 microseconds
N = 1024 Time taken 19475742 microseconds
N = 2000 Time taken 201935846 microseconds
N = 2048 Time taken 255964258 microseconds

4. Базовые скрипты баш.