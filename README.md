Задание

* Реализовать функцию от аргумента a интегрального типа, возвращающую
признак того, что a является степенью двойки:
   f (a) == ((\exists i \in \N \cup {0}): a == 2^i).

* Реализовать класс битового вектора произвольной разрядности. Необходимые
методы:
   - конструктор (разрядность, массив переменных интегрального типа);
   - разрядность ();
   - установить битовое поле (смещение, битвектор);
   - получить битовое поле (смещение, разрядность);
   - получить битовое поле (смещение, разрядность) в переменную
интегрального типа: отдельный вариант для битовых полей малой разрядности
(до 64 разрядов);
   - получить строковое представление в 16-ричном виде.
  Разрядное (битовое) поле битового вектора определяется номерами позиций
младшего и старшего разряда поля.

* Реализовать функцию, для данного набора входных элементов (A)
возвращающую случайную выборку из n элементов (n <= size_of (A)). Все
возможные выборки должны быть равновероятны. Элементы входного набора
считать попарно различными.