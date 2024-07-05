#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100

/*********************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the
concepts learned. I have constructed the functions and their respective algorithms and corresponding code by
myself. The program was run, tested, and debugged by my own efforts. I further certify that I have not copied in
part or whole or otherwise plagiarized the work of other students and/or persons.
<Cassandra Erika R. Jalandoni>, DLSU ID# <12207640> S14
**********************************************************************************************/

typedef struct {
    char id[6]; // at most 5 characters 
    char name[31];// at most 30 characters 
    int quantity;
    float price;
} Product;

typedef struct {
    Product inventory[MAX_PRODUCTS];
    int count;
} Inventory;

/****************************************  
	Function: loadInventory
	Description: This function loads the inventory from a file.
	@param: Inventory* inv, Product p
	@return: void
*****************************************/

void loadInventory(Inventory *inv) {
    FILE *file = fopen("inventory.txt", "r");
    if(file == NULL) {
        printf("Error opening file\n");
        return;
    }
    
    Product p;
    while(fscanf(file, "%[^,],%[^,],%d,%f\n", p.id, p.name, &p.quantity, &p.price) != EOF) {
        strcpy(inv->inventory[inv->count].id, p.id);
        strcpy(inv->inventory[inv->count].name, p.name);
        inv->inventory[inv->count].quantity = p.quantity;
        inv->inventory[inv->count].price = p.price;
        inv->count++;
    }
    if(inv->count==0)
    {
    	printf("inventory is EMPTY.../n");
	}

    fclose(file);
}

/****************************************  
	Function: sortInventoryByName
	Description: This function sorts the inventory alphabetically.
	@param: Inventory* inv, int i, int j
	@return: void
*****************************************/ 

void sortInventoryByName(Inventory *inv) {
    int i, j;
    Product temp;

    for (i = 0; i < inv->count - 1; i++) {
        for (j = 0; j < inv->count - i - 1; j++) {
            if (strcmp(inv->inventory[j].name, inv->inventory[j + 1].name) > 0) {
                // Swap the products
                temp = inv->inventory[j];
                inv->inventory[j] = inv->inventory[j + 1];
                inv->inventory[j + 1] = temp;
            }
        }
    }
}

/****************************************  
	Function: sortInventoryById
	Description: This function sorts the inventory by product ID.
	@param: Inventory* inv, int i, int j
	@return: void
*****************************************/ 

void sortInventoryById(Inventory *inv) {
    int i, j;
    Product temp;

    for (i = 0; i < inv->count - 1; i++) {
        for (j = 0; j < inv->count - i - 1; j++) {
            if (strcmp(inv->inventory[j].id, inv->inventory[j + 1].id) > 0) {
                // Swap the products
                temp = inv->inventory[j];
                inv->inventory[j] = inv->inventory[j + 1];
                inv->inventory[j + 1] = temp;
            }
        }
    }
}

/****************************************  
	Function: isProductIdExists
	Description: This function compares product ids if there is a repetition
				 if yes it returns 1
	@param: Inventory* inv, char id, int i
	@return: returns 1 or 0
*****************************************/ 

int isProductIdExists(Inventory *inv, const char* id) {
	int i;
    for (i = 0; i < inv->count; i++) {
        if (strcmp(inv->inventory[i].id, id) == 0) {
            return 1;
        }
    }
    return 0;
}

/****************************************  
	Function: viewInventory
	Description: This function displays the current inventory.
	@param: Inventory* inv, int i
	@return: void
*****************************************/ 

void viewInventory(Inventory *inv) {
	sortInventoryByName(inv);
	int i;
    for(i = 0; i < inv->count; i++) {
        printf("ID: %s, Name: %s, Quantity: %d, Price: %.2f\n", inv->inventory[i].id, inv->inventory[i].name, inv->inventory[i].quantity, inv->inventory[i].price);
    }
}

/****************************************  
	Function: viewInventoryById
	Description: This function displays the current inventory sorted by product ID.
	@param: Inventory* inv, int i
	@return: void
*****************************************/ 

