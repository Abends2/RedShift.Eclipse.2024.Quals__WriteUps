#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define TEXT_SIZE 32
#define HASH_SIZE 64
#define NUM_ROUNDS 10
#define SALT "some_random_salt"
#define KEY "13579;=?A9KMOQSUACEGIKMOQI[]_ace"

typedef void (*TransformFunc)(char *, const unsigned char *);


void processCommandLineArguments(int argc, char *argv[], char *text) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--str") == 0) {
            if (i + 1 < argc) {
                strncpy(text, argv[i + 1], TEXT_SIZE);
                text[TEXT_SIZE] = '\0'; // Убеждаемся, что строка заканчивается нулевым символом
                return;
            } else {
                printf("Error: Missing argument after %s\n", argv[i]);
                exit(1);
            }
        }
    }
}

// Пример обфускации ключа
const char* getObfuscatedKey() {
    static char obfuscatedKey[HASH_SIZE + 1] = {0};
    if (obfuscatedKey[0] == 0) {
        const char* key = "13579;=?A9KMOQSUACEGIKMOQI[]_ace";
        for (int i = 0; i < strlen(key); i++) {
            obfuscatedKey[i] = key[i] ^ 0x5A; // XOR with a simple mask
        }
    }
    return obfuscatedKey;
}

// Рандомизированная задержка для обфускации времени выполнения
void randomDelay() {
    for (volatile int i = 0; i < rand() % 100000; i++) {
        // Пустое тело цикла
    }
}

void xorTransform(char *data, const unsigned char *key) {
    int i, key_len = strlen((const char*)key);
    randomDelay();  // Вставка задержки
    for (i = 0; i < HASH_SIZE; i++) {
        data[i] ^= key[i % key_len];
    }
}

void mixTransform(char *data, const unsigned char *key) {
    int i, key_len = strlen((const char*)key);
    for (i = 0; i < HASH_SIZE; i++) {
        int swap_idx = (key[i % key_len] + i) % HASH_SIZE;
        char temp = data[i];
        data[i] = data[swap_idx];
        data[swap_idx] = temp;
    }
}

void rotateTransform(char *data, const unsigned char *key) {
    int i, key_len = strlen((const char*)key);
    for (i = 0; i < HASH_SIZE; i++) {
        int rnd = (key[i % key_len] % 7) + 1;
        data[i] = (data[i] << rnd) | (data[i] >> (8 - rnd));
    }
}

void complexEncryptDecrypt(char *data, const unsigned char *key, TransformFunc *transforms, int numTransforms) {
    int round, i;
    for (round = 0; round < NUM_ROUNDS; round++) {
        for (i = 0; i < numTransforms; i++) {
            transforms[i](data, key);
        }
    }
}

void reversibleHash(char *input, char *output) {
    memset(output, 0, HASH_SIZE); // Обнуляем выходную строку

      for (int i = 0; i < TEXT_SIZE; i++) {
                uint32_t currentChar = (unsigned char)input[i];  // Работаем в 32-битном режиме

        // Применяем различные биективные операции:
        currentChar += 7;    // Добавляем константу
        currentChar ^= 29;   // XOR с константой
        currentChar *= 13;   // Умножаем на простое число
        currentChar = ~currentChar;  // Битовое NOT
        currentChar += (currentChar << 3); // Сложение с самим собой со сдвигом
        currentChar ^= (currentChar >> 5); // XOR со сдвигом
        currentChar *= 199;  // Умножаем на другое простое число
        currentChar ^= (currentChar << 4); // XOR с сдвигом
        currentChar += 91;   // Добавляем другую константу
        currentChar ^= 111;  // XOR с другой константой
        currentChar = (currentChar << 1) | (currentChar >> (31 - 1)); // Циклический сдвиг
        currentChar *= 251;  // Умножаем на простое число
        currentChar ^= (currentChar >> 2); // XOR со сдвигом
        currentChar += 58;   // Добавляем константу
        currentChar ^= 171;  // Еще один XOR с константой

        // Используем младший байт для вывода
        output[i] = currentChar % 256;
    } 
   output[TEXT_SIZE] = '\0'; // Устанавливаем завершающий нулевой символ для корректной работы со строками
}


void decryptKey(char* key) {
    const char* obfuscatedKey = getObfuscatedKey();
    int keyLen = strlen(obfuscatedKey);
    for (int i = 0; i < keyLen; ++i) {
        key[i] = obfuscatedKey[i] ^ 0x5A; // Расшифровка
    }
}

int main(int argc,char *argv[]) {
    char text[TEXT_SIZE + 1];
    processCommandLineArguments(argc, argv, text);
    char hashed_text[HASH_SIZE + 1];
    unsigned char key[HASH_SIZE + 1];
    decryptKey((char*)key);
    TransformFunc transforms[3] = {xorTransform, mixTransform, rotateTransform};
    reversibleHash(text, hashed_text);
    for(int i = 0; i < strlen(hashed_text); i++)
    {
        printf("%x",hashed_text[i]);
    }
    printf("\n");
        complexEncryptDecrypt(hashed_text, key, transforms, 3);
    char *filename = "encrypted_output.txt";    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }
    fprintf(file, "%s\n", hashed_text);
    fclose(file);

    return 0;

  }
