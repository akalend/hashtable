# simple hashtable

tools/generate.py - генерация тестового файла
tests - unit tests

В качестве хранилища данных используется упрощенная хеш-таблица, основанная на разреженных массивах. В данном случае, взята Хеш-функция CRC64. Старший байт используется как ключ 1 в 64К массиве строк. 

Bucket - массив элементов 64К х 64, взято с запасом. Было произведено с десяток замеров с разными длиннами строк на массиве ~ 130-140Мб, в котором от 2-3 млн строк. Коллизия, при использовании 32 битного ключа в качестве хеш-функции составила 30 - 35 строк.

Каждая строка Bucket массива имеет 64 элемента следующей структуры:
```c
typedef struct  {
	uint16_t key;  	/* вторая часть ключа */
	char data[2];  	/* первые два байта от данных, на случай коллизии */
} ht_element;

```
Было выбрано магическое число 64 элемента в строке массива специально, чтоб был запас в 2 раза. Так как crc64 - это 8 байт, то первые 2 байта используются как ключ, для определения строки массива, а следующие два байта (можно 4 или 6) использовать для различия данных в случае коллизии. Практика показала, что 2х байт, при использовании CRC64 хватает (при использовании CRC32 необходимо использовать минимум 4 байта).


Как возможное расширение данного проекта, если коллизия уж слишком велика и не хватает элементов массива, то можно последние 8 байт использовать, как указатель на списочную структуру, где будут храниться ключи.


*Недостатки* - не оптимально распределена память, возможны пустые ячейки.

## Варианты

Предложенный выше вариант заточен под конкретную задачу и не совсем оптимален для универсального использования. Если мы за ранее не знаем объем используемого текста, то можно использовать алгоритм хеш-таблицы с переаллоцированием, как реализовано в STL. 

Первоночально величина Bucket массива устанавливается в некоторую константу, например, 1011. По мере заполнения массива, его величина увеличиваетсяв два раза, при этом мы меняем хеш-функцию, по которой осуществляется определение позиции в нашем bucket массиве.


Следующий вариант - это можно построить хештаблицу, основанную на списках, т.е. в Bucket хранися массив указателей на списочную структуру:

```c
typedef struct  {
	uint16_t key;  		/* вторая часть ключа */
	char data[2];  		/* первые два байта от данных, на случай коллизии */
	ht_element* next;	/* указатель на следующий элемент списка*/
} ht_element;

```

Если сравнивать по памяти, то при кол-ве коллизий менее 32 шт, выгоднее использовать списки, при более - использовать разреженный массив, так как в списке 8 байт (64-bit разрядность) занимает указатель.  Тут можно варировать как размерностью массива, например увеличить кол-во элементов до 128K или 256K. Тогда индексом массива будет старшие два байта + старший бит (или два) следующего байта. В этом случае - список коллизий будет короче и использование списочной структуры выгоднее, чем разреженный массив.


*Плюсы списочной хештаблицы* - более оптимально распределена память, нет избыточности.
*минусы* - медленее по скорости, но для данной задачи скорость вполне приемлема. Но, если часто использовать вставку/удаление элементов, то необходимо аллоцировать/освобождать память. Для этого лучше использовать пулы аллокаторов, а то может возникнуть проблема дефрагментации памяти.

Есть еще вариант, где все коллизии хранятся в одном отдельном массиве. Тут как раз применяется двойное хеширование, но в этом случаи мы опять имеем излишнюю избыточность.

Возможно использование хеш-табдицы с открытой адресацией, это когда в случае коллизии, мы используем следующую ячейкув одномерном массиве. В этом случае, желательно использовать размер bucket массива соизмеримыйс ко-вом используемых ключей.  Хеш функция: 

```c
  ORD(k) % n
```
k - номер ключа
n - размерность массива, рекомендуется выбирать простое число


В общем все очень зависит от данных, их длинны, частоты коллизий при использовании хеш-функции crc64. Можно использовать md5, тогда коллизия будет меньше, но кол-во байт на хранения хеша - больше.

