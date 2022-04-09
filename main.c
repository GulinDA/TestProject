#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *get_string(int *len) // Функция чтения идентификатора
{
    *len = 0;
    int capacity = 1;
    char *s = (char*) malloc(sizeof(char));
    char c = getchar();
    while (c != '\n') {
        s[(*len)++] = c;
        if (*len >= capacity) {
            capacity *= 2;
            s = (char*) realloc(s, capacity * sizeof(char));
        }
        c = getchar();
    }
    s[*len] = '\0';
    return s;
}

char *parse_identifier(char *s)         //Функция обработки идентификатора и нахождение следующего
{
    if (strlen(s)<2 || (strlen(s)+1)%3  || strlen(s)>29)
    {
        char *str = (char*)malloc(19*sizeof(char));
        str = "Invalid identifier";
        return str;
    }
    int count = (strlen(s)+1)/3;
    char array_str [count][3];             //Массив частей идентификатора
    char separator_str [count];             //Строка разделителей
    for (int i = 0, j = 0; i < strlen(s)-2; i+=3, j++)
    {
        array_str[j][0] = s[i];
        array_str[j][1] = s[i+1];
        array_str[j][2] = '\0';
        separator_str[j] = s[i+2];
    }
    array_str[count-1][0] = s[strlen(s)-2];
    array_str[count-1][1] = s[strlen(s)-1];
    array_str[count-1][2] = '\0';
    separator_str[count-1] = '\0';              //Разделение идентификатора на массив частей и строку разделителей для проверки
    for (int i = 0; i < count-1; i++)           //Проверка разделителей
    {
        if (separator_str[i]!='-')
        {
            char *str = (char*)malloc(19*sizeof(char));
            str = "Invalid identifier";
            return str;
        }
    }
    const char consonants_str[] = "BCDFGHJKLMNPRSTVWXZ";
    const char digits_str[] = "1234567891";
    const char max_identifier[] = "Z9";
    for (int i = 0; i<count; i++)               //Проверка частей идентификатора
    {
        if(!(strchr(consonants_str, array_str[i][0])&&strchr(digits_str, array_str[i][1])))
        {
            char *str = (char*)malloc(19*sizeof(char));
            str = "Invalid identifier";
            return str;
        }
    }
    int flag_new_part = 1;
    for (int i = count-1; i>=0; i--)            //Получение следующего идентификатора
    {
        if (strcmp(array_str[i],max_identifier) == 0)
        {
            array_str[i][0] = 'B';
            array_str[i][1] = '1';
        }
        else
        {
            int index = strchr(digits_str, array_str[i][1])-digits_str;
            array_str[i][1] = digits_str[index+1];
            if (index+1 == strlen(digits_str)-1)
            {
                index = strchr(consonants_str, array_str[i][0])-consonants_str;
                array_str[i][0] = consonants_str[index+1];
            }
            flag_new_part = 0;
            break;
        }
    }
    if (flag_new_part && count == 10)                       //максимальный идентификатор, состоящий из 10 Z9
    {
        char *str = (char*)malloc(15*sizeof(char));
        str = "Max identifier";
        return str;
    }
    if (flag_new_part)                                      //если все Z9, то добавление новой части идентификатора
    {
        char *str = (char*)malloc((count+1)*3*sizeof(char));
        for(int i = 0; i < count+1; i++)
        {
            str[i*3] = 'B';
            str[i*3+1] = '1';
            str[i*3+2] = '-';
        }
        str[(count+1)*3-1] = '\0';
        return str;
    }
    else                                                     //Выаод следующего идентификатора в остальных случаях
    {
        char *str = (char*)malloc(count*3*sizeof(char));
        for(int i = 0; i < count; i++)
        {
            str[i*3] = array_str[i][0];
            str[i*3+1] = array_str[i][1];
            str[i*3+2] = '-';
        }
        str[count*3-1] = '\0';
        return str;
    }
}

int main() {
    int len;
    printf("Input identifier:\n");
    char *s = get_string(&len);
    char *snext = parse_identifier(s);
    printf("%s\n", snext);
    free(s);
    return 0;
}
