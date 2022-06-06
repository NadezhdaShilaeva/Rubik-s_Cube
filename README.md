# Rubik-s Cube
###### Лабораторная работа по программированию №4. 2 семестр.


Программа, имитирующая сборку Кубика Рубика 3x3.  

В данной программе реализованы следующие функции:  
- Сохранение и чтение состояния Кубика Рубика из файла.  
- Проверка корректности текущего состояния (инвариант состояний кубика).  
- Вывод в консоль текущего состояния в виде развертки с цветными гранями.  
- Вращение граней кубика рубика с помощью вводимых команд.  
- Генерация случайного состояния Кубика Рубика, корректного с точки зрения
инварианта состояний.  
- Нахождения “решения” для текущего состояния в виде последовательности
поворотов граней.  

Нефункциональные особенности программы:
- Программа спроектирована, с использованием ОПП.  
- Логические сущности выделены в отдельный классы _CSide_ и _CCube_.  

Данная программа реализована в виде рекурсивной игры _GameCube_, которая сначала предлагает пользователю выбрать начальное состояние кубика:
- ___file___ - считать состояние кубика из файла (далее программа запрашивает у пользователя имя файла);  
- ___generate___ - сгенерировать корректное состояние;  
- ___solved___ - использовать начальное (решенное) состояние.  

Далее программа предлагает пользователю набор команд для управления кубиком и игрой:
- ___stop___ - остановить игру;  
- ___show___ - вывести в консоль текущее состояние кубика;  
- ___file___ - сохранить текущее состояние кубика в файл (далее программа запрашивает у пользователя имя файла);  
- ___solve___ - решить Кубик Рубика и вывести решение в консоль;  
- ___F___ / ___B___ / ___R___ / ___L___ / ___U___ / ___D___ - повернуть соответствующую грань по часовой стрелке;  
- ___F'___ / ___B'___ / ___R'___ / ___L'___ / ___U'___ / ___D'___ - повернуть соответствующую грань против часовой стрелке;  

#####Формат входных данных:
Вводится одна из предлагаемых программой команд. В случае некорректного ввода, программа сообщает об ошибке и просит повторно ввести команду.

---

#####Примеры использования программы:
___Выходные данные:___  
Welcome to our Rubik's cube game!  
Enter "file" to read the cube from file.  
Enter "generate" to generate the cube.  
Enter "solved" to start the game with solved cube.  

___Входные аргументы:___  
generate  

___Выходные данные:___  
Game started!  
Enter "stop" to stop the game.  
Enter "show" to show current state of the cube.  
Enter "file" to save current state of cube in file.  
Enter "solve" to solve the cube and show the cube solution.  
Enter "F" / "B" / "R" / "L" / "U" / "D" to rotate clockwise the corresponding side.  
Enter "F'" / "B'" / "R'" / "L'" / "U'" / "D'" to rotate counterclockwise the corresponding side.  

___Входные аргументы:___  
show

___Выходные данные:___  
Enter the command for the cube:  

___Входные аргументы:___  
solve  

___Выходные данные:___  
L F U F F B' U U F F U U U L L B B U U U R R F U F' U' F U F' U' F U F' U' U U U R U R' U' U U L U L' U' B U B' U' B U B' U' U U F U F' U' L' U' L U U' B' U' B U L U L' U' U B U B' U' R' U' R U R B U B' U' R' R B U B' U' R' R U R' U R U U R' U F U' B' U F' U' B U D' R' D R D' R' D R U D' R' D R D' R' D R U D' R' D R D' R' D R U U

Thank you for playing the game!  
Would you like to play the game again?  
Enter "yes" if you want and "no" if you don't want:  

___Входные аргументы:___  
yes  

___Выходные данные:___  
Welcome to our Rubik's cube game!  
Enter "file" to read the cube from file.  
Enter "generate" to generate the cube.  
Enter "solved" to start the game with solved cube.  

___Входные аргументы:___  
solved  

___Выходные данные:___  
Game started!  
Enter "stop" to stop the game.  
Enter "show" to show current state of the cube.  
Enter "file" to save current state of cube in file.  
Enter "solve" to solve the cube and show the cube solution.  
Enter "F" / "B" / "R" / "L" / "U" / "D" to rotate clockwise the corresponding side.  
Enter "F'" / "B'" / "R'" / "L'" / "U'" / "D'" to rotate counterclockwise the corresponding side.  

___Входные аргументы:___  
F  

___Выходные данные:___  
Enter the command for the cube:  

___Входные аргументы:___  
show  

___Выходные данные:___  

Enter the command for the cube:  

___Входные аргументы:___  
F'  

___Выходные данные:___  
Congratulations!  
You solve the cube!  
Would you like to play the game again?  
Enter "yes" if you want and "no" if you don't want:  

___Входные аргументы:___  
no  

___Выходные данные:___  
Goodbye! I hope to see you again!  