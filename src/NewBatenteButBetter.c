#include "../includes/TipoDados.h"

#define ARRAY_SIZE 10

typedef struct NewBatenteButBetter{
    int key;
    struct NewBatenteButBetter *next;
    struct NewBatenteButBetter *value;
    struct NewBatenteButBetter *Info;
}map;
typedef struct {
    int key;
    char *value;
} HashMapNode;

int array[ARRAY_SIZE];
HashMapNode **hashmap;

typedef struct _map {
    char *key;
    int value;
    struct _map *next;
} map;

/* void insert(map **table, char *key, int value) {
    map *item = malloc(sizeof(map));
    item->key = malloc(strlen(key) + 1);
    strcpy(item->key, key);
    item->value = value;
    item->next = NULL;
    if (*table == NULL) {
        *table = item;
    } else {
        map *tmp = *table;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = item;
    }
} */



void insert(map **table, char *key, Elemento* Info) {
    map *item = (map*) malloc(sizeof(map));
    item->key = (char*) malloc(strlen(key) + 1);
    strcpy(item->key, key);
    item->Info = Info;
    item->next = NULL;
    if (*table == NULL) {
        *table = item;
    } else {
        map *tmp = *table;
        while (tmp->next != NULL) {
            if (strcmp(tmp->key, key) == 0) {
                if (tmp->Info < Info) {
                    map *new_item = (map*) malloc(sizeof(map));
                    new_item->key = (char*) malloc(strlen(key) + 1);
                    strcpy(new_item->key, key);
                    new_item->Info = Info;
                    new_item->next = NULL;
                    if (tmp == *table) {
                        new_item->next = *table;
                        *table = new_item;
                    } else {
                        new_item->next = tmp;
                        map *prev = *table;
                        while (prev->next != tmp) {
                            prev = prev->next;
                        }
                        prev->next = new_item;
                    }
                    return;
                } else {
                    free(item->key);
                    free(item);
                    return;
                }
            }
            tmp = tmp->next;
        }
        if (strcmp(tmp->key, key) == 0) {
            if (tmp->Info < Info) {
                map *new_item = (map*) malloc(sizeof(map));
                new_item->key = (char*) malloc(strlen(key) + 1);
                strcpy(new_item->key, key);
                new_item->Info = Info;
                new_item->next = NULL;
                if (tmp == *table) {
                    new_item->next = *table;
                    *table = new_item;
                } else {
                    new_item->next = tmp;
                    map *prev = *table;
                    while (prev->next != tmp) {
                        prev = prev->next;
                    }
                    prev->next = new_item;
                }
                return;
            } else {
                free(item->key);
                free(item);
                return;
            }
        }
        tmp->next = item;
    }
}

