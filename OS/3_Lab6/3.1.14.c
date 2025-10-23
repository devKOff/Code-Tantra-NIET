#include <stdio.h>

// Define constants based on the test case
#define LOGICAL_ADDRESS_SPACE 1024
#define PAGE_SIZE 128
#define NUM_PAGES 8
#define NUM_FRAMES 8

int main() {
    // The page table, hardcoded from your test case.
    // Index = Page Number, Value = Frame Number
    int page_table[NUM_PAGES] = {3, 5, 1, 7, 2, 6, 0, 4};

    int logical_address;
    int page_number, offset;
    int frame_number, physical_address;
    
    // 1. Print the setup information
    printf("Logical Address Space = %d bytes\n", LOGICAL_ADDRESS_SPACE);
    printf("Page Size = %d bytes\n", PAGE_SIZE);
    printf("Number of Pages = %d\n", NUM_PAGES);
    printf("Number of Frames = %d\n", NUM_FRAMES);

    // 2. Print the Page Table
    printf("Page Table:\n");
    for (int i = 0; i < NUM_PAGES; i++) {
        printf("Page %d -> Frame %d\n", i, page_table[i]);
    }

    // 3. Get user input
    // The prompt does not have a newline, so the user types on the same line
    printf("Enter a logical address (0 - %d): ", LOGICAL_ADDRESS_SPACE - 1);
    scanf("%d", &logical_address);

    // 4. Validate the logical address
    if (logical_address < 0 || logical_address >= LOGICAL_ADDRESS_SPACE) {
        printf("Invalid logical address\n");
    } else {
        // 5. Calculate Page Number and Offset
        page_number = logical_address / PAGE_SIZE;
        offset = logical_address % PAGE_SIZE;

        // 6. Look up the Frame Number in the page table
        frame_number = page_table[page_number];

        // 7. Calculate the Physical Address
        physical_address = (frame_number * PAGE_SIZE) + offset;

        // 8. Print the results
        printf("Logical Address %d is in:\n", logical_address);
        printf("Page Number = %d\n", page_number);
        printf("Offset = %d\n", offset);
        printf("Frame Number from Page Table = %d\n", frame_number);
        
        // Print the final calculation as shown in the test case
        printf("Physical Address = (Frame %d * %d) + %d = %d\n", 
               frame_number, PAGE_SIZE, offset, physical_address);
    }

    return 0;
}