/*
 * Developer: Dennis Dao
 * July 25, 2022
 * v1.0
 */

// Program to implement a virtual memory manager
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGES 256
#define PAGESIZE 256
#define FRAMESIZE 256
#define PHYSICAL_MEM 65536

int main(int argc, char* argv[]){
    // Variables
    signed int pageTable[PAGES]; // Storing pages
    signed int frameNumber = 0; // frame number counter
    signed int memPage = 0; // Counter for pages of memory used
    signed int phys, val; // Storing the physical address and value at the offset of the physical address
    signed int logical; // The value storing the read logical address
    signed int offset; // The value storing the converted offset (bits 0-7)
    signed int page; // The value storing the page number (bits 8-15)
    signed char buffer[PAGESIZE]; // Buffer for reading
    signed char memory[PHYSICAL_MEM]; // The total memory
    FILE *addresses, *backing, *out; // Files to open

    // Verify number of arguments
    if(argc != 2){
        printf("Usage: %s <addresses.txt>\n", argv[0]);
        exit(-1);
    }

    // Initialize page table with -1's
    for(int i = 0; i < PAGES; i++){
        pageTable[i] = -1;
    }

    // Open necessary files
    if((addresses = fopen(argv[1], "r")) == NULL || (backing=fopen("BACKING_STORE.bin", "rb")) == NULL){
        perror("reading problem");
        exit(-1);
    }

    if((out = fopen("out.txt", "w")) == NULL){
        perror("writing problem");
        exit(-1);
    }

    // Until EOF, read in the address from the addresses file
    while(!feof(addresses)){
        // Read logical address
        fscanf(addresses, "%d", &logical);
        // Mask with 65535 for the 16 rightmost bits (65535 = 11111111 11111111)
        logical = logical & 65535;
        // Mask with 255 for the offset/8 rightmost bits (255 = 11111111)
        offset = logical & 255;
        // Shift bits right with >> 8 times for the page number (get the 8 leftmost bits)
        page = logical >> 8;

        // Handle page faults
        if(pageTable[page] == -1){
            // Set file pointer to start of the calculated page and read contents
            // 1 page = 256 bytes, 256 * n will skip n pages
            fseek(backing, PAGESIZE*page, SEEK_SET);
            fread(buffer, sizeof(char), PAGESIZE, backing);
            // Copy to the memory array at the appropriate page, move to the next "blank" page
            // memory+PAGESIZE*memPage affects where in memory it will copy to
            // ex. mempage 0 = positions 0-255, mempage 1 = positions 256-511, mempage 2 = positions 512-767...
            memcpy(memory+PAGESIZE*memPage, buffer, PAGESIZE);
            memPage++;

            // Assign frame numberto the page table, increment the frame for the next page fault
            pageTable[page] = frameNumber;
            frameNumber++;
        }

        // Determine physical address and index value
        // Physical address is determined by adding the frame number with offset
        phys = (pageTable[page] << 8) | offset;
        // Value is determined by checking the relevant page in memory
        // (1 page = 256 bytes, multiplying by frame number n skips n pages)
        // At index i will be the value we are looking for
        val = memory[pageTable[page]*PAGESIZE+offset];

        // Output to the screen and file
        printf("Virtual address: %d Physical Address: %d Value: %d\n", logical, phys, val);
        fprintf(out, "Virtual address: %d Physical Address: %d Value: %d\n", logical, phys, val);
    }

   // Finished with all files
   fclose(addresses);
   fclose(backing);
   fclose(out);
}
