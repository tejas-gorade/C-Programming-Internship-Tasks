#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "inventory.dat"

struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
};

void clearBuffer() {
    while (getchar() != '\n');
}

int idExists(int id) {
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Product p;

    if (!fp) return 0;

    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (p.id == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void addProduct() {
    FILE *fp = fopen(FILE_NAME, "ab");
    struct Product p;

    if (!fp) {
        printf("File error!\n");
        return;
    }

    printf("Enter ID: ");
    if (scanf("%d", &p.id) != 1 || p.id <= 0) {
        printf("Invalid ID!\n");
        clearBuffer();
        fclose(fp);
        return;
    }

    if (idExists(p.id)) {
        printf("ID already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    if (scanf(" %49[^\n]", p.name) != 1) {
        printf("Invalid name!\n");
        clearBuffer();
        fclose(fp);
        return;
    }

    printf("Enter Quantity: ");
    if (scanf("%d", &p.quantity) != 1 || p.quantity < 0) {
        printf("Invalid quantity!\n");
        clearBuffer();
        fclose(fp);
        return;
    }

    printf("Enter Price: ");
    if (scanf("%f", &p.price) != 1 || p.price < 0) {
        printf("Invalid price!\n");
        clearBuffer();
        fclose(fp);
        return;
    }

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("Product added successfully!\n");
}

void displayProducts() {
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Product p;

    if (!fp) {
        printf("No records found.\n");
        return;
    }

    printf("\nID\tName\t\tQty\tPrice\n");

    while (fread(&p, sizeof(p), 1, fp) == 1) {
        printf("%d\t%s\t%d\t%.2f\n", p.id, p.name, p.quantity, p.price);
    }

    fclose(fp);
}

void deleteProduct() {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Product p;
    int id, found = 0;

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    printf("Enter ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        fclose(fp); fclose(temp);
        return;
    }

    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (p.id == id) {
            found = 1;
            continue;
        }
        fwrite(&p, sizeof(p), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("Deleted successfully!\n");
    else
        printf("ID not found.\n");
}

int main() {
    int choice;

    do {
        printf("\n--- Inventory System ---\n");
        printf("1. Add\n2. Display\n3. Delete\n4. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: deleteProduct(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice\n");
        }

    } while (choice != 4);

    return 0;
}
