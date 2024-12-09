#ifndef WeightedDirectedGraph_hpp
#define WeightedDirectedGraph_hpp

#include <iostream>
#include <vector>
#include <unordered_map> 
#include <queue>
#include <stack>
#include <limits>

template<typename T>
class WeightedNotDirectecGraph
{
    private:

        std::vector<T> Vertex;
        std::vector<std::vector<double>> Matrix;

    public:

        // Constructor
        WeightedNotDirectecGraph() : Vertex(), Matrix() {}

        WeightedNotDirectecGraph(const T& V) : Vertex(1,V), Matrix(1,std::vector<double>(1,std::numeric_limits<double>::infinity())) {}

        // Destructor
        ~WeightedNotDirectecGraph(){
            Vertex.clear();
            Matrix.clear();
        }

        // Checks if empty
        bool empty(){
            return Vertex.empty();
        }

        // Clears the graph
        void clear(){
            for(int i = 0; i < Vertex.size(); ++i){
                Matrix[i].clear();
            }
            Matrix.clear();
            Vertex.clear();
        }

        // Adds a vertex to the graph
        void addVertex(const T& V){
            if(std::find(Vertex.begin(), Vertex.end(), V) == Vertex.end()) {
                Vertex.push_back(V);
                for(int i = 0; i < Matrix.size(); ++i){
                    Matrix[i].push_back(std::numeric_limits<double>::infinity());
                }
                Matrix.push_back(std::vector<double>(Vertex.size(),std::numeric_limits<double>::infinity()));
            }
        }

        // Removes a vertex
        void removeVertex(const T& V){
            auto it = std::find(Vertex.begin(), Vertex.end(), V);
            int index = it -  Vertex.begin();
            Vertex.erase(it);
            Matrix.erase(Matrix.begin() + index);
            for(int i = 0; i < Matrix.size(); ++i){
                Matrix[i].erase(Matrix[i].begin() + index);
            }
        }

        // Checks if a vertex is on the graph
        bool containsVertex(const T& V){
            return std::find(Vertex.begin(), Vertex.end(), V) != Vertex.end();
        }

        // Adds an edge between two vertex
        void addEdge(const T& V1, const T& V2, const double& W){
            int i = std::distance(Vertex.begin(), std::find(Vertex.begin(), Vertex.end(), V1));
            int j = std::distance(Vertex.begin(), std::find(Vertex.begin(), Vertex.end(), V2));
            if(containsVertex(V1) && containsVertex(V2)){
                Matrix[i][j] = W;
                Matrix[j][i] = W;
            }
        }

        // Removes an edge between two vertex
        void removeEdge(const T& V1, const T& V2){
            int i = std::distance(Vertex.begin(), std::find(Vertex.begin(), Vertex.end(), V1));
            int j = std::distance(Vertex.begin(), std::find(Vertex.begin(), Vertex.end(), V2));
            if(containsVertex(V1) && containsVertex(V2)){
                Matrix[i][j] = std::numeric_limits<double>::infinity();
                Matrix[j][i] = std::numeric_limits<double>::infinity();
            }
        }

        // Checks if the graph has an edge
        bool containsEdge(const T& V1, const T& V2){
            int i = std::distance(Vertex.begin(), std::find(Vertex.begin(), Vertex.end(), V1));
            int j = std::distance(Vertex.begin(), std::find(Vertex.begin(), Vertex.end(), V2));
            return Matrix[i][j] < std::numeric_limits<double>::infinity() && Matrix[j][i] < std::numeric_limits<double>::infinity(); 
        }

        // Returns the weight of the arc
        double weight(const T& V1, const T& V2){
            int i = std::distance(Vertex.begin(), std::find(Vertex.begin(), Vertex.end(), V1));
            int j = std::distance(Vertex.begin(), std::find(Vertex.begin(), Vertex.end(), V2));
            if(containsEdge(V1, V2)){
                return Matrix[i][j];
            }
            return std::numeric_limits<double>::infinity();
        }

        // Returns a list of the neighbors of a given vertex
        std::vector<std::pair<T,double>> neighbors(const T& V){
            int index = std::distance(Vertex.begin(), std::find(Vertex.begin(), Vertex.end(), V));
            std::vector<std::pair<T,double>> neighbors;
            for(int i = 0; i < Matrix.size(); ++i){
                if(Matrix[index][i] < std::numeric_limits<double>::infinity()){
                    std::pair<T, double> aux(Vertex[i],Matrix[index][i]);
                    neighbors.push_back(aux);
                }
            }
            return neighbors;
        }

        // Returns the degree of a vertex
        int degree(const T& V){
            int index = std::distance(Vertex.begin(), std::find(Vertex.begin(), Vertex.end(), V));
            int degree = 0;
            for(int i = 0; i < Matrix.size(); ++i){
                if(Matrix[index][i] < std::numeric_limits<double>::infinity()){
                    degree++;
                }
            }
            return degree;
        }