int get(map **table, char *key) {
    if (*table == NULL) {
        return -1;
    }
    map *tmp = *table;
    while (tmp != NULL) {
        if (strcmp(tmp->key, key) == 0) {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return -1;
}

void set(map **table, char *key, int value) {
    if (*table == NULL) {
        return;
    }
    map *tmp = *table;
    while (tmp != NULL) {
        if (strcmp(tmp->key, key) == 0) {
            tmp->value = value;
            return;
        }
        tmp = tmp->next;
    }
}

#define MAX_LINES 100

void generate_random_charToInt_array(char arr[][MAX_LINES], int size)
{
    printf("{\n");
    for (int i = 0; i < size; i++)
    {
        printf("\t[");
        for (int j = 0; j < strlen(arr[i]); j++)
        {
            if (arr[i][j] == '\n')
            {
                if (j == strlen(arr[i]) - 1)
                {
                    printf("\"\\n\"");
                }
                else
                {
                    printf("\"\\n\",");
                }
            }
            else
            {
                printf("'%c',", arr[i][j]);
            }
        }
        printf("],\n");
    }
    printf("}\n");
    char arr[MAX_LINES][MAX_LINES];
    int num_lines = 0;

    for (int i = 0; i < MAX_LINES; i++)
    {
        memset(arr[i], ' ', MAX_LINES);
    }

    for (int i = 0; i < MAX_LINES; i++)
    {
        int num_chars = rand() % MAX_LINES + 1;
        for (int j = 0; j < num_chars; j++)
        {
            if (j == 0)
            {
                arr[i][j] = '{';
            }
            else if (j == num_chars - 1)
            {
                arr[i][j] = '}';
            }
            else
            {
                int rand_num = rand() % 3;
                if (rand_num == 0)
                {
                    arr[i][j] = '\"';
                    int string_length = rand() % (num_chars - 2) + 1;
                    for (int k = j + 1; k < j + string_length + 1 && k < num_chars - 1; k++)
                    {
                        arr[i][k] = rand() % 94 + 33;
                    }
                    j += string_length;
                    arr[i][j] = '\"';
                }
                else if (rand_num == 1)
                {
                    arr[i][j] = '\'';
                    int ascii_num = rand() % 94 + 33;
                    arr[i][j + 1] = (char) ascii_num;
                    j++;
                }
                else
                {
                    arr[i][j] = ' ';
                }
            }
        }
        arr[i][num_chars] = '\n';
        num_lines++;
    }

    print_array(arr, num_lines);

    return 0;
}

void remove_key(map **table, char *key) {
    if (*table == NULL) {
        return;
    }
    map *tmp = *table;
    if (strcmp(tmp->key, key) == 0) {
        *table = tmp->next;
        free(tmp->key);
        free(tmp);
        return;
    }
    map *prev;
    while (tmp != NULL) {
        if (strcmp(tmp->key, key) == 0) {
            prev->next = tmp->next;
            free(tmp->key);
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

bool is_valid_key(char *key) {
    for (int i = 0; i < strlen(key); i++) {
        if (!isalnum(key[i]) && key[i] != '_') {
            return false;
        }
    }
    return true;
}

void print(map **table) {
    printf("Map Contents:\n");
    map *tmp = *table;
    while (tmp != NULL) {
        printf("%s => %d\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

int hash(int key) {
    return key % ARRAY_SIZE;
}

void insert_to_array(int value) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (array[i] == 0) {
            array[i] = value;
            break;
        }
    }
}

void insert_to_hashmap(int key, char *value) {
    int index = hash(key);
    HashMapNode *node = (HashMapNode *) malloc(sizeof(HashMapNode));
    node->key = key;
    node->value = value;
    if (hashmap[index] == NULL) {
        hashmap[index] = (HashMapNode **) malloc(sizeof(HashMapNode *));
        *hashmap[index] = node;
    } else {
        int count = 0;
        HashMapNode **temp = hashmap[index];
        while (*temp != NULL) {
            temp = &((*temp)->value);
            count++;
        }
        *temp = node;
        hashmap[index] = (HashMapNode **) realloc(hashmap[index], (count+2) * sizeof(HashMapNode *));
    }
}

char *get_from_hashmap(int key) {
    int index = hash(key);
    HashMapNode **temp = hashmap[index];
    while (*temp != NULL) {
        if ((*temp)->key == key) {
            return (*temp)->value;
        }
        temp = &((*temp)->value);
    }
    return NULL;
}

void delete_from_hashmap(int key) {
    int index = hash(key);
    HashMapNode **temp = hashmap[index];
    while (*temp != NULL) {
        if ((*temp)->key == key) {
            *temp = (*temp)->value;
            return;
        }
        temp = &((*temp)->value);
    }
}



char* encrypt(char* value) {
    char* encrypted = malloc(strlen(value) + 1);
    for (int i = 0; i < strlen(value); i++) {
        encrypted[i] = value[i] + 5;
    }
    encrypted[strlen(value)] = '\0';
    return encrypted;
}

float randomize_value(float value) {
    int type = Aleatorio(1, 3);
    if (type == 1) {
        return (float)(value * 2);
    } else if (type == 2) {
        return (float)(value / 2);
    } else {
        return (float)pow(value, 2);
    }
}

void ascii_map(char* key, float value, float** map) {
    for (int i = 0; i < strlen(key); i++) {
        int index = (int)key[i];
        map[index][i] = randomize_value(value);
    }
}

void hash_map(float value, float** map) {
    float p = 0.6180339887;
    for (int i = 0; i < 1000; i++) {
        float v = (float)(value * p);
        int index = (int)(1000 * v);
        map[index][i] = randomize_value(value);
    }
}

int setValue() {
    srand(time(NULL));
    int size = Aleatorio(1, 1000);
    float** array = malloc(size * sizeof(float*));
    for (int i = 0; i < size; i++) {
        int map_size = Aleatorio(1, 1000);
        float** map = malloc(map_size * sizeof(float*));
        for (int j = 0; j < map_size; j++) {
            map[j] = malloc(1000 * sizeof(float));
        }
        array[i] = *map;
    }
    char* key = "test";
    float value = 42.0;
    char* encrypted = encrypt(key);
    ascii_map(encrypted, value, array[0]);
    hash_map(value, array[Aleatorio(0, size - 1)]);
    return 0;
}

int TesteDoHashQuickTest() {
    setValue();
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    hashmap = (HashMapNode **) malloc(ARRAY_SIZE * sizeof(HashMapNode *));
    insert_to_hashmap(1, "um");
    insert_to_hashmap(2, "dois");
    insert_to_hashmap(3, "três");
    printf("Valor do primeiro elemento do array: %d\n", array[0]);
    printf("Valor do segundo elemento do array: %d\n", array[1]);
    printf("Valor do terceiro elemento do array: %d\n", array[2]);
    printf("Valor do elemento 1 do hashmap: %s\n", get_from_hashmap(1));
    printf("Valor do elemento 2 do hashmap: %s\n", get_from_hashmap(2));
    printf("Valor do elemento 3 do hashmap: %s\n", get_from_hashmap(3));
    delete_from_hashmap(1);
    delete_from_hashmap(2);
    delete_from_hashmap(3);
    printf("Valor do primeiro elemento do array: %d\n", array[0]);
    printf("Valor do segundo elemento do array: %d\n", array[1]);
    printf("Valor do terceiro elemento do array: %d\n", array[2]);
    printf("Valor do elemento 1 do hashmap: %s\n", get_from_hashmap(1));
    printf("Valor do elemento 2 do hashmap: %s\n", get_from_hashmap(2));
    printf("Valor do elemento 3 do hashmap: %s\n", get_from_hashmap(3));
    return 0;
}
