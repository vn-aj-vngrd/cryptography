#include "functions.h"

/************************************************************************************************************************
 * Main Functions
 ************************************************************************************************************************/

char *encrypt(char plaintext[])
{
    int len = strlen(plaintext);
    char *ciphertext = (char *)calloc(len + 1, sizeof(char));
    memcpy(ciphertext, plaintext, len + 1);

    rsa_encrypt(ciphertext);
    atbash(ciphertext);

    return ciphertext;
}

char *decrypt(char ciphertext[], char key[])
{
    int len = strlen(ciphertext);
    char *plaintext = (char *)calloc(len + 1, sizeof(char));
    memcpy(plaintext, ciphertext, len + 1);

    atbash(plaintext);
    rsa_decrypt(plaintext, key);

    return plaintext;
}

/************************************************************************************************************************
 * Cryptograph Functions
 ************************************************************************************************************************/

/*
 * Encrypt the plaintext via RSA
 *
 * @param plaintext
 */

void rsa_encrypt(char plaintext[])
{
    // Two prime numbers
    int p;
    int q;
    int r;
    int s;

    printf("\n\nEnter 4 different prime numbers: ");
    scanf("%d %d %d %d", &p, &q, &r, &s);
    fflush(stdin);

    // Let N = p * q * r * s
    int n = p * q * r * s;

    // Get the Euler Totient
    int t = (p - 1) * (q - 1) * (r - 1) * (s - 1);

    // (e * d) mod t = 1
    int e = calculateE(n, t);
    int d = calculateD(e, t);

    // For debugging purpose
    // printf("e: %d\nd: %d\nt: %d\nn: %d\n", e, d, t, n);

    // delimiter
    char delim = ',';

    int delim_size = 1;
    int e_size = floor(log10(abs(e))) + 1;
    int d_size = floor(log10(abs(d))) + 1;
    int n_size = floor(log10(abs(n))) + 1;

    int private_key_size = d_size + delim_size + n_size + 1;
    int public_key_size = e_size + delim_size + n_size + 1;

    // Save private key
    char *private_key = (char *)calloc(private_key_size, sizeof(char));
    sprintf(private_key, "%d%c%d", d, delim, n);
    printf("\nPrivate Key: %s\n", private_key);
    saveTextToFile(private_key, "private key");

    // Save public key
    char *public_key = (char *)calloc(public_key_size, sizeof(char));
    sprintf(public_key, "%d%c%d", e, delim, n);
    printf("\n\nPublic Key: %s\n", public_key);
    saveTextToFile(public_key, "public key");

    // Declare bignum variables
    // M -> plaintext
    // C -> ciphertext
    // E -> public key 1, exponent
    // N -> public key 2, modulus
    struct bn M, C, E, N;

    // Initialize bignum variables
    bignum_init(&M);
    bignum_init(&C);
    bignum_init(&E);
    bignum_init(&N);

    // Encryption Process
    int i;
    for (i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            // Assign bignum
            bignum_from_int(&M, toupper(plaintext[i]) - 'A' + 1);
            bignum_from_int(&E, e);
            bignum_from_int(&N, n);

            // Calculate C = (M ^ E) % N
            bignum_pow_mod(&M, &E, &N, &C);

            // Convert C to int and mod 26
            int c = bignum_to_int(&C) % 26;

            //  Convert it to its orignal ascii
            plaintext[i] = isupper(plaintext[i]) ? c + 'A' - 1 : c + 'a' - 1;
        }
        else
        {
            plaintext[i] = plaintext[i];
        }
    }
}

/*
 * Decrypt the ciphertext via RSA
 *
 * @param ciphertext
 * @param key
 */