        // BFS
        std::vector<T> BFS(const T& Start){
            // Checks if empty
            if (Vertex.empty()) {
                std::cout << "Graph is empty" << std::endl;
                return std::vector<T>();
            }

            std::unordered_map<T, int> mapping;
            for(int i = 0; i < Vertex.size(); ++i){
                mapping[Vertex[i]] = i;
            }

            std::vector<bool> explored(Vertex.size(), false);
            std::queue<T> frontier;
            std::vector<T> visited;

            frontier.push(Start);
            explored[mapping.at(Start)] = true;

            while (!frontier.empty()){
                T current = frontier.front();
                frontier.pop();
                int currentIndex = mapping.at(current);
                visited.push_back(Vertex[currentIndex]);

                std::vector<std::pair<T, double>> neighbor = neighbors(current);

                for(int j = 0; j < neighbor.size(); ++j){
                    if(explored[mapping.at(neighbor[j].first)] == false)
                        frontier.push(neighbor[j].first);
                        explored[mapping.at(neighbor[j].first)] = true;
                }
            }
            return visited;
        }

        // DFS
        std::vector<T> DFS(const T& Start){
            // Checks if empty
            if (Vertex.empty()) {
                std::cout << "Graph is empty" << std::endl;
                return std::vector<T>();
            }

            std::unordered_map<T, int> mapping;
            for(int i = 0; i < Vertex.size(); ++i){
                mapping[Vertex[i]] = i;
            }

            std::vector<bool> explored(Vertex.size(), false);
            std::stack<T> frontier;
            std::vector<T> visited;

            frontier.push(Start);
            explored[mapping.at(Start)] = true;

            while (!frontier.empty()){
                T current = frontier.top();
                frontier.pop();
                int currentIndex = mapping.at(current);
                visited.push_back(Vertex[currentIndex]);

                std::vector<std::pair<T, double>> neighbor = neighbors(current);

                for(int j = 0; j < neighbor.size(); ++j){
                    if(explored[mapping.at(neighbor[j].first)] == false)
                        frontier.push(neighbor[j].first);
                        explored[mapping.at(neighbor[j].first)] = true;
                }
            }
            return visited;
        }

        // BFS path
        std::pair<std::vector<T>, double> findPathBFS(const T& Start, const T& End){

            std::pair<std::vector<T>, double> path;

            // Check if the graph is empty
            if (Vertex.empty()) {
                std::cout << "Graph is empty" << std::endl;
                return path;
            }

            // Check if the vertices exist
            if (!containsVertex(Start) || !containsVertex(End)){
                std::cout << "One or more vertices do not exist" << std::endl;
                return path;
            }

            std::unordered_map<T, int> mapping;
            for(int i = 0; i < Vertex.size(); ++i){
                mapping[Vertex[i]] = i;
            }

            std::vector<bool> explored(Vertex.size(), false);
            std::queue<T> frontier;
            std::unordered_map<T, std::pair<T, double>> parents;

            frontier.push(Start);
            explored[mapping.at(Start)] = true;
            parents[Start].first = T();
            parents[Start].second = 0;

            while(!frontier.empty()){
                T current = frontier.front();
                frontier.pop();

                if(current == End){

                    T pathVertex = current;

                    while (pathVertex != T()){
                        path.first.push_back(pathVertex);
                        path.second = path.second + parents[pathVertex].second;
                        pathVertex = parents[pathVertex].first;
                    }

                    std::reverse(path.first.begin(), path.first.end());
                    break;
                }

                std::vector<std::pair<T,double>> neighbor = neighbors(current);

                for(int j = 0; j < neighbor.size(); ++j){
                    if(explored[mapping.at(neighbor[j].first)] == false){
                        frontier.push(neighbor[j].first);
                        explored[mapping.at(neighbor[j].first)] = true;
                        parents[neighbor[j].first].first = current;
                        parents[neighbor[j].first].second = neighbor[j].second;
                    }
                }
            }
            return path;
        }

        // DFS path
        std::pair<std::vector<T>, double> findPathDFS(const T& Start, const T& End){
            
            std::pair<std::vector<T>, double> path;

            // Check if the graph is empty
            if (Vertex.empty()) {
                std::cout << "Graph is empty" << std::endl;
                return path;
            }

            // Check if the vertices exist
            if (!containsVertex(Start) || !containsVertex(End)){
                std::cout << "One or more vertices do not exist" << std::endl;
                return path;
            }

            std::unordered_map<T, int> mapping;
            for(int i = 0; i < Vertex.size(); ++i){
                mapping[Vertex[i]] = i;
            }

            std::vector<bool> explored(Vertex.size(), false);
            std::stack<T> frontier;
            std::unordered_map<T, std::pair<T, double>> parents;

            frontier.push(Start);
            explored[mapping.at(Start)] = true;
            parents[Start].first = T();
            parents[Start].second = 0;

            while(!frontier.empty()){
                T current = frontier.top();
                frontier.pop();

                if(current == End){

                    T pathVertex = current;

                    while (pathVertex != T()){
                        path.first.push_back(pathVertex);
                        path.second = path.second + parents[pathVertex].second;
                        pathVertex = parents[pathVertex].first;
                    }

                    std::reverse(path.first.begin(), path.first.end());
                    break;
                }

                std::vector<std::pair<T,double>> neighbor = neighbors(current);

                for(int j = 0; j < neighbor.size(); ++j){
                    if(explored[mapping.at(neighbor[j].first)] == false){
                        frontier.push(neighbor[j].first);
                        explored[mapping.at(neighbor[j].first)] = true;
                        parents[neighbor[j].first].first = current;
                        parents[neighbor[j].first].second = neighbor[j].second;
                    }
                }
            }
            return path;
        }

};

#endif