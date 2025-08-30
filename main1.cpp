#include <_stdlib.h>
#include <chrono>
#include <iostream>
#include <string>
#include <filesystem>
#include "ADTs/dynamicArray.hpp"
#include "ADTs/linkedList.hpp"
#include "ADTs/priorityQueue.hpp"
#include "ADTs/linkedList.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

//using namespace std::chrono;

/* Anime Data Type */
class Anime {
    public:

    int anime_id;
    std::string name;
    std::string genre;
    std::string type;
    int episodes;
    float rating;
    int members;

    bool operator>=(const Anime& other) const {
        return rating >= other.rating;
    }

    bool operator<=(const Anime& other) const {
        return rating <= other.rating; 
    }

    bool operator>(const Anime& other) const {
        return rating > other.rating; 
    }

    bool operator<(const Anime& other) const {
        return rating < other.rating;
    }
    
    bool operator==(const Anime& other) const {
        return rating == other.rating;
    }

};

/* Person Data Type */
class Person {
    
    public:

        std::string favGenres;
        std::string favDuration;

        Person(std::string genres, std::string duration){
            favGenres = genres;
            favDuration = duration;
        }

};

/* Methods to read and store data */

dynamicArray<Anime> ArrayReadAnimeCSV(const std::string& filename) {
    dynamicArray<Anime> animes;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return animes;
    }

    // Ignores headline
    std::getline(file, line);

    // Reads every line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Anime anime;
        std::string temp;

        try {
            // Converts from CSV to string
            std::getline(ss, temp, ',');
            anime.anime_id = std::stoi(temp); // If not int

            std::getline(ss, anime.name, ',');

            // Genre is between ""
            std::getline(ss, temp, ',');
            if (temp[0] == '\"') {
                anime.genre = temp.substr(1);  // Erases first "
                while (temp.back() != '\"') {
                    std::getline(ss, temp, ',');
                    temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
                    anime.genre += "," + temp;  // Adds next genre
                }
                anime.genre.pop_back();  // Erases last "
            } else {
                anime.genre = temp;
            }

            std::getline(ss, anime.type, ',');

            std::getline(ss, temp, ',');
            anime.episodes = std::stoi(temp); // If not int

            std::getline(ss, temp, ',');
            anime.rating = std::stof(temp); // If not int

            std::getline(ss, temp, ',');
            anime.members = std::stoi(temp); // If not int

            animes.pushBack(anime);

        } catch (const std::invalid_argument& e) {
            // Skips the line and continues
            continue;
        }
    }

    file.close();
    return animes;
}

priorityQueue<Anime> PriorityQueueReadAnimeCSV(const std::string& filename) {
    priorityQueue<Anime> animes;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return animes;
    }

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Anime anime;
        std::string temp;

        try {
            std::getline(ss, temp, ',');
            anime.anime_id = std::stoi(temp);

            std::getline(ss, anime.name, ',');

            std::getline(ss, temp, ',');
            if (temp[0] == '\"') {
                anime.genre = temp.substr(1); 
                while (temp.back() != '\"') { 
                    std::getline(ss, temp, ',');
                    temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
                    anime.genre += "," + temp;
                }
                anime.genre.pop_back();
            } else {
                anime.genre = temp;
            }

            std::getline(ss, anime.type, ',');

            std::getline(ss, temp, ',');
            anime.episodes = std::stoi(temp);

            std::getline(ss, temp, ',');
            anime.rating = std::stof(temp); 

            std::getline(ss, temp, ',');
            anime.members = std::stoi(temp); 

            animes.push(anime, anime.rating);

        } catch (const std::invalid_argument& e) {
            continue;
        }
    }

    file.close();
    return animes;
}

