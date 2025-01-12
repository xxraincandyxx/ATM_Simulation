#include <stdbool.h>
#include <stdio.h>

#ifndef SERVER_H
#define SERVER_H

#define MAX_USERS 100           // Maximum number of users
#define MAX_TRANS_NUM 1000      // Maximum number of transactions
#define ACCOUNT_ID_LENGTH 30    // Maximum length of account ID
#define ACCOUNT_NAME_LENGTH 30  // Maximum length of account name
#define PASSWORD_LENGTH 30      // Maximum length of password
#define CIPHER_SIZE 16          // Cipher size

typedef struct AccountInfo Account;
typedef struct TransferInfo Transfer;

struct TransferInfo {
    double pre_balance, post_balance;                  // Balance change
    unsigned char target_card_id_cipher[CIPHER_SIZE];  // Target account ID
};

struct AccountInfo {
    int acc_no;                                  // Index
    unsigned char firstname[30];                 // First name
    unsigned char lastname[30];                  // Last name
    unsigned char card_id_cipher[CIPHER_SIZE];   // Card number
    unsigned char password_cipher[CIPHER_SIZE];  // Password
    double balance;                              // Balance
    Transfer transaction_hist[MAX_TRANS_NUM];    // Transaction history
};

void login(FILE* db);         // Login menu
void registration(FILE* db);  // Registration menu

void mainMenu();                              // Main menu
bool userMenu(const unsigned char* card_id);  // Main menu

// User-related functions
void transfer(Account* fromAccount, Account* toAccount,
              double amt);  // Transfer funds

// Registering-related functions
void _init_acc_transinfo(Account* ptr_usr_data);
void register_user(FILE* db);

// Administrator-related functions
void adminLogin();               // Admin login
void adminMenu();                // Admin menu
void addUser(FILE* db);          // Add users
void listAllUserInfo(FILE* db);  // List all user information

// Clear screen function
void clearScreen();
void invalidInputWarning();

// Encryption-related
// API Calls
void demo();
int get_cipher_size();
int get_key_size();
void encryptor(const unsigned char* input, unsigned char* cipher);
void decryptor(const unsigned char* cipher, unsigned char* output);

// Forecast-related
//
typedef struct {
    double* values;  // Array to store forecasted values
    int count;       // Number of forecasted values
} ForecastResult;
ForecastResult linear_forecast(double *data, int data_size, int forecast_count);

#endif
