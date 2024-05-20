#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MESSAGES 5
#define BUFFER_SIZE 256
#define CAPTION_SIZE 100

typedef struct {
    char encryptedMessage[BUFFER_SIZE];
    char caption[CAPTION_SIZE];
} EncryptedMessage;

EncryptedMessage messages[MAX_MESSAGES];
int message_count = 0;
char key[32];

char step1_unlocked = 0;
char step2_unlocked = 0;
char step3_unlocked = 0;
char step4_unlocked = 0;
char flag[] = "EclipseCTF{All_Step3_Complet3d_1s_n1se_sceel}";

unsigned char ror(unsigned char val, int n) {
    return (val >> n) | (val << (8 - n));
}

void xor_encrypt_decrypt(char *input, char *output, int data_len) {
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; i < data_len; ++i) {
        unsigned char enc_char = input[i] ^ key[key_index];
        output[i] = ror(enc_char, key_index % 8);
        key_index = (key_index + 1) % key_len;
    }
    output[data_len] = '\0';
}

void generate_key() {
    strcpy(key, "default_secret_key_123456"); // Simple and guessable key
}

void encrypt_message() {
    char overflow_buf[64];
    gets(overflow_buf); 
    if (!step1_unlocked) {
        printf("Step 1 is not unlocked yet!\n");
        return;
    }

    char buffer[128];
    printf("Enter your message to encrypt (up to 127 characters): ");
    fgets(buffer, 256, stdin); // Buffer overflow vulnerability
    buffer[strcspn(buffer, "\n")] = 0;
    int buffer_len = strlen(buffer);
    char encrypted[buffer_len + 1];
    xor_encrypt_decrypt(buffer, encrypted, buffer_len);
    if (message_count < MAX_MESSAGES) {
        strcpy(messages[message_count].encryptedMessage, encrypted);
        printf("Enter a short caption for the message: ");
        fgets(messages[message_count].caption, CAPTION_SIZE, stdin);
        messages[message_count].caption[strcspn(messages[message_count].caption, "\n")] = 0;
        message_count++;
        printf("Message encrypted!\n");
        step2_unlocked = 1; // Unlock step 2 after first message encryption
    } else {
        printf("No more space to store messages.\n");
    }
}

void view_messages() {
    if (!step2_unlocked) {
        printf("Step 2 is not unlocked yet!\n");
        return;
    }

    int i, choice;
    printf("Encrypted messages:\n");
    for (i = 0; i < message_count; i++) {
        printf("%d. %s\n", i + 1, messages[i].caption);
    }
    printf("Enter message number to view the encrypted content or 0 to reveal a secret: ");
    char choice_str[16];
    scanf("%15s", choice_str); // Format string vulnerability with scanf
    choice = atoi(choice_str);

    if (choice == 0 && step3_unlocked) {
        printf("Here's your flag: %s\n", flag); // Directly reveal the flag only if all steps are unlocked
        return;
    }

    if (choice < 1 || choice > message_count) {
        printf("Invalid choice!\n");
    } else {
        printf("Encrypted content of message %d: ", choice);
        printf(messages[choice - 1].encryptedMessage); // Format string vulnerability
        printf("\n");
    }
}

int main() {
    setbuf(stdout, NULL); // Disable buffering
    generate_key();
    int choice;

    printf("Perform buffer overflow to unlock step 1.\n"); // Hint for participants
    // Dangerous, allows buffer overflow to manipulate flow

    while (1) {
        printf("1. Encrypt a message\n2. View encrypted messages\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);
        getchar(); // Consume newline
        switch (choice) {
            case 1:
                encrypt_message();
                break;
            case 2:
                view_messages();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
