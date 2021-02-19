/*
 * Student Name: Dennis Dao
 * Student Number: 110010116
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure Definitions
// Define a CategoryNode structure type.
typedef struct categoryStruct{
	int itemCatCode;
	char itemCat[20];
	struct categoryStruct* nextCategory;
} CategoryNode;

// Define a PriceNode structure type.
typedef struct priceStruct{
	int itemCode;
	char itemName[17];
	float itemPrice;
	struct priceStruct* nextPrice;
} PriceNode;

// Define an ItemNode structure type.
typedef struct itemStruct{
	int itemCode;
	int numItems;
	float itemPrice;
	float totSales;
	char itemName[17];
	struct itemStruct* nextItem;
} ItemNode;

// Define a ReportNode structure type.
typedef struct reportStruct{
	int code;
	char name[17];
	int numItems;
	float sales;
	struct reportStruct* nextReport;
} ReportNode;

// Function Prototypes
CategoryNode *setCategoryInfo(int code, char itemCat[]);
PriceNode *setPriceInfo(int code, char itemName[], float itemPrice);
ItemNode *setItemInfo(int code, int numItems, float totalSales, float basePrice, char name[]);
ReportNode *setReportInfo(int code, char name[], int numItems, float sales);
void initializeLists (CategoryNode **categoryHead, PriceNode **priceHead, ItemNode **itemHead, ReportNode **reportHead);
void insertCategoryAtHead (CategoryNode **head, int code, char itemCat[]);
void insertCategoryAtEnd (CategoryNode **head, int code, char itemCat[]);
void insertTransactionAtHead (ItemNode **head, int code, int numItems, float totalSales, float basePrice, char name[]);
void insertTransactionAtEnd (ItemNode **head, int code, int numItems, float totalSales, float basePrice, char name[]);
void insertPriceAtHead (PriceNode **head, int code, char itemName[], float itemPrice);
void insertPriceAtEnd (PriceNode **head, int code, char itemName[], float itemPrice);
void insertReportAtHead(ReportNode **head, int code, char name[], int numItems, float sales);
void insertReportAtEnd(ReportNode **head, int code, char name[], int numItems, float sales);
void printTransactions (ItemNode *head);
void sortItemCodes (ItemNode *head);
void sortReport(ReportNode *head);
void clearCategoryList (CategoryNode **head);
void clearPriceList (PriceNode **head);
void clearTransactionList (ItemNode **head);
void clearReportList(ReportNode **head);
void generateReceipt (ItemNode *head, int totalCustomers, int numItemsSold, float totalSales);
void generateCategoryReport (CategoryNode *categoryHead, ReportNode *reportHead);
void generateSummaryReport(CategoryNode *categoryHead, ReportNode *reportHead, int customers);
float getPrice(int code, PriceNode *priceHead);
char* getName(int code, PriceNode *priceHead);
int getTotalItems(int code, ReportNode *reportNode);

int main(){
	setbuf(stdout, NULL);
	// Pointers to files.
	FILE *fptr1;
	FILE *fptr2;
	FILE *fptr3;

	// Variable definitions
	int numItemsSold = 0;
	float basePrice;
	float salePrice;
	float totalSales = 0.00;
	int totalCustomers = 0;
	int code;
	int numItems = 0;
	char itemCat[50];
	char itemName[50];
	char fileInfo[50];

	// Defining heads of linked lists.
	CategoryNode *categoryHead;
	PriceNode *priceHead;
	ItemNode *transactionHead;
	ReportNode *reportHead;

	// Item categories from CategoryName.dat to be read. (Use-Case 1)
	fptr1 = fopen("CategoryName.dat", "a+");
	// Items, codes, prices from CodeNamePrice.dat to be read. (Use-Case 2)
	fptr2 = fopen("CodeNamePrice.dat", "a+");
	// Daily transactions for DailyTransactions.dat to be read.(Use-Case 3)
	fptr3 = fopen("DailyTransactions.dat", "a+");

	// Exit the program if any of the files cannot be opened.
	if(fptr1 == NULL || fptr2 == NULL || fptr3 == NULL){
		puts("File could not be opened.");
		exit(1);
	}
	// Initialize the lists
	initializeLists(&categoryHead, &priceHead, &transactionHead, &reportHead);

	// Keep reading data for each file until end of file.
	// Reading data from CategoryName.dat
	while(!feof(fptr1)){
		// Assume at least one category will have a space.
		fgets(fileInfo, sizeof(fileInfo), fptr1);
		sscanf(fileInfo, "%d %[^\n]s", &code, itemCat);
		insertCategoryAtEnd(&categoryHead, code, itemCat);
	}

	// Reading data from CodeNamePrice.dat
	while(!feof(fptr2)){
		fscanf(fptr2, "%d", &code);
		fscanf(fptr2, "\t%[^\t]s", itemName);
		fscanf(fptr2, "%f", &basePrice);
		insertPriceAtEnd(&priceHead, code, itemName, basePrice);
	}

	// Reading data from DailyTransactions.dat
	while(!feof(fptr3)){
		fscanf(fptr3, "%d %d", &code, &numItems);
		// Increment customers by 1, print the receipt, and clear info for customer n if a code of 0/000 is found.
		// Reasonably assume if a 0 is found and there are more items after, no items are sold at that 0
		// (In file: 1st 000	 0, last 000	 " ").
		if(code == 0){
			totalCustomers++;
			// Generate each customer's receipt (Use-Case 4).
			generateReceipt(transactionHead, totalCustomers, numItemsSold, totalSales);
			clearTransactionList(&transactionHead);
			numItemsSold = 0;
			totalSales = 0.0;
			continue;
		}

		// Update info for the receipt and reports (Use Case-4 and 5).
		strcpy(itemName, getName(code, priceHead));
		basePrice = getPrice(code, priceHead);
		salePrice = basePrice * numItems;
		totalSales += salePrice;
		numItemsSold+= numItems;

		// Insert the info into the list and sort it.
		insertTransactionAtEnd(&transactionHead, code, numItems, salePrice, basePrice, itemName);
		sortItemCodes(transactionHead);

		// Insert info for the report into the list
		insertReportAtEnd(&reportHead, code, itemName, numItems, basePrice);
	}
	// Sort the info for the report.
	sortReport(reportHead);

	// Close the input files
	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);

	// Generate category reports to output and InventoryX00.dat (Use-Case 5) Part 2
	generateCategoryReport(categoryHead, reportHead);
	// Generate summary report (Use-Case 6)
	generateSummaryReport(categoryHead, reportHead, totalCustomers);

	// Deallocate the allocated memory
	clearCategoryList(&categoryHead);
	clearPriceList(&priceHead);
	clearTransactionList(&transactionHead);
	clearReportList(&reportHead);
	return 0;
}

// Function definitions
// Set the category of each item, given the code and category
CategoryNode * setCategoryInfo(int code, char itemCat[]){
	CategoryNode *category;
	// Allocate memory
	category = (CategoryNode *) malloc(sizeof(CategoryNode));
	category->itemCatCode = code;
	strcpy(category->itemCat, itemCat);
	category->nextCategory = NULL;
	return category;
}

// Set the price of each item, given the code, name and price.
PriceNode * setPriceInfo(int code, char itemName[], float itemPrice){
	PriceNode *price;
	// Allocate memory
	price = (PriceNode *) malloc(sizeof(PriceNode));
	price->itemCode = code;
	strcpy(price->itemName, itemName);
	price->itemPrice = itemPrice;
	price->nextPrice = NULL;
	return price;
}

// Set the info of each item, given the code and number of that item sold.
ItemNode * setItemInfo(int code, int numItems, float totalSales, float basePrice, char name[]){
        ItemNode *item;
        // Allocate memory
        item = (ItemNode *) malloc(sizeof(ItemNode));
        item->itemCode = code;
        item->numItems = numItems;
	item->itemPrice = basePrice;
	item->totSales = totalSales;
	strcpy(item->itemName, name);
        item->nextItem = NULL;
        return item;
}

// Set the info for the report.
ReportNode *setReportInfo(int code, char name[], int numItems, float sales){
	ReportNode *report;
	// Allocate memory.
	report = (ReportNode *) malloc(sizeof(ReportNode));
	report->code = code;
	strcpy(report->name, name);
	report->numItems = numItems;
	report->sales = sales;
	report->nextReport = NULL;
	return report;
}

// Initialize the category linked list.
void initializeLists(CategoryNode **categoryHead, PriceNode **priceHead, ItemNode **itemHead, ReportNode **reportHead){
	*categoryHead = NULL;
	*priceHead = NULL;
	*itemHead = NULL;
	*reportHead = NULL;
}

// Insert the category at the head of the list.
void insertCategoryAtHead(CategoryNode **head, int code, char itemCat[]){
        CategoryNode * categoryInfo = setCategoryInfo(code, itemCat);
        // Check if the list is empty.
        if(*head == NULL){
                *head = categoryInfo;
        }
        else{
                categoryInfo->nextCategory = *head;
                *head = categoryInfo;
        }
}

// Insert the category at the end of the list
void insertCategoryAtEnd(CategoryNode **head, int code, char itemCat[]){
	// If the list is empty, insert at the head instead.
	if(*head == NULL){
		insertCategoryAtHead(head, code, itemCat);
		return;
	}
	else{
        	CategoryNode *categoryInfo = setCategoryInfo(code, itemCat);
        	CategoryNode *current = *head;

        	// Determine where the last item in the list is.
        	while(current->nextCategory != NULL){
                	current = current->nextCategory;
        	}
        	current->nextCategory = categoryInfo;
	}
}

// Insert the price at the head of the list.
void insertPriceAtHead(PriceNode **head, int code, char itemName[], float itemPrice){
	PriceNode * priceInfo = setPriceInfo(code, itemName, itemPrice);
	// Check if the list is empty.
	if(*head == NULL){
		*head = priceInfo;
	}
	else{
		priceInfo->nextPrice = *head;
		*head = priceInfo;
	}
}

// Insert the price at the end of the list.
void insertPriceAtEnd(PriceNode **head, int code, char itemName[], float itemPrice){
	// If the list is empty, insert at the head instead.
	if(*head == NULL){
		insertPriceAtHead(head, code, itemName, itemPrice);
		return;
	}
        PriceNode *priceInfo = setPriceInfo(code, itemName, itemPrice);
        PriceNode *current = *head;

        // Determine where the last item in the list is.
        while(current->nextPrice != NULL){
                current = current->nextPrice;
        }
        current->nextPrice = priceInfo;
}

// Insert the item at the head of the list.
void insertTransactionAtHead(ItemNode **head, int code, int numItems, float totalSales, float basePrice, char name[]){
        ItemNode * itemInfo = setItemInfo(code, numItems, totalSales, basePrice, name);
        // Check if the list is empty.
        if(*head == NULL){
                *head = itemInfo;
        }
        else{
                itemInfo->nextItem = *head;
                *head = itemInfo;
        }
}

// Insert the item at the end of the list.
void insertTransactionAtEnd(ItemNode **head, int code, int numItems, float totalSales, float basePrice, char name[]){
        // If the list is empty, insert at the head instead.
        if(*head == NULL){
                insertTransactionAtHead(head, code, numItems, totalSales, basePrice, name);
                return;
        }
        ItemNode *itemInfo = setItemInfo(code, numItems, totalSales, basePrice, name);
        ItemNode *current = *head;

        // Determine where the last item in the list is.
        while(current->nextItem != NULL){
                current = current->nextItem;
        }
        current->nextItem = itemInfo;
}

// Insert the report at the head of the list.
void insertReportAtHead(ReportNode **head, int code, char name[], int numItems, float sales){
        ReportNode * reportInfo = setReportInfo(code, name, numItems, sales);
        // Check if the list is empty.
        if(*head == NULL){
                *head = reportInfo;
        }
        else{
                reportInfo->nextReport = *head;
                *head = reportInfo;
        }
}

// Insert the report at the end of the list.
void insertReportAtEnd(ReportNode **head, int code, char name[], int numItems, float sales){
        // If the list is empty, insert at the head instead.
        if(*head == NULL){
                insertReportAtHead(head, code, name, numItems, sales);
                return;
        }
        ReportNode *reportInfo = setReportInfo(code, name, numItems, sales);
        ReportNode *current = *head;

        // Determine where the last item in the list is.
        while(current->nextReport != NULL){
                current = current->nextReport;
        }
        current->nextReport = reportInfo;
}

// Print the transaction list.
void printTransactions(ItemNode *head){
        while(head != NULL){
                printf(" %d\t\t %-16s\t %5.2f\t    %4d\t %7.2f\n", head->itemCode, head->itemName, head->itemPrice, head->numItems, head-> totSales);
                head = head->nextItem;
        }
        printf("\n");
}

// Bubble Sort by codes in the list in ascending order.
void sortItemCodes(ItemNode *head){
        ItemNode *current;
        ItemNode *nextNode;
	// Temps to sort all info for the receipt. (1&2 for code and amount, 3&4 for sale price and base price)
	// (5 for names)
        int temp1;
	int temp2;
	float temp3;
	float temp4;
	char temp5[50];

        for(current = head; current->nextItem != NULL; current = current->nextItem){
                for(nextNode = current->nextItem; nextNode != NULL; nextNode = nextNode -> nextItem){
                        if(current->itemCode > nextNode->itemCode && nextNode->itemCode != 0){
                                temp1 = current->itemCode;
				temp2 = current->numItems;
				temp3 = current->totSales;
				temp4 = current->itemPrice;
				strcpy(temp5, current->itemName);
                                current->itemCode = nextNode-> itemCode;
				current->numItems = nextNode -> numItems;
				current->totSales = nextNode->totSales;
				current->itemPrice = nextNode->itemPrice;
				strcpy(current->itemName, nextNode->itemName);
                                nextNode->itemCode = temp1;
				nextNode->numItems = temp2;
				nextNode->totSales = temp3;
				nextNode->itemPrice = temp4;
				strcpy(nextNode->itemName, temp5);
                        }
                }
        }
}

// Bubble Sort the report info in the list in ascending order.
void sortReport(ReportNode *head){
        ReportNode *current;
        ReportNode *nextNode;
        // Temps to sort all info for the report. (1 for code, 2 for name, 3 for numItems, 4 for sales)
        int temp1;
        char temp2[17];
        int temp3;
        float temp4;

        for(current = head; current->nextReport != NULL; current = current->nextReport){
                for(nextNode = current->nextReport; nextNode != NULL; nextNode = nextNode -> nextReport){
                        if(current->code > nextNode->code && nextNode->code != 0){
                                temp1 = current->code;
                                strcpy(temp2, current->name);
                                temp3 = current->numItems;
                                temp4 = current->sales;
                                current->code = nextNode-> code;
                                strcpy(current->name, nextNode->name);
                                current->numItems = nextNode->numItems;
                                current->sales = nextNode->sales;
                                nextNode->code = temp1;
                                strcpy(nextNode->name, temp2);
                                nextNode->numItems = temp3;
                                nextNode->sales = temp4;
                        }
                }
        }
}

// Clear the category list and deallocate the allocated memory
void clearCategoryList(CategoryNode **head){
        CategoryNode * current = *head;
        while(current != NULL){
                current = current->nextCategory;
                free(*head);
                *head = current;
        }
}

// Clear the price list and deallocate the allocated memory
void clearPriceList(PriceNode **head){
	PriceNode * current = *head;
	while(current != NULL){
		current = current->nextPrice;
		free(*head);
		*head = current;
	}
}

// Clear the transaction list and deallocate the allocated memory
void clearTransactionList(ItemNode **head){
	ItemNode * current = *head;
	while(current != NULL){
		current = current->nextItem;
		free(*head);
		*head = current;
	}
}

// Clear the report list and deallocate the allocated memory.
void clearReportList(ReportNode **head){
	ReportNode *current = *head;
	while(current != NULL){
		current = current->nextReport;
		free(*head);
		*head = current;
	}
}

// Print each customer's receipt.
void generateReceipt(ItemNode * head, int totalCustomers, int items, float totalSales){
	// Generate each customer receipt sorted by item code. (Use-Case 4).
        printf("Customer Receipt # %d\n", totalCustomers);
        printf("Code\t\t Item Name\t\t Price\t NumItem\t TotSale\n");
        printTransactions(head);
        printf("\t\t\t\t\tTotals:\t     %3d \t  %.2f\n\n", items, totalSales);
}

// Generate reports for each category.
void generateCategoryReport(CategoryNode *categoryHead, ReportNode* reportHead){
	CategoryNode *currentCategory;
	ReportNode *currentReport;

	// Go through each category in the list.
	for(currentCategory = categoryHead; currentCategory->nextCategory != NULL; currentCategory = currentCategory->nextCategory){
		FILE *fptr;
		// Strings to hold pieces of the file name to be concatenated.
		char fileName[] = "Inventory";
		char fileNumber[4];
		char fileType[] = ".dat";
		// Counter variables
		int previousCode = 0;
		int catItemsSold = 0;
		int itemsSold = 0;
		float catItemsSales = 0.00;

		// Format the file number (the current category) into fileNumber char array.
		sprintf(fileNumber, "%d", currentCategory->itemCatCode);
		// Make the file and concatenate the strings (name, category, file type) together to make the file name.
		// Open and write in binary mode.
		fptr = fopen(strcat(strcat(fileName, fileNumber), fileType), "wb");
		// Exit the program if the file cannot be opened.
		if(fptr == NULL){
			puts("Error. File cannot be opened.");
			exit(1);
		}

		// Output to both the stdout and the inventory file.
		printf("Category Name: %s\n", currentCategory->itemCat);
		fprintf(fptr, "Category Name: %s\n", currentCategory->itemCat);
		printf("Category Code: %d\n", currentCategory->itemCatCode);
		fprintf(fptr, "Category Code: %d\n", currentCategory->itemCatCode);
		printf("Code\t  Item Name\t   NumItems\t TotSale\n");
		fprintf(fptr, "Code\t  Item Name\t    NumItems\t TotSale\n");
		// Go through every item that was made in the day's transactions list
		for(currentReport = reportHead; currentReport != NULL; currentReport = currentReport->nextReport){
			// If the code is in range of the category (X00-X99), insert info into the report.
			if(currentReport->code >= currentCategory->itemCatCode && currentReport->code < currentCategory->itemCatCode + 100){
				for(int i = 0; i < currentReport->numItems; i++){
					// If the code has been read before, only change the amount of sales.
					if(previousCode == currentReport->code){
						catItemsSold++;
	                                        catItemsSales += currentReport->sales;
						itemsSold++;
						continue;
					}
					// Skip the item if the code was invalid (the code does not exist in the codenameprice.dat list)
					if(strcmp(currentReport->name, "Item not found") == 0){
						continue;
					}
					catItemsSold++;
					printf(" %d\t  %-17s\t%3d\t  %6.2f\n", currentReport->code, currentReport->name, getTotalItems(currentReport->code, reportHead), (float)currentReport->sales*getTotalItems(currentReport->code, reportHead));
					fprintf(fptr, " %d\t  %-17s\t %-3d\t  %6.2f\n", currentReport->code, currentReport->name, getTotalItems(currentReport->code, reportHead), (float)currentReport->sales*getTotalItems(currentReport->code, reportHead));
					catItemsSales += currentReport->sales;
					previousCode = currentReport->code;
				}
			}
		}
		printf("\n");
		fprintf(fptr, "\n");
		printf("Total Items Sold: %5d\n", catItemsSold);
		fprintf(fptr, "Total Items Sold:%6d\n", catItemsSold);
		printf("Total Sales: %10.2f\n\n", catItemsSales);
		fprintf(fptr, "Total Sales:%11.2f\n\n", catItemsSales);
		// Close inventoryX00 file.
		fclose(fptr);
	}
}

// Generate the summary report.
void generateSummaryReport(CategoryNode *categoryHead, ReportNode *reportHead, int customers){
        CategoryNode *currentCategory;
        ReportNode *currentReport;
	int catItems = 0;
	float catSales = 0.00;
	int totalItems = 0;
	float totalSales = 0.00;
	int previousCode = 0;

        puts("Daily Summary Report");
        printf("Code\t  Category Name\t\t #Items Sold\t Tot Sales Amt\n");
	// Go through every category on the list.
	for(currentCategory = categoryHead; currentCategory->nextCategory != NULL; currentCategory = currentCategory->nextCategory){
		// Go through every item on the transaction list.
        	for(currentReport = reportHead; currentReport != NULL; currentReport = currentReport->nextReport){
			// If the code is in range of the category (X00-X99), insert info into the report.
                        if(currentReport->code >= currentCategory->itemCatCode && currentReport->code < currentCategory->itemCatCode + 100){
				for(int i = 0; i < currentReport->numItems; i++){
                        	        // If the code has already been read, change only the sales and item amount.
					if(previousCode == currentReport->code){
						catItems++;
						catSales += currentReport->sales;
						continue;
					}
					// If the code was invalid (code does not exist), skip the item.
					if(strcmp(currentReport->name, "Item not found") == 0){
                                                continue;
                                        }
					catItems++;
					catSales += currentReport->sales;
					previousCode = currentReport->code;
				}
			}
		}
		printf(" %d\t  %s\t\t\t\t\t%-3d\t   %7.2f\n\n", currentCategory->itemCatCode, currentCategory->itemCat, catItems, catSales);
		totalItems += catItems;
		totalSales += catSales;
		// Reset counters for the next category.
		catSales = 0;
		catItems = 0;
	}

        printf("Total Customers:\t%10d\n", customers);
        printf("Total Items Sold: \t%10d\n", totalItems);
        printf("Total Sales: \t\t%10.2f\n\n", totalSales);

}

// Search for matching code in the price list to assign price.
float getPrice(int code, PriceNode *priceHead){
        PriceNode *currentPrice;

	// Check if a code matches a code on the price list. If match found, return the price.
        for(currentPrice = priceHead; currentPrice != NULL; currentPrice = currentPrice->nextPrice){
        	if(code == currentPrice->itemCode){
			return currentPrice->itemPrice;
		}
        }
	return 0.0;
}

// Search for matching name in the price list to assign name.
char* getName(int code, PriceNode *priceHead){
        PriceNode *currentPrice;

	// Check if a code matches a code on the price list. If match found, return the name.
        for(currentPrice = priceHead; currentPrice != NULL; currentPrice = currentPrice->nextPrice){
                if(code == currentPrice->itemCode){
                        return currentPrice->itemName;
                }
        }
        return "Item not found";
}

// Get the total amount of a code that was sold (ex. code 105, 5 bought appears twice = return 10)
int getTotalItems(int code, ReportNode *reportHead){
	ReportNode *currentReport;
	int total = 0;

	// Check if a code matches a code on the report list.
	for(currentReport = reportHead; currentReport != NULL; currentReport = currentReport->nextReport){
		if(code == currentReport->code){
			total += currentReport->numItems;
		}
	}
	return total;
}
