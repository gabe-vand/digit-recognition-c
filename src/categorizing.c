
int trainModel() {

}

int loadData() {

}

char categorizeGrid(int** grid, int xSize, int ySize) {
    //grid comes in as (xSize, ySize)
    // 1) turn into 28x28
    
}

void printGrid(int** grid, int xSize, int ySize) {
    for (int y = 0; y < ySize; y++) {
        for (int x = 0; x <xSize; x++) {
            printf("%d, ", grid[y][x]);
        }
        printf("\n");
    }
}