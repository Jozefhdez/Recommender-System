# Recommender system of using Anime Database

This project implements a system to efficiently manage and search a collection of anime data. The main goal is to optimize the search operations by utilizing various data structures and algorithms. The project includes features for building an AVL Tree for efficient searching, creating a graph for calculating anime similarity, and performing BFS and DFS traversal to explore relationships between anime.

## Data Structures and Algorithms Used

### 1. **Dynamic Array**
   - **Purpose**: The `dynamicArray<Anime>` is used to read and store the list of anime from a CSV file. This array dynamically resizes as more data is read.
   - **Algorithm**: The array grows as new elements are added, ensuring that we can store the complete list of anime without worrying about running out of space.

### 2. **AVL Tree**
   - **Purpose**: The AVL Tree is a balanced binary search tree that ensures efficient searching. It's used in two separate steps:
     - **Step 1**: Build an AVL tree for storing anime names.
     - **Step 2**: Build a second AVL tree for storing anime genres.
   - **Algorithm**: The AVL Tree performs **self-balancing** during insertions to maintain logarithmic time complexity for searches, insertions, and deletions. It guarantees that the tree remains balanced, meaning the height difference between the left and right subtrees is at most one.
   - **Operations**: 
     - Insertions of anime names and genres are performed by comparing string values, with rotations used to maintain balance during insertion.
     - The search operation is optimized to find an anime quickly by its name or genre.

### 3. **Graph**
   - **Purpose**: The `WeightedNotDirectecGraph` is used to represent relationships between animes based on their similarity. Each anime is a vertex, and edges represent the similarity between pairs of animes.
   - **Algorithm**: 
     - **Similarity Calculation**: A function calculates a similarity score between two animes, which is used as the weight for the edges in the graph.
     - **Graph Construction**: The graph is built by iterating over pairs of animes and adding edges if the similarity score is below a certain threshold (e.g., 0.8).
     - **Neighbor Search**: For each anime, the closest neighboring animes are calculated and displayed.

### 4. **Breadth-First Search (BFS) and Depth-First Search (DFS)**
   - **Purpose**: BFS and DFS are used to explore the anime graph and find related animes based on their similarity.
   - **Algorithms**:
     - **BFS**: This algorithm explores the graph level by level, starting from a given anime, and visiting all neighboring nodes (animes) in a breadth-first manner.
     - **DFS**: This algorithm explores as far as possible down each branch before backtracking. It’s used to traverse the graph from a given anime and list its related animes.
   - **Output**: For each anime, both BFS and DFS traversals are performed to find the top 10 related animes based on their similarity.

## Main Components

### 1. **Reading the CSV File**
   The system begins by reading the anime data from a CSV file. The data includes anime names, episodes, and genres, which are stored in a dynamic array.

### 2. **Building the AVL Trees**
   - **Anime Names AVL Tree**: Each anime is inserted into an AVL tree using its name as the key.
   - **Anime Genres AVL Tree**: A second AVL tree is created using anime genres to allow for efficient genre-based searches.

### 3. **Searching with AVL Trees**
   - The system performs multiple search queries to find animes by name or genre. The time for each search is measured, and the closest match is returned if an exact match is not found.

### 4. **Similarity Calculation and Graph Construction**
   A graph is created where each anime is connected to others based on their similarity score. The system calculates similarities between animes and constructs edges between them. It then calculates and displays the top 5 neighbors for specific anime titles.

### 5. **Graph Traversal**
   - BFS and DFS traversals are performed on the graph to explore the most similar animes to a given anime. The top 10 animes found by each traversal are printed.

## Example Search Queries
- For the **AVL Tree (Anime Names)**, the system performs searches for popular anime titles like "Kimi no Na wa.", "Fullmetal Alchemist: Brotherhood", and "Gintama".
- For the **AVL Tree (Anime Genres)**, the system performs searches for genre combinations like "Drama, Romance, School" and "Action, Adventure, Drama".

## Performance Metrics
- **Building the AVL Trees**: The time to construct the AVL tree for both anime names and genres is measured in milliseconds.
- **Search Times**: The search times for both name and genre-based queries are recorded and displayed.
- **Similarity Calculation**: The system calculates and displays the similarity percentage between related animes in the graph.
- **Graph Traversal**: The results of BFS and DFS traversals are printed, showing the related animes for a selected anime.

