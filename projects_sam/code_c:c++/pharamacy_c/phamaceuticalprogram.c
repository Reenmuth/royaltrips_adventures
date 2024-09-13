#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define MAX_CLIENT_ID_LENGTH 5
#define MAX_PRODUCT_NAME_LENGTH 50
#define MAX_CLIENT_NAME_LENGTH 20
#define MAX_CLIENT_EMAIL_LENGTH 50
#define MAX_PHONE_NUMBER_LENGTH 11

struct client {
    int client_ID;
    char phone_number[MAX_PHONE_NUMBER_LENGTH];
    char client_name[MAX_CLIENT_NAME_LENGTH];
    char client_email[MAX_CLIENT_EMAIL_LENGTH];
};

struct order {
    int order_number;
    int order_ref;
    int client_ID;
    char product_name[MAX_PRODUCT_NAME_LENGTH];
    int quantity;
    float price;
    char order_date[30];
};

struct product {
    char product_name[MAX_PRODUCT_NAME_LENGTH];
    float price;
};

void greeting() {
    printf("\n\tPHARMACEUTICAL COMPANY LIM\n");
    printf("..................\t................\n");
}

void heading() {
    printf("\tPharmaceutical Company LIM\n");
    printf("\t##########################\n");
}

bool is_valid_phone_number(const char* phone_number) {
    if (strlen(phone_number) != 10)
        return false;

    if (strncmp(phone_number, "07", 2) != 0 && strncmp(phone_number, "01", 2) != 0)
        return false;

    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone_number[i]))
            return false;
    }

    return true;
}
bool is_valid_email(const char* email) {
    const char* at = strchr(email, '@');
    if (at == NULL)
        return false;

    const char* dot = strrchr(at, '.');
    if (dot == NULL || dot < at + 2 || dot[1] == '\0')
        return false;

    return true;
}

bool load_client_details(struct client* clients, const char* client_id_input) {
    FILE* fp = fopen("clients.txt", "r");
    if (fp == NULL) {
        printf("Error opening client file.\n");
        return false;
    }

    // Temporary variables to read data from the file
    int temp_client_ID;
    char temp_client_name[MAX_CLIENT_NAME_LENGTH];
    char temp_phone_number[MAX_PHONE_NUMBER_LENGTH];
    char temp_client_email[MAX_CLIENT_EMAIL_LENGTH];

    // Search for the matching client ID
    while (fscanf(fp, "Client ID: %d\nClient name: %s\nClient phone number: %s\nClient email: %s\n",
                  &temp_client_ID, temp_client_name, temp_phone_number, temp_client_email) != EOF) {
        if (temp_client_ID == atoi(client_id_input)) {
            // If the client ID matches, populate the client structure with the found details
            clients->client_ID = temp_client_ID;
            strcpy(clients->client_name, temp_client_name);
            strcpy(clients->phone_number, temp_phone_number);
            strcpy(clients->client_email, temp_client_email);
            fclose(fp);
            return true; // Client found
        }
    }

    fclose(fp);
    return false; // Client not found
}

void client_details(struct client* clients, int* client_counter) {
    printf("\nEnter client details:\n");

    do {
        printf("Phone number: ");
        scanf("10%s", clients->phone_number);

        if (!is_valid_phone_number(clients->phone_number))
            printf("Invalid phone number. It should start with 07 or 01 and be 10 digits long.\n");

    } while (!is_valid_phone_number(clients->phone_number));

    printf("Client name: ");
    scanf(" %[^\n]%*c", clients->client_name);

    do {
        printf("Client email: ");
        scanf("49%s", clients->client_email);

        if (!is_valid_email(clients->client_email))
            printf("Invalid email address.\n");

    } while (!is_valid_email(clients->client_email));


    clients->client_ID = (*client_counter)++;
    printf("Your unique ID is: %d\n", clients->client_ID);

    FILE* fp = fopen("clients.txt", "a");
    fprintf(fp, "\nClient ID: %d\n", clients->client_ID);
    fprintf(fp, "Client name: %s\n", clients->client_name);
    fprintf(fp, "Client phone number: %s\n", clients->phone_number);
    fprintf(fp, "Client email: %s\n", clients->client_email);
    fprintf(fp, "__________________________\n");
    fclose(fp);

    printf("\n\tHello %s...\nWelcome to the Great Pharmaceutical Company\n", clients->client_name);
    printf("\t-------------------------\n");
    printf("Thanks for filling in the information!\n");
    printf("Proceed to the main menu.\n");
}

