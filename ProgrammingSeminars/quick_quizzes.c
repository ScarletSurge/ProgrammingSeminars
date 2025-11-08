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

typedef struct time
{
    unsigned int hours;
    unsigned int minutes;
};

typedef struct schedule_unit
{
    unsigned int route_number;
    char* station_name;
    struct time stop_time;
} schedule_unit;

int read_schedule_from_file(
    char const* file_path,
    schedule_unit **read_schedule_units,
    size_t *read_schedule_units_count);

int read_schedule_unit(
    FILE *read_context,
    schedule_unit *target);

int quick_quiz_03_11_25(
    int argc,
    char *argv[])
{
    int x;
    schedule_unit *read_units;
    size_t read_units_count;
    switch (read_schedule_from_file("D:\\Repos\\KosyginRSU\\ProgrammingSeminars\\ProgrammingSeminars\\schedule.txt", &read_units, &read_units_count))
    {
    case 0:
        x = 10;
        break;
    }

    return 0;
}

int read_schedule_from_file(
    char const* file_path,
    schedule_unit** read_schedule_units,
    size_t* read_schedule_units_count)
{
    int exit_code = 0;

    if (file_path == NULL)
    {
        exit_code |= 0x1;
    }

    if (read_schedule_units == NULL)
    {
        exit_code |= 0x2;
    }

    if (read_schedule_units_count == NULL)
    {
        exit_code |= 0x4;
    }

    if (exit_code != 0)
    {
        return exit_code;
    }

    FILE *input_file;
    if (!(input_file = fopen(file_path, "r")))
    {
        return 8;
    }

    if ((*read_schedule_units = (schedule_unit*)malloc(sizeof(schedule_unit) * (*read_schedule_units_count = 16))) == NULL)
    {
        fclose(input_file);
        return 16;
    }

    int idx = 0;

    while (!feof(input_file))
    {
        // &a[i] <-> a + i
        if (idx == *read_schedule_units_count)
        {
            schedule_unit *for_realloc = (schedule_unit *)realloc(*read_schedule_units, sizeof(schedule_unit) * (*read_schedule_units_count << 1));
            if (for_realloc == NULL)
            {
                int i;
                for (i = 0; i < *read_schedule_units_count; ++i)
                {
                    free((*read_schedule_units)[i].station_name);
                }
                free(*read_schedule_units);
                *read_schedule_units = NULL;
                *read_schedule_units_count = 0;
                return 32;
            }
            *read_schedule_units = for_realloc;
            for_realloc = NULL;
            *read_schedule_units_count <<= 1;
        }

        switch (read_schedule_unit(input_file, *read_schedule_units + idx))
        {
        case 0:

            break;
        }

        ++idx;
    }

    fclose(input_file);

    if (idx < *read_schedule_units_count)
    {
        schedule_unit* for_realloc = (schedule_unit*)realloc(*read_schedule_units, sizeof(schedule_unit) * idx);
        if (for_realloc == NULL)
        {
            int i;
            for (i = 0; i < *read_schedule_units_count; ++i)
            {
                free((*read_schedule_units)[i].station_name);
            }
            free(*read_schedule_units);
            *read_schedule_units = NULL;
            *read_schedule_units_count = 0;
            return 32;
        }
        *read_schedule_units = for_realloc;
        for_realloc = NULL;
        *read_schedule_units_count = idx;
    }

    return exit_code;
}

int read_schedule_unit(
    FILE *read_context,
    schedule_unit *target)
{
    if (read_context == NULL)
    {
        return 1;
    }

    if (target == NULL)
    {
        return 2;
    }

    target->route_number = 0;
    target->stop_time.hours = 0;
    target->stop_time.minutes = 0;
    size_t station_name_buf_len = 16;
    if ((target->station_name = (char*)malloc(sizeof(char) * station_name_buf_len)) == NULL)
    {
        return 3;
    }
    char *sn = target->station_name;

    char c = ' ';
    int read_flag = 0; // 0 - while reading route number; 1 - while reading time; 2 - read station name
    int reading_minutes = 0;

    unsigned int *time_var_addr;

    while (1)
    {
        c = fgetc(read_context);

        if (c == EOF || c == '\n' || c == '\r')
        {
            if (sn - target->station_name == station_name_buf_len)
            {
                char* for_realloc = (char*)realloc(target->station_name, sizeof(char) * (station_name_buf_len + 1));
                if (for_realloc == NULL)
                {
                    free(target->station_name);
                    target->station_name = NULL;
                    return 4;
                }
                target->station_name = for_realloc;
                sn = target->station_name + station_name_buf_len;
            }

            *sn = 0;

            int strl;
            if ((strl = sn - target->station_name) != station_name_buf_len)
            {
                char *for_realloc = (char *)realloc(target->station_name, sizeof(char) * (strl + 1));
                if (for_realloc == NULL)
                {
                    free(target->station_name);
                    target->station_name = NULL;
                    return 4;
                }
                target->station_name = for_realloc;
            }

            break;
        }
        
        if (read_flag == 2)
        {
            if (sn - target->station_name == station_name_buf_len)
            {
                char* for_realloc = (char*)realloc(target->station_name, sizeof(char) * (station_name_buf_len << 1));
                if (for_realloc == NULL)
                {
                    free(target->station_name);
                    target->station_name = NULL;
                    return 4;
                }
                target->station_name = for_realloc;
                sn = target->station_name + station_name_buf_len;
                station_name_buf_len <<= 1;
            }
            *sn++ = c;
        }
        if (c == ':' && read_flag == 1)
        {
            reading_minutes = 1;
        }
        else if (isdigit(c))
        {
            switch (read_flag)
            {
            case 0:
                target->route_number = target->route_number * 10 + c - '0';
                break;
            case 1:
                time_var_addr = reading_minutes == 0
                    ? &target->stop_time.hours
                    : &target->stop_time.minutes;
                *time_var_addr = *time_var_addr * 10 + (c - '0');
                break;
            }
        }

        else if (c == ' ')
        {
            if (read_flag != 2)
            {
                ++read_flag;
            }
        }
    }

    return 0;
}