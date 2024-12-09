#include <_stdlib.h>
#include <chrono>
#include <iostream>
#include <string>
#include <filesystem>
#include "ADTs/dynamicArray.hpp"
#include "ADTs/avlTree.hpp"
#include "ADTs/avl.hpp"
#include "ADTs/WeightedNotDirectedGraph.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

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

    bool operator==(const Anime& other) const {
        return name == other.name;
    }

};

// Hash function
namespace std {
    template <>
    struct hash<Anime> {
        size_t operator()(const Anime& anime) const {
            return hash<std::string>()(anime.name); // Only hash the name
        }
    };
}

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

/* Similarity between 2 nodes */

double Similarity(const Anime& A1, const Anime& A2){
    
    double episodeSimilarity = 0;
    double genreSimilarity = 0;
    double typeSimilarity = 0;

    // EPISODES
    double difference = std::abs(A1.episodes - A2.episodes);
    episodeSimilarity = 0.375 * std::exp(-.01 * difference);
    
    std::vector<std::string> genre1;
    std::vector<std::string> genre2;

    // GENRE
    std::string temp;

    std::stringstream genreStream1(A1.genre);
    while (std::getline(genreStream1, temp, ',')) {
        genre1.push_back(temp);
    }

    std::stringstream genreStream2(A2.genre);
    while (std::getline(genreStream2, temp, ',')) {
        genre2.push_back(temp);
    }

    int minSize = std::min(genre1.size(), genre2.size());
    int equals = 0;

    if(genre1.size() > genre2.size()){
        for(int i = 0; i < genre2.size(); ++i){
            for(int j = 0; j < genre1.size(); ++j){
                if(genre2[i] == genre1[j]){
                    equals++;
                }
            }
        }
    }
    else{
        for(int i = 0; i < genre1.size(); ++i){
            for(int j = 0; j < genre2.size(); ++j){
                if(genre1[i] == genre2[j]){
                    equals++;
                }
            }
        }
    }

    difference = std::abs(minSize - equals);
    genreSimilarity = 0.375 * std::exp(-.4 * difference);

    // TYPE
    if(A1.type == A2.type){
        typeSimilarity = .25;
    }
    else{
        typeSimilarity = 0;
    }

    return 1 - (genreSimilarity + episodeSimilarity + typeSimilarity);
}

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

        dynamicArray<Anime> animesArray = ArrayReadAnimeCSV(filename);

    //---------------------------------------------------------------------------------------------------------------------------------------------------//
    // ENTREGABLE 2: PASO 1

    // Construcción del árbol AVL
    AVLTree avlTree;
    auto start_build = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < animesArray.size(); ++i) {
        avlTree.insert(animesArray[i].name, i);
    }

    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
    auto stop_build = std::chrono::high_resolution_clock::now();
    auto duration_build = std::chrono::duration_cast<std::chrono::milliseconds>(stop_build - start_build);
    std::cout << "Tiempo para construir el árbol AVL: " << duration_build.count() << " ms" << std::endl;
    std::cout << "\n";

    // Realizar 20 búsquedas
    std::vector<std::string> searchQueries = {
        "Kimi no Na wa.",
        "Fullmetal Alchemist: Brotherhood",
        "Gintama°",
        "Steins;Gate",
        "Kara no Kyoukai 5: Mujun Rasen",
        "Haikyuu!!: Karasuno Koukou VS Shiratorizawa Gakuen Koukou",
        "Hunter x Hunter (2011)",
        "Ginga Eiyuu Densetsu",
        "Gintama Movie: Kanketsu-hen - Yorozuya yo Eien Nare",
        "Gintama': Enchousen",
        "Clannad: After Story",
        "Koe no Katachi",
        "Gintama",
        "Code Geass: Hangyaku no Lelouch R2",
        "Haikyuu!! Second Season",
        "Sen to Chihiro no Kamikakushi",
        "Shigatsu wa Kimi no Uso",
        "Mushishi Zoku Shou 2nd Season",
        "Ookami Kodomo no Ame to Yuki",
        "Code Geass: Hangyaku no Lelouch",
        "Hajime no Ippo",
        "Rurouni Kenshin: Meiji Kenkaku Romantan - Tsuioku-hen",
        "Cowboy Bebop",
        "One Punch Man",
        "Mononoke Hime",
        "Suzumiya Haruhi no Shoushitsu",
        "Monogatari Series: Second Season",
        "Mushishi Zoku Shou",
        "Akira_",  // Inventado
        "Naruto_Shippuden",  // Inventado
        "Death_Note",  // Inventado
        "Attack_on_Titan",  // Inventado
        "Demon_Slayer"  // Inventado
    };

    std::cout << "Optimización de búsquedas de productos: ";
    std::cout << "\n";
    for (const auto& query : searchQueries) {
        auto start_search = std::chrono::high_resolution_clock::now();
        AVLNode* result = avlTree.search(query);
        auto stop_search = std::chrono::high_resolution_clock::now();
        auto duration_search = std::chrono::duration_cast<std::chrono::milliseconds>(stop_search - start_search);

        if (result != nullptr && result->name == query) {
            std::cout << "\n";
            std::cout << "Producto encontrado: " << animesArray[result->index].name << " con " << animesArray[result->index].episodes << " episodios" << std::endl;
        } else {
            std::cout << "\n";
            std::cout << "Producto no encontrado, el nodo más cercano es: " << animesArray[result->index].name << " con " << animesArray[result->index].episodes << " episodios." << std::endl;
        }

        std::cout << "Tiempo para encontrar el producto: " << duration_search.count() << " ms" << std::endl;
    }

    //---------------------------------------------------------------------------------------------------------------------------------------------------//
    // ENTREGABLE 2: PASO 2

    // Construcción del árbol AVL para categorias
    AVL arbolCategorias;

    auto start_build_cat = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < animesArray.size(); ++i) {
        arbolCategorias.insertarProducto(animesArray[i].genre, i);
    }

    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
    auto stop_build_cat = std::chrono::high_resolution_clock::now();
    auto duration_build_cat = std::chrono::duration_cast<std::chrono::milliseconds>(stop_build_cat - start_build_cat);
    std::cout << "Tiempo para construir el árbol AVL: " << duration_build_cat.count() << " ms" << std::endl;
    std::cout << "\n";

    // Realizar 20 búsquedas
    std::vector<std::string> searchQueriesCategorias = {
        "Drama,Romance,School,Supernatural",  // Kimi no Na wa.
        "Action,Adventure,Drama,Fantasy,Magic,Military,Shounen",  // Fullmetal Alchemist: Brotherhood
        "Action,Comedy,Historical,Parody,Samurai,Sci-Fi,Shounen",  // Gintama°
        "Sci-Fi,Thriller",  // Steins;Gate
        "Action,Comedy,Historical,Parody,Samurai,Sci-Fi,Shounen",  // Gintama'
        "Comedy,Drama,School,Shounen,Sports",  // Haikyuu!!: Karasuno Koukou VS Shiratorizawa Gakuen Koukou
        "Action,Adventure,Shounen,Super Power",  // Hunter x Hunter (2011)
        "Drama,Military,Sci-Fi,Space",  // Ginga Eiyuu Densetsu
        "Action,Comedy,Historical,Parody,Samurai,Sci-Fi,Shounen",  // Gintama Movie: Kanketsu-hen - Yorozuya yo Eien Nare
        "Action,Comedy,Historical,Parody,Samurai,Sci-Fi,Shounen",  // Gintama': Enchousen
        "Drama,Fantasy,Romance,Slice of Life,Supernatural",  // Clannad: After Story
        "Drama,School,Shounen",  // Koe no Katachi
        "Action,Comedy,Historical,Parody,Samurai,Sci-Fi,Shounen",  // Gintama
        "Action,Drama,Mecha,Military,Sci-Fi,Super Power",  // Code Geass: Hangyaku no Lelouch R2
        "Comedy,Drama,School,Shounen,Sports",  // Haikyuu!! Second Season
        "Adventure,Drama,Supernatural",  // Sen to Chihiro no Kamikakushi
        "Drama,Music,Romance,School,Shounen",  // Shigatsu wa Kimi no Uso
        "Adventure,Fantasy,Historical,Mystery,Seinen,Slice of Life,Supernatural",  // Mushishi Zoku Shou 2nd Season
        "Fantasy,Slice of Life",  // Ookami Kodomo no Ame to Yuki
        "Action,Mecha,Military,School,Sci-Fi,Super Power",  // Code Geass: Hangyaku no Lelouch
        "Comedy,Drama,Shounen,Sports",  // Hajime no Ippo
        "Action,Drama,Historical,Martial Arts,Romance,Samurai",  // Rurouni Kenshin: Meiji Kenkaku Romantan - Tsuioku-hen
        "Action,Adventure,Comedy,Drama,Sci-Fi,Space",  // Cowboy Bebop
        "Action,Comedy,Parody,Sci-Fi,Seinen,Super Power,Supernatural",  // One Punch Man
        "Action,Adventure,Fantasy",  // Mononoke Hime
        "Comedy,Mystery,Romance,School,Sci-Fi,Supernatural",  // Suzumiya Haruhi no Shoushitsu
        "Comedy,Mystery,Romance,Supernatural,Vampire",  // Monogatari Series: Second Season
        "Adventure,Fantasy,Historical,Mystery,Seinen,Slice of Life,Supernatural",  // Mushishi Zoku Shou
        "Action,Adventure",  // Akira (Inventado)
        "Shounen,Action,Adventure",  // Naruto Shippuden (Inventado)
        "Psychological,Thriller, Mystery",  // Death Note (Inventado)
        "Action,Adventure,Mystery",  // Attack on Titan (Inventado)
        "Action,Supernatural,Shounen"  // Demon Slayer (Inventado)
    };

    std::cout << "Optimización de búsquedas de categorias: ";
    std::cout << "\n";
    for (const auto& query : searchQueriesCategorias) {
        auto start_search = std::chrono::high_resolution_clock::now();
        AVLN* result = arbolCategorias.searchCategory(query);
        auto stop_search = std::chrono::high_resolution_clock::now();
        auto duration_search = std::chrono::duration_cast<std::chrono::milliseconds>(stop_search - start_search);


        if (result != nullptr && result->categoria == query) {
            std::cout << "\n";
            std::cout << "Producto encontrado: " << animesArray[result->index].name << " con " << animesArray[result->index].episodes << " episodios" << std::endl;
        } 
        else {
            // Buscar el anime más cercano cuando no hay coincidencia exacta
            AVLN* bestMatch = arbolCategorias.searchCategory(query);
            if (bestMatch != nullptr) {
                std::cout << "\n";
                std::cout << "Producto no encontrado, el anime más cercano es: " << animesArray[bestMatch->index].name << " con " << animesArray[bestMatch->index].episodes << " episodios" << std::endl;
            } else {
                std::cout << "\n";
                std::cout << "Producto no encontrado, no hay coincidencias cercanas." << std::endl;
            }
        }


        std::cout << "Tiempo para encontrar el producto: " << duration_search.count() << " ms" << std::endl;
    }

    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;

    //---------------------------------------------------------------------------------------------------------------------------------------------------//
    // ENTREGABLE 2: PASO 3

    /* Make graph with the animes */

        WeightedNotDirectecGraph<Anime> graph;

        for(int i = 0; i < animesArray.size(); ++i){
            graph.addVertex(animesArray[i]);
        }

    /* Calculate the similarity */

        // helps to make the process faster by not doing the whole database
        int auxTime = 11000;

        for(int i = 0; i < animesArray.size() - auxTime; ++i){
            for(int j = i + 1; j < animesArray.size() - auxTime; ++j){
                double weight = Similarity(animesArray[i], animesArray[j]);
                if(weight < .8){
                    graph.addEdge(animesArray[i], animesArray[j], weight);
                }
            }
        }

    /* Neighbors */

        std::vector<std::string> names = {
            "Kimi no Na wa.",
            "Hunter x Hunter (2011)",
            "Clannad: After Story",
            "Gintama",
            "Mononoke Hime",
            "Haikyuu!!",
            "Kara no Kyoukai 5: Mujun Rasen",
            "Zoku Natsume Yuujinchou",
            "Ping Pong The Animation",
            "Fate/Zero 2nd Season",
            "Angel Beats!",
            "Shelter",
            "Kaguya-hime no Monogatari",
            "Hunter x Hunter: Greed Island",
            "Nagi no Asukara",
            "One Piece Film: Gold",
            "Baccano! Specials",
            "Kill la Kill",
            "Tengen Toppa Gurren Lagann Movie: Gurren-hen",
            "Aria The Avvenire"
        };

        std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "GRAFO. Calcular los vecinos de 20 animes y su porcentaje de similitud" << std::endl;
        std::cout << "\n";

        for(int i = 0; i < names.size(); ++i){
            std::cout << std::endl << "5 vecinos de el anime " << names[i] << "son: " << std::endl;
            Anime aux(0,names[i],"","",0,0,0);
            std::vector<std::pair<Anime, double>> neighbors = graph.neighbors(aux);
            for(int j = 0; j < 5; ++j){
                std::cout << "\t" << neighbors[j].first.name << " con una similitud del " << (1 - neighbors[j].second)*100 << "%" << std::endl;
            }
        }

    //---------------------------------------------------------------------------------------------------------------------------------------------------//
    // ENTREGABLE 2: PASO 4

    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    std::vector<std::string> names1 = {
        "Kimi no Na wa.",
        "Hunter x Hunter (2011)",
        "Clannad: After Story",
        "Gintama",
        "Mononoke Hime",
    };

    for(int i = 0; i < names1.size(); ++i){
        Anime aux(0,names1[i],"","",0,0,0);

        std::cout << std::endl << "Recorrido BFS del anime " << names1[i] << ": " << std::endl;
        std::vector<Anime> BFS = graph.BFS(aux);
        for(int j = 0; j < 10; ++j){
            std::cout << "\t" << BFS[j].name << std::endl;
        }

        std::cout << std::endl << "Recorrido DFS del anime " << names1[i] << ": " << std::endl;
        std::vector<Anime> DFS = graph.DFS(aux);
        for(int j = 0; j < 10; ++j){
            std::cout << "\t" << DFS[j].name << std::endl;
        }

        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    }

    std::vector<std::string> names2 = {
        "Kimi no Na wa.",
        "Hunter x Hunter (2011)",
        "One Piece Film: Gold",
        "Baccano! Specials",
        "Clannad: After Story",
        "Kill la Kill", 
        "Gintama",
        "Tengen Toppa Gurren Lagann Movie: Gurren-hen",
        "Mononoke Hime",
        "Aria The Avvenire"
    };

    for(int i = 0; i < names2.size(); i+=2){
        Anime aux(0,names2[i],"","",0,0,0);
        Anime aux1(0,names2[i+1],"","",0,0,0);

        std::cout << std::endl << "Camino BFS del anime " << names2[i] << " al anime " << names2[i+1] << ": " << std::endl;
        std::pair<std::vector<Anime>, double> BFS = graph.findPathBFS(aux,aux1);
        for(int j = 0; j < BFS.first.size(); ++j){
            std::cout << "\t" << BFS.first[j].name << std::endl;
        }
        std::cout << std::endl << "Con una distancia de " << BFS.second << std::endl;

        std::cout << std::endl << "Camino DFS del anime " << names2[i] << " al anime " << names2[i+1] << ": " << std::endl;
        std::pair<std::vector<Anime>, double> DFS = graph.findPathDFS(aux,aux1);
        for(int j = 0; j < DFS.first.size(); ++j){
            std::cout << "\t" << DFS.first[j].name << std::endl;
        }
        std::cout << std::endl << "Con una distancia de " << DFS.second << std::endl;

        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    }

    return 0;
}