void viewInventoryById(Inventory *inv) {
	sortInventoryById(inv);
	int i;
    for(i = 0; i < inv->count; i++) {
        printf("ID: %s, Name: %s, Quantity: %d, Price: %.2f\n", inv->inventory[i].id, inv->inventory[i].name, inv->inventory[i].quantity, inv->inventory[i].price);
    }
}

/****************************************  
	Function: addProduct
	Description: This function adds a new product to the inventory.
	@param: Inventory* inv
	@return: void
*****************************************/ 


void addProduct(Inventory *inv) {
    if(inv->count == MAX_PRODUCTS) {
        printf("Inventory full\n");
        return;
    }
if (inv->count == MAX_PRODUCTS) {
        printf("Inventory full\n");
        return;
    }

    Product newProduct;
    
    do{
        printf("Enter product ID: ");
        scanf("%s", newProduct.id);
        
        if(atoi(newProduct.id)<0)
        {
        	printf("id cannot be a NEGATIVE number. Please enter new id\n");
		}

        if (isProductIdExists(inv, newProduct.id)) {
            printf("Product ID already exists. Please enter a different ID.\n");
        }
    } while (isProductIdExists(inv, newProduct.id) || atoi(newProduct.id)<0);

    printf("Enter product name: ");
    //scanf("%s", newProduct.name);
    int ch;
    while((ch=getchar()) !='\n'&& ch !=EOF);
    fgets(newProduct.name,sizeof(newProduct.name),stdin);
    
    do{
    printf("Enter quantity: ");
    scanf("%d", &newProduct.quantity);
    if(newProduct.quantity<0)
    {
    	printf("quantity cannot be NEGATIVE. Please enter new quantity\n");
	}
	}while(newProduct.quantity<0);
	
	do{
    printf("Enter price: ");
    scanf("%f", &newProduct.price);
    if(newProduct.price<0)
    {
    	printf("price cannot be NEGATIVE. Please enter new quantity\n");
	}
	}while(newProduct.price<0);

    strcpy(inv->inventory[inv->count].id, newProduct.id);
    strcpy(inv->inventory[inv->count].name, newProduct.name);
    inv->inventory[inv->count].quantity = newProduct.quantity;
    inv->inventory[inv->count].price = newProduct.price;

    inv->count++;
    printf("new product succesfully added!\n");
}


/****************************************  
	Function: updateProductQuantity
	Description: This function updates the quantity of a product in the inventory.
	@param: Inventory* inv, int i
	@return: void
*****************************************/ 

void updateProductQuantity(Inventory *inv) {
    char id[6];
    printf("Enter product ID: ");
    scanf("%s", id);
    int i;

    for(i=0; i<inv->count; i++) {
        if(strcmp(inv->inventory[i].id, id) == 0) {
            printf("Enter new quantity: ");
            scanf("%d", &inv->inventory[i].quantity);
            return;
        }
    }

    printf("Product not found\n");
}

/****************************************  
	Function: updateProductPrice
	Description: This function updates the price of a product in the inventory.
	@param: Inventory* inv, int i
	@return: void
*****************************************/ 

void updateProductPrice(Inventory *inv) {
    char id[6];
    printf("Enter product ID: ");
    scanf("%s", id);
    int i;

    for(i=0; i<inv->count; i++) {
        if(strcmp(inv->inventory[i].id, id) == 0) {
            printf("Enter new price: ");
            scanf("%f", &inv->inventory[i].price);
            return;
        }
    }

    printf("Product not found\n");
}

/****************************************  
	Function: searchProduct
	Description: This function searches the input of the user
	@param: Inventory* inv, int i, int option, char id, char name
	@return: void
*****************************************/ 

