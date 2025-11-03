#include "quick_quizzes.h"

int quick_quiz_22_09_25(
    int argc,
    char *argv[])
{
    int value1, value2, value3;
    printf("Input 3 integral values: ");
    if (scanf("%d%d%d", &value1, &value2, &value3) != 3)
    {
        // TODO: validation
    }

    // а)
    if (value1 == value2 + value3 ||
        value2 == value3 + value1 ||
        value3 == value1 + value2)
    {
        // TODO: for product, You can do the same with operator*
    }

    // б)
    if (value1 > 0 && value2 > 0 && value3 > 0 &&
        value1 + value2 > value3 &&
        value1 - value2 < value3 &&
        value2 - value1 < value3 &&
        value3 + value2 > value1 &&
        value3 - value2 < value1 &&
        value2 - value3 < value1 &&
        value1 + value3 > value2 &&
        value1 - value3 < value2 &&
        value3 - value1 < value2)
    {
        // TODO
    }

    // в) 
    // 8192 == 2^13
    // 00100000 00000000
    //                 1
    // 00011111 11111111
    int n = value1 + value2 + value3;
    int is_power_of_two = (n & (n - 1)) == 0 && n > 0;
    printf("Is power of 2: %d", is_power_of_two);

    // 2^0 == 2^1 - 1
    // 2^0 + 2^1 == 2^2 - 1
    // 2^0 + 2^1 + 2^2 == 2^3 - 1
    // 2^13 - 1 = 

    return 0;
}

int quick_quiz_29_09_25(
    int argc,
    char *argv[])
{
    double difference;
    int attempts_counter = 0;
    double first_value, second_value;
    double epsilon = 0.0;
    // while (epsilon == 0.0) - ЭТО БАН!!1!1
    // while (epsilon != 0.0) - ЭТО БАН!!1!1

    // TODO: printf
    if (scanf("%lf", &first_value) != 1)
    {
        // TODO: validate
    }

    while (epsilon <= 0.0)
    {
        // TODO: printf
        if (scanf("%lf", &epsilon) != 1)
        {
            // TODO: validate
        }

        if (++attempts_counter == 3 && epsilon <= 0.0)
        {
            // exit(1); - ЭТО БАН
            return 1;
        }
    }

    do
    {
        // TODO: printf
        if (scanf("%lf", &second_value) != 1)
        {
            // TODO: validate
        }
    } while (fabsl(first_value - second_value) >= epsilon);

    printf("v1 * v2 == %lf", first_value * second_value);

    return 0;
}

int quick_quiz_06_10_25(
    int argc,
    char *argv[])
{
    int values[512], i;
    int* p_value = values;
    double average = 0.0;
    // rand() % (b - a + 1) + a
    // rand() % 7 - 0, 1, 2, 3, 4, 5, 6
    // [a..b] -> [0...b-a] + a

    srand((unsigned int)time(NULL));
    for (i = 0; i < 512; ++i)
    {
        values[i] = rand() % 1001 - 500;
        printf("%d ", values[i] /*use assignment operator*/);
    }

    for (i = 0; i < 512; ++i)
    {
        average += *p_value;
        p_value++;
    }

    printf("%.6lf", average /= 512);

    return 0;
}

int quick_quiz_13_11_25(
    int argc,
    char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid command arguments count!");
        return -3;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile)
    {
        // TODO: handle file opening error
        printf("Input file not exists!");
        return -1;
    }

    FILE* outputFile = fopen(argv[2], "w");
    if (!outputFile)
    {
        printf("Output file can't be created!");
        fclose(inputFile);
        return -2;
    }

    char buf[BUFSIZ], * b = buf, c, c_ = ' ';
    int convertedValue;

    while (!feof(inputFile))
    {
        c = toupper(fgetc(inputFile));

        if (!(c == ' ' || c == '\t' || c == '\n' || c == EOF))
        {
            // x = ++*b, *++b, x = *b++, x = (*b)++
            *b = c;
            b++;
        }
        else if (b != buf) // lexem found!
        {
            *b = '\0'; // b - buf == strlen(buf)
            b = buf;
            convertedValue = 0;

            while (*b /*!= 0*/)
            {
                if (isdigit(*b) || (*b >= 'A' && *b <= 'F'))
                {
                    convertedValue = convertedValue * 16 + (isdigit(*b)
                        ? *b - '0' // *b - 48 - the same
                        : *b - 'A' + 10); // *b - 55
                }
                else
                {
                    break;
                }

                ++b;
            }

            if (!*b)
            {
                fprintf(outputFile, "%s(16) == %d(10)\n", buf, convertedValue);
            }

            b = buf;
        }

        c_ = c;
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

int quick_quiz_20_10_25(
    int argc,
    char *argv[])
{
    // TODO

    return 0;
}

int quick_quiz_27_10_25(
    int argc,
    char* argv[])
{
    // TODO: 

    return 0;
}

int quick_quiz_03_11_25(
    int argc,
    char *argv[])
{


    return 0;
}