void rsa_decrypt(char ciphertext[], char key[])
{
    char delim[] = ",";
    char *token;

    // Get the d
    char *d_str = strtok(key, delim);
    int d = atol(d_str);

    // Get the n
    char *n_str = strtok(NULL, delim);
    int n = atol(n_str);

    // For debugging purpose
    // printf("d: %d\nn: %d\n", d, n);

    // Declare bignum variables
    // M -> plaintext
    // C -> ciphertext
    // D -> private key 1, exponent
    // N -> private key 2, modulus
    struct bn M, C, D, N;

    // Initialize bignum variables
    bignum_init(&M);
    bignum_init(&C);
    bignum_init(&D);
    bignum_init(&N);

    // Decryption
    int i;
    for (i = 0; i < strlen(ciphertext); i++)
    {
        if (isalpha(ciphertext[i]))
        {
            // Assign bignum
            bignum_from_int(&C, toupper(ciphertext[i]) - 'A' + 1);
            bignum_from_int(&D, d);
            bignum_from_int(&N, n);

            // Calculate M = (C ^ D) % N
            bignum_pow_mod(&C, &D, &N, &M);

            // Convert M to int and mod 26
            int m = bignum_to_int(&M) % 26;

            //  Convert it to its orignal ascii
            ciphertext[i] = isupper(ciphertext[i]) ? m + 'A' - 1 : m + 'a' - 1;
        }
        else
        {
            ciphertext[i] = ciphertext[i];
        }
    }
}

/*
 * Encrypt/Decrypt the text via Atbash
 *
 * @param text
 */

void atbash(char text[])
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            text[i] = isupper(text[i]) ? 'Z' - (text[i] - 'A') : 'z' - (text[i] - 'a');
        }
    }

    strrev(text);
}

/************************************************************************************************************************
 * Helper Functions
 ************************************************************************************************************************/

/*
 * E must be less than t
 * E must be coprime with n and t
 */

int calculateE(int n, int t)
{
    int e;

    for (e = 2; e < t; e++)
    {
        if (e % 2 != 0 && (n % e) != 0 && (t % e) != 0)
        {
            return e;
        }
    }

    return -1;
}

/*
 * loop through the multiples of e
 * Display all candidates when m mod t is 1
 * Allow user to select a d value from the displayed d candidates
 */

int calculateD(int e, int t)
{
    int d, m, val;

    printf("List of d candidates: ");

    for (d = 1, m = e; d < MAX_D; m += e, d++)
    {
        if (d != e && m % t == 1)
        {
            printf("%d ", d);
        }
    }

    printf("\nChoose one d candidate from above: ");
    scanf("%d", &val);
    fflush(stdin);

    return val;
}

/*
 * Format text in numbers
 *
 * @param text: text in string
 * @return textNum: text in numbers
 */

int *formatTextInNum(char text[])
{
    int i;
    int *textNum = (int *)calloc(strlen(text) + 1, sizeof(int));

    for (i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            textNum[i] = toupper(text[i]) - 'A' + 1;
        }
        else
        {
            textNum[i] = text[i];
        }
    }

    return textNum;
}

/************************************************************************************************************************
 * Utility Functions
 ************************************************************************************************************************/

/*
 * This function gets the text from a file.
 *
 * @param text The text to be read from the file.
 *
 * @return 1 if the text is read successfully, 0 otherwise.
 */

int getTextFromFile(char text[], char type[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to open %s: ", type);
    scanf("%[^\n]", filename);
    fflush(stdin);

    FILE *file = fopen(strcat(filename, ".txt"), "r");
    if (!file)
    {
        return 0;
    }

    fgets(text, MAX_SIZE, file);
    fclose(file);

    return 1;
}

/*
 * This function saves the string text to a file.
 *
 * @param text The text to be saved to the file.
 * @param type The type of the text.
 */

void saveTextToFile(char text[], char type[])
{
    char filename[MAX_SIZE];

    printf("Enter filename to save %s: ", type);
    scanf("%[^\n]", filename);
    fflush(stdin);

    FILE *file = fopen(strcat(filename, ".txt"), "w");
    if (!file)
    {
        return;
    }

    fprintf(file, "%s", text);
    fclose(file);

    printf("File saved successfully.");
}

/*
 * This function prints the text.
 *
 * @param text The text to be printed.
 */

void displayNumText(int text[])
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%d ", text[i]);
    }
}

/*
 * This function displays the menu.
 */

int menu()
{
    int choice;

    printf("-----------------\n");
    printf("Van's Cryptograph\n");
    printf("-----------------\n");
    printf("[1] Encrypt\n");
    printf("[2] Decrypt\n");
    printf("[3] Exit\n");
    printf("\nSelect: ");

    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}