linkedList<Anime> LinkedListReadAnimeCSV(const std::string& filename){
    linkedList<Anime> animes;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return animes;
    }


    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Anime anime;
        std::string temp;

        try {
            std::getline(ss, temp, ',');
            anime.anime_id = std::stoi(temp);

            std::getline(ss, anime.name, ',');

            std::getline(ss, temp, ',');
            if (temp[0] == '\"') {
                anime.genre = temp.substr(1); 
                while (temp.back() != '\"') { 
                    std::getline(ss, temp, ',');
                    temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
                    anime.genre += "," + temp;
                }
                anime.genre.pop_back();
            } else {
                anime.genre = temp;
            }

            std::getline(ss, anime.type, ',');

            std::getline(ss, temp, ',');
            anime.episodes = std::stoi(temp);

            std::getline(ss, temp, ',');
            anime.rating = std::stof(temp);

            std::getline(ss, temp, ',');
            anime.members = std::stoi(temp);

            animes.pushFront(anime);

        } catch (const std::invalid_argument& e) {
            continue;
        }
    }

    file.close();
    return animes;

}

/* Quick sort by episode number */

int partitionEpisodes(dynamicArray<Anime>& array, int front, int pivot){

    if(front >= pivot){
        return pivot;
    }
    else{
        int i = front;

        for(int j = front; j < pivot; j++){
            if(array[j].episodes >= array[pivot].episodes){
                std::swap(array[i],array[j]);
                i++;
            }
        }
        std::swap(array[pivot],array[i]);
        return i;
    }
}

void quickSortEpisodes(dynamicArray<Anime>& array, int front, int back){

    if(front >= back){
        return;
    }
    else{
    
    int pi = partitionEpisodes(array, front, back);

    quickSortEpisodes(array, front, pi - 1);
    quickSortEpisodes(array, pi + 1, back);
    }
}

/* Sort algorithms by rating number */

int partitionRating(dynamicArray<Anime>& array, int front, int pivot){

    if(front >= pivot){
        return pivot;
    }
    else{
        int i = front;

        for(int j = front; j < pivot; j++){
            if(array[j].rating >= array[pivot].rating){
                std::swap(array[i],array[j]);
                i++;
            }
        }
        std::swap(array[pivot],array[i]);
        return i;
    }
}

void quickSortRating(dynamicArray<Anime>& array, int front, int back){

    if(front >= back){
        return;
    }
    else{
    
    int pi = partitionRating(array, front, back);

    quickSortRating(array, front, pi - 1);
    quickSortRating(array, pi + 1, back);
    }
}