struct product products[] = {
    {"Antibiotics", 2500.0},
    {"Antidiabetics", 4000.50},
    {"Tablets", 1000.0},
    {"Drops", 3000.00},
    {"Injections", 2000.50},
    {"Antidepressants", 4500.50},
    {"Capsules", 4500.50},
    {"Inhalers", 1500.40},
    {"Hormones", 2300.30},
};
void generate_receipt(struct client* clients, struct order* orders);

void generate_orders(struct client* clients, int* order_counter) {
    printf("\nGenerating orders...\n");
    struct order orders;

    printf("Product name: ");
    scanf("20%s", orders.product_name);

    printf("Quantity: ");
    scanf("%d", &orders.quantity);


    orders.order_ref = (*order_counter)++;
    printf("Order reference number: %d\n", orders.order_ref);

    float price = -1.0;
    for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++) {
        if (strcmp(orders.product_name, products[i].product_name) == 0) {
            price = products[i].price;
            break;
        }
    }

    if (price == -1.0) {
        printf("Invalid product name.\n");
        return;
    }

    orders.price = price * orders.quantity;
    orders.client_ID = clients->client_ID;

    FILE* fp = fopen("orders.txt", "a");
    fprintf(fp, "Order ref: %d\n", orders.order_ref);
    fprintf(fp, "Client ID: %d\n", orders.client_ID);
    fprintf(fp, "Product name: %s\n", orders.product_name);
    fprintf(fp, "Quantity: %d\n", orders.quantity);
    fprintf(fp, "Total price: %.2f\n", orders.price);
    fprintf(fp, "_____________________\n");
    fclose(fp);

    printf("\nOrder generated successfully!\n");
    printf("Order reference number: %d\n", orders.order_ref);
    printf("Product name: %s\n", orders.product_name);
    printf("Quantity: %d\n", orders.quantity);
    printf("Total price: Ksh %.2f\n", orders.price);
    printf("Thank you for making your order.\n");

    
    generate_receipt(clients, &orders);
}

void payment_Method(struct client* clients){
    int option;
    printf("\nChoose your preferred payment method?\n");
    printf("1. Mpesa\n");
    printf("2. Global card\n");
    printf("which payment method do you prefer(use your client id as account number if mpesa method): ");
    scanf("%d", &option);

    if (option == 1){
       printf("lets walk simple steps to make payment using mpesa\n");
       printf("Use client ID: %d for your payment account.\n", clients->client_ID);
    } else if (option == 2) {
        printf("Proceed with your global card details.\n");
    } else {
        printf("Invalid payment option. Please try again.\n");
    }
    
}

void show_orders(struct client* clients) {
    printf("Generating previous orders for client %d\n", clients->client_ID);

    FILE* fp;
    struct order ref;
    char buffer[255];
    fp = fopen("orders.txt", "r");
    if (fp == NULL) {
        printf("Error in opening orders file.\n");
        return;
    }

    bool orders_found = false;

    while (fgets(buffer, sizeof(buffer), fp)) {
        // Check if the line contains the client ID for the current client
        if (sscanf(buffer, "Order ref: %d", &ref.order_ref) == 1) {
            // After finding order ref, proceed to read the rest of the order
            fscanf(fp, "Client ID: %d\n", &ref.client_ID);
            fscanf(fp, "Product name: %s\n", ref.product_name);
            fscanf(fp, "Quantity: %d\n", &ref.quantity);
            fscanf(fp, "Total price: %f\n", &ref.price);
            fgets(buffer, sizeof(buffer), fp); // Skip the separator line

            // If the client ID matches, display the order details
            if (ref.client_ID == clients->client_ID) {
                orders_found = true;
                printf("\nOrder reference: %d\n", ref.order_ref);
                printf("Client ID: %d\n", ref.client_ID);
                printf("Product name: %s\n", ref.product_name);
                printf("Quantity: %d\n", ref.quantity);
                printf("Total price: Ksh%.2f\n", ref.price);
                printf("------------------------\n");
            }
        }
    }

    if (!orders_found) {
        printf("No orders found for client ID %d.\n", clients->client_ID);
    }

    fclose(fp);
}

