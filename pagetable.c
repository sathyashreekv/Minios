#include <stdio.h>

#define PAGE_SIZE 4
#define NUM_PAGES 4
#define NUM_FRAMES 4

// Function to print the page table and physical memory
void print_memory(int page_table[], int physical_memory[][PAGE_SIZE]) {
    printf("\nPage Table:\n");
    for (int i = 0; i < NUM_PAGES; i++) {
        if (page_table[i] != -1) {
            printf("Page %d -> Frame %d\n", i, page_table[i]);
        } else {
            printf("Page %d -> Not Loaded\n", i);
        }
    }

    printf("\nPhysical Memory:\n");
    for (int i = 0; i < NUM_FRAMES; i++) {
        printf("Frame %d: ", i);
        if (physical_memory[i][0] != -1) {
            for (int j = 0; j < PAGE_SIZE; j++) {
                printf("%d ", physical_memory[i][j]);
            }
            printf("\n");
        } else {
            printf("Empty\n");
        }
    }
}

// Function to access a virtual address
void access_virtual_address(int address, int page_table[], int physical_memory[][PAGE_SIZE]) {
    int page_number = address / PAGE_SIZE;
    int offset = address % PAGE_SIZE;

    printf("\nAccessing virtual address %d -> Page %d, Offset %d\n", address, page_number, offset);

    // Check if the page is already in memory
    if (page_table[page_number] != -1) {
        // If the page is in memory, print the physical address
        int frame = page_table[page_number];
        printf("Page %d is already loaded in Frame %d, Physical address: [%d][%d]\n", page_number, frame, frame, offset);
    } else {
        // Page fault: load the page into an available frame
        printf("Page fault: Page %d is not loaded in memory!\n", page_number);
        // Find an empty frame to load the page
        int loaded = 0;
        for (int i = 0; i < NUM_FRAMES; i++) {
            if (physical_memory[i][0] == -1) {
                // Load the page into this frame
                page_table[page_number] = i;
                // Simulate loading the page into memory
                for (int j = 0; j < PAGE_SIZE; j++) {
                    physical_memory[i][j] = page_number * PAGE_SIZE + j;
                }
                printf("Page %d loaded into Frame %d\n", page_number, i);
                loaded = 1;
                break;
            }
        }
        if (!loaded) {
            printf("No available frame for Page %d!\n", page_number);
        }
    }
}

int main() {
    // Initialize the page table with -1 (not loaded)
    printf("Memory Management : Page Table\n");
   printf("A Page Table is an operating system data structure that maps virtual addresses to physical \n");
   printf("addresses. Virtual memory is divided into pages, and physical memory into frames. The page\n");
   printf("table tracks which virtual page is in which frame, enabling the OS to translate virtual\n");
   printf("addresses to physical ones. If a program accesses a page found in the page table, it\n");
   printf("retrieves the data from the corresponding frame; otherwise, a page fault occurs,and the\n");
   printf("program must load the page into an available frame.\n");
   printf(" ");
   
    int page_table[NUM_PAGES] = {-1, -1, -1, -1};

    // Initialize the physical memory with -1 (empty frames)
    int physical_memory[NUM_FRAMES][PAGE_SIZE] = {{-1, -1, -1, -1},
                                                   {-1, -1, -1, -1},
                                                   {-1, -1, -1, -1},
                                                   {-1, -1, -1, -1}};

    // Load pages into memory initially
    page_table[0] = 0;  // Page 0 -> Frame 0
    for (int i = 0; i < PAGE_SIZE; i++) physical_memory[0][i] = i;  // Page 0 content
    
    page_table[2] = 1;  // Page 2 -> Frame 1
    for (int i = 0; i < PAGE_SIZE; i++) physical_memory[1][i] = 8 + i;  // Page 2 content
    
    page_table[3] = 2;  // Page 3 -> Frame 2
    for (int i = 0; i < PAGE_SIZE; i++) physical_memory[2][i] = 12 + i;  // Page 3 content

    // Print the initial memory state
    print_memory(page_table, physical_memory);

    // Access some virtual addresses
    access_virtual_address(5, page_table, physical_memory);  // Accessing address 5
    access_virtual_address(9, page_table, physical_memory);  // Accessing address 9
    access_virtual_address(0, page_table, physical_memory);  // Accessing address 0
    access_virtual_address(12, page_table, physical_memory); // Accessing address 12
    access_virtual_address(3, page_table, physical_memory);  // Accessing address 3

    // Print the final memory state
    print_memory(page_table, physical_memory);

    return 0;
}