void bubbleSortRating(dynamicArray<Anime>& arr){
    auto n = arr.size();

    for (unsigned long long i = 1; i < n; i++) {
        bool swapped = false;
        for (unsigned long long j = 0; j < n - i; j++) {
            if (arr[j + 1].rating > arr[j].rating) {
                std::swap(arr[j+1], arr[j]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void insertionSortRating(dynamicArray<Anime>& arr) {

    for(int i = 1; i < arr.size(); i++){
        int j = i - 1;
        while(arr[j].rating > arr[j+1].rating && j >= 0){
            std::swap(arr[j],arr[j+1]);
            j--;
        }
    }
    
}

void insertionSort(dynamicArray<Anime>& arr) {
    int n = arr.size(); 
    int i, j;       
    float key;
    
    for (i = 1; i < n; i++) {
        key = arr[i].rating; 
        j = i - 1;     

        
        while (j >= 0 && arr[j].rating < key) {
            arr[j + 1] = arr[j];  
            j = j - 1;            
        }
        arr[j + 1].rating = key;  
    }
}

/* Binary Search */

int binarySearch(dynamicArray<Anime>& array, int find, int front, int back){

    if(front > back){
        return -1;
    }

    int  mid = front + (back - front) / 2;

    if(array[mid].episodes == find){
        return mid;
    }
    else if(array[mid].episodes < find){
        return binarySearch(array, find, front, mid-1);
    }
    else{
        return binarySearch(array, find, mid+1, back);
    }
}

/* Checks if an anime is a specific genre */

bool isGenre(const Anime& anime, const std::string& genre) {
    std::stringstream genreStream(anime.genre);
    std::string temp;
    while (std::getline(genreStream, temp, ',')) {
        if (temp == genre || temp == genre) { 
            return true;
        }
    }
    return false;
}

/* Linear Search by genre */

int LinearSearch(dynamicArray<Anime>& arr, std::string& genre) {
    for(int i = 0; i < arr.size(); i++){
        if(isGenre(arr[i], genre)){
            return i;
        }
    }
    return -1;
}

/* Creates a subarray of animes from one genre and sorts it by rating */

dynamicArray<Anime> subCategorizeQuickSort(dynamicArray<Anime> arr, std::string& genre){
    dynamicArray<Anime> subCategory;
    for(int i = 0; i < arr.size(); i++){
        if(isGenre(arr[i], genre) == true){
            subCategory.pushBack(arr[i]);
        }
    }
    quickSortRating(subCategory, 0, subCategory.size()-1);

    return subCategory;
}

dynamicArray<Anime> subCategorizeRec(dynamicArray<Anime> arr, std::string& genre){
    dynamicArray<Anime> subCategory;
    float compare = 7.5;
    for(int i = 0; i < arr.size(); i++){
        if(isGenre(arr[i], genre) == true && arr[i].rating > compare && arr[i].type == "TV"){
            subCategory.pushBack(arr[i]);
        }
    }
    quickSortEpisodes(subCategory, 0, subCategory.size()-1);

    return subCategory;
}

dynamicArray<Anime> subCategorizeBubbleSort(dynamicArray<Anime> arr, std::string& genre){
    dynamicArray<Anime> subCategory;
    for(int i = 0; i < arr.size(); i++){
        if(isGenre(arr[i], genre)){
            subCategory.pushBack(arr[i]);
        }
    }
    bubbleSortRating(subCategory);

    return subCategory;
}

dynamicArray<Anime> subCategorizeInsertionSort(dynamicArray<Anime> arr, std::string& genre){
    dynamicArray<Anime> subCategory;
    for(int i = 0; i < arr.size(); i++){
        if(isGenre(arr[i], genre)){
            subCategory.pushBack(arr[i]);
        }
    }
    insertionSort(subCategory);

    return subCategory;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------------------------------------------------------------------------------//


int main() {

    /* Gets the full path to the csv file */
        std::filesystem::path relative_path = "archive/anime.csv";
        std::string filename;

        try {
            filename = std::filesystem::absolute(relative_path).string();
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error obtaining the full path: " << e.what() << std::endl;
        } 
    
    /* Calls the methods to read the csv file and store it */

        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
        std::cout << "\nRead and Write methods \n\n";

        auto start_array = std::chrono::high_resolution_clock::now();
        dynamicArray<Anime> animesArray = ArrayReadAnimeCSV(filename);
        auto stop_array = std::chrono::high_resolution_clock::now();
        auto duration_array = std::chrono::duration_cast<std::chrono::milliseconds>(stop_array - start_array);
        std::cout<< "Anime array: " << animesArray.size() << std::endl;
        std::cout << "Duration to read and store in Dynamic Array: " << duration_array.count() << " ms" << std::endl;

        auto start_queue = std::chrono::high_resolution_clock::now();
        priorityQueue<Anime> animesPriorityQueue = PriorityQueueReadAnimeCSV(filename);
        auto stop_queue = std::chrono::high_resolution_clock::now();
        auto duration_queue = std::chrono::duration_cast<std::chrono::milliseconds>(stop_queue - start_queue);
        std::cout<< "Anime queue: " << animesPriorityQueue.size() << std::endl;
        std::cout << "Duration to read and store in Priority Queue: " << duration_queue.count() << " ms" << std::endl;
        
        auto start_list = std::chrono::high_resolution_clock::now();
        linkedList<Anime> animesLinkedList = LinkedListReadAnimeCSV(filename);
        auto stop_list = std::chrono::high_resolution_clock::now();
        auto duration_list = std::chrono::duration_cast<std::chrono::milliseconds>(stop_list - start_list);
        std::cout<< "Anime list: " << animesLinkedList.size() << std::endl;
        std::cout << "Duration to read and store in Linked List: " << duration_list.count() << " ms" << std::endl;

    /* Sorts the array by episodes */
    
        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
        std::cout << "\nSorting array by episodes\n";

        std::cout << std::endl << "Array not sorted" << std::endl << std::endl;

        for(int i = 0; i < 10; ++i){
            std::cout << animesArray[i].name << " with " << animesArray[i].episodes << " episodes" << std::endl;
        }

        std::cout << std::endl << "Array sorted by episodes" << std::endl << std::endl;
        quickSortEpisodes(animesArray, 0, animesArray.size()-1);

        for(int i = 0; i < 10; ++i){
            std::cout << animesArray[i].name << " with " << animesArray[i].episodes << " episodes" << std::endl;
        }

    /* Binary Search by episodes */

        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
        std::cout << "\nBinary Search for episodes \n\n";

        int target = 1471;

        auto start_binary = std::chrono::high_resolution_clock::now();
        int index = binarySearch(animesArray, target, 0, animesArray.size() - 1);
        auto stop_binary = std::chrono::high_resolution_clock::now();
        auto duration_binary = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_binary - start_binary);
    
        if (index != -1) {
            std::cout << "Looking for a " << target << " episode anime: " << animesArray[index].name << std::endl;
        } else {
            std::cout << "Anime with " << target << " episodes not found." << std::endl;
        }

        std::cout << "Duration to find a anime: " << duration_binary.count() << " ns" << std::endl;

    /* Linear Search by genre */
        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
        std::cout << "\nLinear search for genre \n\n";

        std::string gender = "Action";

        auto start_linear = std::chrono::high_resolution_clock::now();
        int indexGender = LinearSearch(animesArray, gender);
        auto stop_linear = std::chrono::high_resolution_clock::now();
        auto duration_linear = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_linear - start_linear);

        if (index != -1) {
            std::cout << "Looking for a " << gender << " anime: " << animesArray[indexGender].name << std::endl;
        } else {
            std::cout << gender <<" anime not found." << std::endl;
        }

        std::cout << "Duration to find a anime: " << duration_linear.count() << " ns" << std::endl;

    /* Sorts the array by rating */ 
        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
        std::cout << "\nSort array by rating \n\n";
    
        std::cout << "Array not sorted" << std::endl << std::endl;

        for(int i = 0; i < 10; ++i){
            std::cout << animesArray[i].name << " with " << animesArray[i].rating << " of rating" << std::endl;
        }

        std::cout << std::endl << "Array sorted by rating" << std::endl << std::endl;
        quickSortRating(animesArray, 0, animesArray.size()-1);

        std::cout << "Animes with higher rating: " << std::endl << std::endl;

        for(int i = 0; i < 10; ++i){
            std::cout << animesArray[i].name << " with " << animesArray[i].rating << " of rating" << std::endl;
        }

    /* Finds the best rated animes by genre */
        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
        std::cout << "\nFinds the best rated animes by genre \n\n";

        std::string genderUser = "Action";
        std::string genderUser2 = "Drama";
        std::string genderUser3 = "Parody";

        std::cout << "Anime of " << genderUser << " with higher rating: " << std::endl;
        auto start_action = std::chrono::high_resolution_clock::now();
        dynamicArray<Anime> genderSubArray = subCategorizeQuickSort(animesArray, genderUser);
        auto stop_action = std::chrono::high_resolution_clock::now();
        auto duration_action = std::chrono::duration_cast<std::chrono::milliseconds>(stop_action - start_action);
        for(int i = 0; i < 10; ++i){
            std::cout << genderSubArray[i].name << " with " << genderSubArray[i].rating << " of rating" << std::endl;
        }
        
        std::cout << "\nDuration to find the most relevant animes: " << duration_action.count() << " ms" << std::endl;
        
        std::cout << "\n\n";

        std::cout << "Anime of " << genderUser2 << " with higher rating: " << std::endl;
        auto start_drama = std::chrono::high_resolution_clock::now();
        dynamicArray<Anime> genderSubArray2 = subCategorizeBubbleSort(animesArray, genderUser2);
        auto stop_drama = std::chrono::high_resolution_clock::now();
        auto duration_drama = std::chrono::duration_cast<std::chrono::milliseconds>(stop_drama - start_drama);
        for(int i = 0; i < 10; ++i){
            std::cout << genderSubArray2[i].name << " with " << genderSubArray2[i].rating << " of rating" << std::endl;
        }

        std::cout << "\nDuration to find the most relevant animes: " << duration_drama.count() << " ms" << std::endl;

        std::cout << "\n\n";

        std::cout << "Anime of " << genderUser3 << " with higher rating: " << std::endl;
        auto start_parody = std::chrono::high_resolution_clock::now();
        dynamicArray<Anime> genderSubArray3 = subCategorizeInsertionSort(animesArray, genderUser3);
        auto stop_parody = std::chrono::high_resolution_clock::now();
        auto duration_parody = std::chrono::duration_cast<std::chrono::milliseconds>(stop_parody - start_parody);
        for(int i = 0; i < 10; ++i){
            std::cout << genderSubArray3[i].name << " with " << genderSubArray3[i].rating << " of rating" << std::endl;
        }
        
        std::cout << "\nDuration to find the most relevant animes: " << duration_parody.count() << " ms" << std::endl;

        
    /* Recomender system */

    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "\nRecomender system \n\n";

    Person person1("Comedy", "short");
    Person person2("Drama", "long");
    Person person3("Comedy", "long");
    Person person4("Action", "long");
    Person person5("Romance", "short");
    Person person6("Parody", "long");
    Person person7("Sci-Fi", "medium");
    Person person8("Fantasy", "medium");
    Person person9("Mystery", "medium");
    Person person10("Action", "short");
    Person person11("Magic", "long");
    Person person12("Action", "medium");
    Person person13("Mecha", "long");
    Person person14("Shounen", "short");
    Person person15("Horror", "short");

    std::vector<Person> people = {person1,person2,person3,person4,person5,person6,person7,person8,person9,person10,person11,person12,person13,person14,person15};
    std::vector<std::string> oppositeGenre = {"Thriller", "Parody", "Thriller", "Romance", "Action", "Drama", "SliceofLife", "Historical", "Military", "Romance", "Sci-Fi", "Romance", "Sports", "Shoujo", "Comedy"};
    
    for(int i = 0; i < people.size(); i++){
        std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
        
        std::string genre = people[i].favGenres;
        std::string duration = people[i].favDuration;
        std::string badGenre = oppositeGenre[i];

        dynamicArray<Anime> favAnimes = subCategorizeRec(animesArray, genre);
        dynamicArray<Anime> badAnimes = subCategorizeRec(animesArray, badGenre);

        std::cout << "The preferences for this person are: \n \t- Genre: " << genre << "\n\t- Duration: " << duration << std::endl << std::endl;

        std::cout << "The good recommendations are: " << std::endl;

        if(duration == "short"){
            for(int j = favAnimes.size()-1; j > favAnimes.size() - 16; j--){
                std::cout << "\t- " << favAnimes[j].name << " with " << favAnimes[j].episodes << " episodes" << " with score " << favAnimes[j].rating << std::endl;
            }
        } 
        else if(duration == "long"){
            for(int j = 0; j < 15; j++){
                std::cout << "\t- " << favAnimes[j].name << " with " << favAnimes[j].episodes << " episodes" << " with score " << favAnimes[j].rating  << std::endl;
            }
        }
        else if(duration == "medium"){
            for(int j = (favAnimes.size()/2) - 7; j < (favAnimes.size()/2)+8; j++){
                std::cout << "\t- " << favAnimes[j].name << " with " << favAnimes[j].episodes << " episodes" << " with score " << favAnimes[j].rating  << std::endl;
            }
        }
        else{
            std::cout << "Not found" << std::endl;
        }

        std::cout << std::endl << "The bad recommendations are: " << std::endl;

        if(duration == "long" || duration == "medium"){
            for(int j = badAnimes.size()-1; j > badAnimes.size() - 16; j--){
                std::cout << "\t- " << badAnimes[j].name << " with " << badAnimes[j].episodes << " episodes" << " with score " << badAnimes[j].rating << std::endl;
            }
        } 
        else if(duration == "short"){
            for(int j = 0; j < 15; j++){
                std::cout << "\t- " << badAnimes[j].name << " with " << badAnimes[j].episodes << " episodes" << " with score " << badAnimes[j].rating  << std::endl;
            }
        }
        else{
            std::cout << "Not found" << std::endl;
        }

    }
    return 0;
}