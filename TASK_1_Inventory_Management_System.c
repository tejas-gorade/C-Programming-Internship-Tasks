#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definition for Product
struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
};

// Function Prototypes
void addProduct();
void displayProducts();
void searchProduct();
void updateProduct();
void deleteProduct();

void addProduct() {
    FILE *fp = fopen("inventory.dat", "ab"); // append in binary
    struct Product p;

    if (fp == NULL) {
        printf("\nError: Could not open file!\n");
        return;
    }

    printf("Enter Product ID: ");
    scanf("%d", &p.id);
    printf("Enter Product Name: ");
    scanf(" %[^\n]", p.name); // Using space before % to consume any leftover newline
    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);
    printf("Enter Price: ");
    scanf("%f", &p.price);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("Product Added Successfully!\n");
}

void displayProducts() {
    FILE *fp = fopen("inventory.dat", "rb");
    struct Product p;

    if (fp == NULL) {
        printf("\n No products found!\n");
        return;
    }

    printf("\n----- Inventory List -----\n");
    printf("%-10s %-20s %-10s %-10s\n", "ID", "Name", "Quantity", "Price");
    printf("------------------------------------------------------------\n");

    while (fread(&p, sizeof(p), 1, fp)) {
        printf("%-10d %-20s %-10d %-10.2f\n", p.id, p.name, p.quantity, p.price);
    }

    fclose(fp);
}

void searchProduct() {
    FILE *fp = fopen("inventory.dat", "rb");
    struct Product p;
    int id, found = 0;

    if (fp == NULL) {
        printf("\nNo products found!\n");
        return;
    }

    printf("Enter Product ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("\nProduct Found!\n");
            printf("ID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n", p.id, p.name, p.quantity, p.price);
            found = 1;
            break;
        }
    }

    if (!found) printf("\nProduct not found!\n");
    fclose(fp);
}

void updateProduct() {
    FILE *fp = fopen("inventory.dat", "rb+");
    struct Product p;
    int id, found = 0;

    if (fp == NULL) {
        printf("\nNo products found!\n");
        return;
    }

    printf("Enter Product ID to update: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", p.name);
            printf("Enter New Quantity: ");
            scanf("%d", &p.quantity);
            printf("Enter New Price: ");
            scanf("%f", &p.price);

            // Move the file pointer back to the start of the record
            fseek(fp, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);
            found = 1;
            printf("Product Updated Successfully!\n");
            break;
        }
    }

    if (!found) printf("\nProduct not found!\n");
    fclose(fp);
}

void deleteProduct() {
    FILE *fp = fopen("inventory.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Product p;
    int id, found = 0;

    if (fp == NULL) {
        printf("\nNo products found!\n");
        if (temp) fclose(temp);
        return;
    }

    printf("Enter Product ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            found = 1;
            continue; // Skip writing this record to the temp file
        }
        fwrite(&p, sizeof(p), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    if (found)
        printf("Product Deleted Successfully!\n");
    else
        printf("Product not found!\n");
}

int main() {
    int choice;

    do {
        printf("\n===== Inventory Management System =====\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search Product\n");
        printf("4. Update Product\n");
        printf("5. Delete Product\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: printf("🚪 Exiting...\n"); break;
            default: printf("Invalid Choice!\n");
        }
    } while (choice != 6);

    return 0;
}