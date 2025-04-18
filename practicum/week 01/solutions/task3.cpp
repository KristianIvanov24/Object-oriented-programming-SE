#include <iostream>
#include <cstring>

// Дефиниране на напитките като степени на 2, за да можем да използваме битови операции
enum Drink {
    WHISKEY = 1,    // 00000001
    VODKA = 2,      // 00000010
    COLA = 4,       // 00000100
    FANTA = 8,      // 00001000
    WATER = 16,     // 00010000
    WINE = 32,      // 00100000
    RUM = 64,       // 01000000
    JUICE = 128     // 10000000
};

struct Client {
    char name[32]; // 31 + '\0'
    unsigned char preferredDrinks; // Битова маска за предпочитаните напитки
};

Client createClient(const char* name) {
    Client newClient;
    strncpy(newClient.name, name, 31);
    newClient.name[31] = '\0';
    newClient.preferredDrinks = 0;
    return newClient;
}

bool doesClientLikeDrink(const Client& client, Drink drink) {
    return (client.preferredDrinks & drink) != 0;
}

void addDrinkPreference(Client& client, Drink drink) {
    client.preferredDrinks |= drink;
}

void removeDrinkPreference(Client& client, Drink drink) {
    client.preferredDrinks &= ~drink;
}
