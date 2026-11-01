#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

#define ROW 9
#define COL 9 

int row, col;
long long number;
char answer;
int digits[20]; /* массив для хранения цифр числа */
int d_count;    /* количество цифр в числе */

int multiply(int r, int c);
void print_addition_table(void);
void analyze_number(long long num);

int main(void) {
    setlocale(0, ".UTF8");

    printf("--- Задание 1. Таблица Пифагора ---\n");
    for (row = 1; row <= ROW; row++) {
        for (col = 1; col <= COL; col++) {
            printf("%5d", multiply(row, col));
        }
        printf("\n");
    }
    printf("\n");

    printf("--- Задание 1.2. Левый нижний треугольник ---\n");
    for (row = 1; row <= ROW; row++) {
        for (col = 1; col <= row; col++) {
            printf("%5d", multiply(row, col));
        }
        printf("\n");
    }
    printf("\n");

    printf("--- Задание 1.3 (Вар15). Таблица сложения ---\n");
    print_addition_table();
    printf("\n");

    printf("--- Задание 2. Анализ длинного числа ---\n");

    while (1) {
        printf("Введите целое число: ");
        scanf("%lld", &number);

        analyze_number(number);

        printf("\nПродолжить? (Да - y, нет - n): ");
        scanf(" %c", &answer);

        if (answer == 'n' || answer == 'N') {
            break;
        }
        printf("\n");
    }

    return 0;
}

   // Умножение для таблицы Пифагора
int multiply(int r, int c) {
    int result = r * c;
    return result;
}

// Печать полной таблицы сложения
void print_addition_table(void) {
    for (row = 1; row <= ROW; row++) {
        for (col = 1; col <= COL; col++) {
            // Форматирование вида: 1 + 1 = 2
            printf("%d + %d = %-2d\t", row, col, row + col);
        }
        printf("\n");
    }
}

// Комплексный анализ числа
void analyze_number(long long num) {
    long long temp = num;
    d_count = 0;

    // Обработка отрицательных чисел
    if (temp < 0) temp = -temp;

    // Разложение на цифры (с конца)
    if (temp == 0) {
        digits[d_count++] = 0;
    }
    else {
        while (temp > 0) {
            digits[d_count++] = temp % 10;
            temp /= 10;
        }
    }

    int i;
    int count3 = 0, last_repeat = 0, even_count = 0, greater5 = 0;
    int sum_odd = 0, sum_ge7 = 0;
    long long prod_nonzero = 1;
    int adjacent_dupes = 0;

    int last_digit = digits[0];

    // Цикл по всем цифрам
    for (i = 0; i < d_count; i++) {
        // 1) Количество цифр 3
        if (digits[i] == 3) count3++;

        // 2) Число повторений последней цифры
        if (digits[i] == last_digit) last_repeat++;

        // 3) Количество четных цифр
        if (digits[i] % 2 == 0) even_count++;

        // 4) Количество цифр больше 5
        if (digits[i] > 5) greater5++;

        // 5) Сумма нечетных цифр
        if (digits[i] % 2 != 0) sum_odd += digits[i];

        // 6) Сумма цифр >= 7
        if (digits[i] >= 7) sum_ge7 += digits[i];

        // 7) Произведение всех цифр, исключая 0
        if (digits[i] != 0) prod_nonzero *= digits[i];

        // 9) Сумма четных цифр, исключая последнюю
        if (i > 0 && digits[i] % 2 == 0) {
            // здесь мы могли бы суммировать, но выполним это отдельно ниже для наглядности
        }

        // 10) Рядом расположенные одинаковые цифры
        if (i > 0 && digits[i] == digits[i - 1]) adjacent_dupes++;
    }

    // 8) Произведение предпоследней и второй цифры
    // "вторая" цифра (слева) - это digits[d_count - 2]
    // "предпоследняя" (с конца) - это digits[1]
    int second_left = (d_count >= 2) ? digits[d_count - 2] : 0;
    int second_right = (d_count >= 2) ? digits[1] : 0;
    int prod_8 = second_left * second_right;

    // 9) Сумма четных цифр, исключая последнюю (digits[0])
    int sum_even_excl_last = 0;
    for (i = 1; i < d_count; i++) {
        if (digits[i] % 2 == 0) sum_even_excl_last += digits[i];
    }

    // 11) Равна ли сумма первой и второй половины цифр
    int half_sum_left = 0, half_sum_right = 0;
    int mid = d_count / 2;
    for (i = 0; i < mid; i++) half_sum_right += digits[i]; // правая половина (младшие разряды)
    for (i = d_count - mid; i < d_count; i++) half_sum_left += digits[i]; // левая половина
    int is_half_equal = (half_sum_left == half_sum_right) ? 1 : 0;

    // 12) Произведение сумм цифр четных и нечетных разрядов (младший разряд - 1)
    int sum_pos_odd = 0, sum_pos_even = 0;
    for (i = 0; i < d_count; i++) {
        if ((i + 1) % 2 != 0) { // нечетный разряд
            sum_pos_odd += digits[i];
        }
        else { // четный разряд
            sum_pos_even += digits[i];
        }
    }
    long long prod_pos_sums = (long long)sum_pos_odd * sum_pos_even;

    // ВЫВОД РЕЗУЛЬТАТОВ
    printf("\n--- Результаты анализа ---\n");
    printf("1) Количество цифр 3: %d\n", count3);
    printf("2) Число повторений последней цифры (%d): %d\n", last_digit, last_repeat);
    printf("3) Количество четных цифр: %d\n", even_count);
    printf("4) Количество цифр больше 5: %d\n", greater5);
    printf("5) Сумма нечетных цифр: %d\n", sum_odd);
    printf("6) Сумма цифр больше или равно 7: %d\n", sum_ge7);
    printf("7) Произведение всех цифр (без 0): %lld\n", prod_nonzero);
    printf("8) Произведение предпоследней и второй цифры: %d\n", prod_8);
    printf("9) Сумма четных цифр, кроме последней: %d\n", sum_even_excl_last);
    printf("10) Количество рядом стоящих одинаковых цифр: %d\n", adjacent_dupes);
    printf("11) Сумма первой половины равна второй? %s\n", is_half_equal ? "Да" : "Нет");
    printf("12) Произведение сумм четных и нечетных разрядов: %lld\n", prod_pos_sums);
}