void searchProduct() {
    int option;
    printf("Search by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &option);
    
    FILE *file = fopen("inventory.txt", "r");
    if(file == NULL) {
        printf("Error opening file\n");
        return;
    }

    Product p;

    switch(option) {
        case 1:
        {
            char id[6];
            printf("Enter product ID: ");
            scanf("%s", id);

            while(fscanf(file, "%[^,],%[^,],%d,%f\n", p.id, p.name, &p.quantity, &p.price) != EOF) {
                if(strcmp(p.id, id) == 0) {
                    printf("ID: %s, Name: %s, Quantity: %d, Price: %.2f\n", p.id, p.name, p.quantity, p.price);
                    fclose(file);
                    return;
                }
            }

            break;
        }
        case 2:
        {
            char name[31];
            printf("Enter product name: ");
            scanf("%s", name);
            
            while(fscanf(file, "%[^,],%[^,],%d,%f\n", p.id, p.name, &p.quantity, &p.price) != EOF) {
                if(strcmp(p.name, name) == 0) {
                    printf("ID: %s, Name: %s, Quantity: %d, Price: %.2f\n", p.id, p.name, p.quantity, p.price);
                    fclose(file);
                    return;
                }
            }
            
            break;
        }
        default: printf("Invalid option\n");
    }

    fclose(file);
    printf("Product not found\n");
}

/****************************************  
	Function: saveAndExit
	Description: This function saves the current inventory to a file and then exits the program.
	@param: Inventory* inv, int option, char name, char id
	@return: void
*****************************************/ 

void saveAndExit(Inventory *inv) {
	int i;
    FILE *file = fopen("inventory.txt", "w");
    if(file == NULL) {
        printf("Error opening file\n");
        return;
    }

    for(i=0; i<inv->count; i++) {
        fprintf(file, "%s,%s,%d,%.2f\n", inv->inventory[i].id, inv->inventory[i].name, inv->inventory[i].quantity, inv->inventory[i].price);
    }

    fclose(file);
    exit(0);
}

/****************************************  
	Function: main
	Description: This is the main function.It prompts the user for a password 
	and then presents a menu of options for viewing, adding, updating, 
	and searching for products.
	@param: void, int loginAttempts, int choice
	@return: int
*****************************************/ 

int main() {
    Inventory inv = {.count = 0};

    loadInventory(&inv);
    printf("\n");
	printf("##      ## ######## ##        ######   #######  ##     ## ######## \n");
	printf("##  ##  ## ##       ##       ##    ## ##     ## ###   ### ##  \n");
	printf("##  ##  ## ##       ##       ##       ##     ## #### #### ## \n");
 	printf("##  ##  ## ######   ##       ##       ##     ## ## ### ## ######\n");
  	printf("##  ##  ## ##       ##       ##       ##     ## ##     ## ## \n");
    printf("##  ##  ## ##       ##       ##    ## ##     ## ##     ## ## \n");
    printf(" ###  ###  ######## ########  ######   #######  ##     ## ######## \n");
	printf("\n");
	

    int loginAttempts = 0;
    while(loginAttempts < 3) {
        char password[15];
        printf("Enter password: ");
        scanf("%s", password);

        if(strcmp(password, "$up3rv1sor") == 0) {
            break;
        }

        printf("Unauthorized access not allowed\n");
        loginAttempts++;
        if(loginAttempts == 3) {
            printf("Too many unsuccessful attempts, exiting...\n");
            return 0;
        }
    }

    int choice;
    do {
        printf("Menu:\n");
        printf("1. View Inventory by Name\n");
        printf("2. View Inventory by ID\n");
        printf("3. Add Product\n");
        printf("4. Update Product Quantity\n");
        printf("5. Update Product Price\n");
        printf("6. Search Product\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice) {
            case 1: viewInventory(&inv); break;
            case 2: viewInventoryById(&inv); break;
            case 3: addProduct(&inv); break;
            case 4: updateProductQuantity(&inv); break;
            case 5: updateProductPrice(&inv); break;
            case 6: searchProduct(); break;
            case 7: saveAndExit(&inv); break;
            default: printf("Invalid option\n");
        }
    } while(choice != 7);

    return 0;
}