void services(struct client* clients) {
    struct order orders;

    printf("\nWe offer delivery services for your convenience.\n");
    printf("Enter code generated after payment: ");
    printf("\nEnter your address and destination to proceed: ");
    char address[10];  
    scanf("%s", address);
    printf("Thank you!\nOnce you place your order, it will be delivered within 48 hours to %s. Order reference: %d\n", address, orders.order_ref);
}

void products_offered() {
    printf("\n\nProducts offered include:\n");
    printf("........................\n");
    for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++) {
        printf("%s\n", products[i].product_name);
    }
    printf("___________________\n");
}
void generate_receipt(struct client* clients, struct order* orders) {
    char receipt_filename[50];
    sprintf(receipt_filename, "receipt_%d.txt", orders->order_ref);
    FILE* fp = fopen(receipt_filename, "a");

    if (fp == NULL) {
        printf("Error generating receipt.\n");
        return;
    }

    fprintf(fp, "----------------------------------\n");
    fprintf(fp, "      PHARMACEUTICAL COMPANY LIM      \n");
    fprintf(fp, "----------------------------------\n");
    fprintf(fp, "Receipt for Order Reference: %d\n", orders->order_ref);
    fprintf(fp, "----------------------------------\n");
    fprintf(fp, "Client Name: %s\n", clients->client_name);
    fprintf(fp, "Client Phone Number: %s\n", clients->phone_number);
    fprintf(fp, "Client Email: %s\n", clients->client_email);
    fprintf(fp, "----------------------------------\n");
    fprintf(fp, "Product Ordered: %s\n", orders->product_name);
    fprintf(fp, "Quantity: %d\n", orders->quantity);
    fprintf(fp, "Total Price: Ksh%.2f\n", orders->price);
    fprintf(fp, "----------------------------------\n");
    fprintf(fp, "Thank you for your purchase!\n");
    fprintf(fp, "----------------------------------\n");
    fprintf(fp, "======================================\n");

    fclose(fp);

    printf("\nReceipt generated successfully!\n");
    printf("You can find your receipt in the file: %s\n", receipt_filename);
}


void help_details() {
    printf("Here for Assistance\n");
}

int main() {
    greeting();
    heading();

    int order_counter = 1000;
    int client_counter = 100;

    struct client clients;
    int option;
    bool client_details_provided = false; // Flag variable to keep track of whether client details have been provided
    char client_id_input[MAX_CLIENT_ID_LENGTH];
    int client_id_provided;
    
    // Ask the user if they already have a client ID
    printf("Do you have a client ID? (1 for Yes, 0 for No): ");
    scanf("%d", &client_id_provided);

    // If the client has an ID, proceed to the main menu after asking for the ID
    if (client_id_provided == 1) {
        printf("Please enter your client ID: ");
        scanf("%s", client_id_input);

        // Here you would typically load client details from a file or database
        if (load_client_details(&clients, client_id_input)) {
            // If client details are loaded successfully, show the client name
            printf("\nWelcome back, %s!\n", clients.client_name);
            client_details_provided = true;
        } else {
            // If client ID is not found, notify the user
            printf("\nClient ID not found. Please register as a new client.\n");
            client_details(&clients, &client_counter);
            client_details_provided = true;
        }
        
    } else {
        // If the client does not have an ID, register a new client
        printf("\nYou need to register as a new client.\n");
        client_details(&clients, &client_counter); // Function that collects client details
        client_details_provided = true;
    }

    do {
        printf("\nSelect an option to proceed:\n");
        printf("1. Generate orders\n");
        printf("2. Show all orders\n");
        printf("3. Method of payment\n");
        printf("4. Delivery services(You must have made payment for this service).\n");
        printf("5. Help\n");
        printf("6. Products available\n");
        printf("7. Exit\n");

        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                generate_orders(&clients, &order_counter);
                break;

            case 2:
                show_orders(&clients);
                break;

            case 3:
                payment_Method(&clients);  
                break;

            case 4:
                services(&clients);
                break;

            case 5:
                help_details();
                break;

            case 6:
                products_offered();
                break;

            case 7:
                printf("\nThank you for using our service. Goodbye!\n");
                break;

            default:
                printf("\nInvalid option selected. Please try again.\n");
                break;
        }

    } while (option != 7);

    return 0;
}
