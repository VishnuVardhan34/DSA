#include <stdio.h>
#include <stdlib.h>

struct SMH {
    int index;
    struct SMH* down;
    struct SMH* right;
};

struct SMD {
    int row, col, data;
    struct SMD* down, *right;
};

void Noodle(int r, int c, int d, struct SMD* begin) {
    struct SMD* data_helper1 = NULL;
    struct SMD* data_helper2 = NULL;
    struct SMH* row_helper = begin->right;
    struct SMH* col_helper = begin->down;

    // Locate the correct row and column headers
    while (row_helper && row_helper->index != r) {
        row_helper = row_helper->right;
    }
    while (col_helper && col_helper->index != c) {
        col_helper = col_helper->down;
    }

    // If row or column header does not exist, return early
    if (!row_helper || !col_helper) {
        printf("Row or column header not found.\n");
        return;
    }

    struct SMD* fixing = (struct SMD*)malloc(sizeof(struct SMD));
    fixing->row = r;
    fixing->col = c;
    fixing->data = d;
    fixing->down = fixing->right = NULL;

    // If both row and column are empty
    if (row_helper->down == NULL && col_helper->right == NULL) {
        row_helper->down = fixing;
        col_helper->right = fixing;
        fixing->down = NULL;
        fixing->right = NULL;
    }
    else {
        // Insert into row list (sorted by column index)
        if (row_helper->down == NULL || ((struct SMD*)row_helper->down)->col > c) {
            // Insert at beginning of row list
            fixing->down = row_helper->down;
            row_helper->down = fixing;
        } else {
            // Traverse row list to find the insertion point
            data_helper1 = (struct SMD*)row_helper->down;
            while (data_helper1->down != NULL && data_helper1->down->col < c) {
                data_helper1 = data_helper1->down;
            }
            fixing->down = data_helper1->down;
            data_helper1->down = fixing;
        }

        // Insert into column list (sorted by row index)
        if (col_helper->right == NULL || ((struct SMD*)col_helper->right)->row > r) {
            // Insert at beginning of column list
            fixing->right = col_helper->right;
            col_helper->right = fixing;
        } else {
            // Traverse column list to find the insertion point
            data_helper2 = (struct SMD*)col_helper->right;
            while (data_helper2->right != NULL && data_helper2->right->row < r) {
                data_helper2 = data_helper2->right;
            }
            fixing->right = data_helper2->right;
            data_helper2->right = fixing;
        }
    }
}

struct SMD* MOD(struct SMD* begin, int max_rows, int max_cols) {
    struct SMH* row_helper = begin->right;
    struct SMH* col_helper = begin->down;
    struct SMD* data_helper = NULL;
    struct SMD* prev_data_helper = NULL;
    int mr, mc, md;

    printf("Enter row and column to modify (modifying to 0 removes the node): ");
    scanf("%d%d", &mr, &mc);

    // Check if the specified row and column are within matrix bounds
    if (mr > max_rows || mc > max_cols) {
        printf("Specified row or column exceeds matrix boundaries.\n");
        return begin;
    }

    // Locate the appropriate row and column headers
    while (row_helper && row_helper->index != mr) {
        row_helper = row_helper->right;
    }
    while (col_helper && col_helper->index != mc) {
        col_helper = col_helper->down;
    }

    // If row or column does not exist
    if (!row_helper || !col_helper) {
        printf("Specified row or column does not exist in the matrix.\n");
        return begin;
    }

    // Find the node in the specified row at the specified column
    data_helper = row_helper->down;
    while (data_helper && data_helper->col != mc) {
        prev_data_helper = data_helper;
        data_helper = data_helper->down;
    }

    // Modify or delete node
    if (data_helper && data_helper->col == mc) {
        printf("Current data: %d\nEnter new data: ", data_helper->data);
        scanf("%d", &md);

        if (md == 0) {
            // Delete the node by linking the previous node to the next
            if (prev_data_helper) {
                prev_data_helper->down = data_helper->down;
            } else {
                row_helper->down = data_helper->down;
            }

            // Update column links
            struct SMD* col_ptr = col_helper->right;
            struct SMD* col_prev = NULL;
            while (col_ptr && col_ptr != data_helper) {
                col_prev = col_ptr;
                col_ptr = col_ptr->right;
            }
            if (col_prev) {
                col_prev->right = data_helper->right;
            } else {
                col_helper->right = data_helper->right;
            }

            free(data_helper);
            printf("Node deleted.\n");
        } else {
            data_helper->data = md;
            printf("Node updated to %d.\n", md);
        }
    } else {
        printf("Node not found for modification.\n");
    }

    return begin;
}


void displaySparseMatrix(struct SMD* begin) {
    struct SMH* row_header = begin->right;

    printf("Sparse Matrix Representation:\n");
    while (row_header) {
        struct SMD* current = row_header->down;
        while (current) {
            printf("Row: %d, Col: %d, Data: %d\n", current->row, current->col, current->data);
            current = current->down;
        }
        row_header = row_header->right;
    }
}

int main() {
    int row, col, info, r_size, c_size;
    printf("Enter matrix size (rows and columns): ");
    scanf("%d%d", &r_size, &c_size);

    struct SMD* mainheader = (struct SMD*)malloc(sizeof(struct SMD));
    mainheader->row = -1;
    mainheader->col = -1;
    mainheader->data = 0;
    mainheader->down = mainheader->right = NULL;

    struct SMH* row_travel = NULL; // Row header pointer
    struct SMH* col_travel = NULL; // Column header pointer

    // Initialize row headers
    struct SMH* row_adding = (struct SMH*)malloc(sizeof(struct SMH));
    mainheader->right = row_adding;
    row_adding->index = 1;
    row_adding->right = row_adding->down = NULL;
    row_travel = row_adding;

    for (int i = 2; i <= r_size; i++) {
        struct SMH* new_row = (struct SMH*)malloc(sizeof(struct SMH));
        row_travel->right = new_row;
        new_row->index = i;
        new_row->right = new_row->down = NULL;
        row_travel = new_row;
    }

    // Initialize column headers
    struct SMH* col_adding = (struct SMH*)malloc(sizeof(struct SMH));
    mainheader->down = col_adding;
    col_adding->index = 1;
    col_adding->right = col_adding->down = NULL;
    col_travel = col_adding;

    for (int i = 2; i <= c_size; i++) {
        struct SMH* new_col = (struct SMH*)malloc(sizeof(struct SMH));
        col_travel->down = new_col;
        new_col->index = i;
        new_col->right = new_col->down = NULL;
        col_travel = new_col;
    }

    printf("Insertion of headers completed.\n");
    printf("Enter data to insert (row column data). Enter -1 -1 -1 to end:\n");

    while (1) {
        scanf("%d%d%d", &row, &col, &info);
        if (row == -1 && col == -1 && info == -1) break;
        Noodle(row, col, info, mainheader);
        printf("Insertion processed!\n");
    }

    // Display the sparse matrix
    displaySparseMatrix(mainheader);

    int flash=0;

    while(flash!=-1){
        printf("Modify the matrix? -1 to exit\n");
        scanf("%d", &flash);
        if(flash==-1){
            break;
        }
        else{
            mainheader = MOD(mainheader, r_size, c_size);
            displayMat(mainheader);
        }
    }

    return 0;
}
