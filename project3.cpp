#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>
#include <utility>
#include <stack>
#include <stdlib.h>

using namespace std;

struct Node {
    char color;
    string direction;
    int number;
    pair<int, int> location;
    vector<Node*> neighbors;
    
    Node* parent;
    bool visited;
    bool discovered;

    Node(char c, string d, int num, pair<int,int> l){
        color = c;
        direction = d;
        number = num;
        location = l;
        parent = NULL;
    }
    Node(char c, int n, pair<int, int> l){
        color = c;
        number = n;
        location = l;
        parent = NULL;
    }
};

vector<Node> graph;

void printGraph(){
     for(int i = 0; i < graph.size(); i++){
        cout << "Node: " << graph[i].color << graph[i].direction << graph[i].number << endl;
        cout<< "Neighbors " <<endl;
        for(int j =0; j < graph[i].neighbors.size(); j++){
            cout<< graph[i].neighbors[j]->color << graph[i].neighbors[j]->direction << graph[i].neighbors[j]->number << " " <<  endl;
        }
        cout << endl;
     }
}

void findNeighbors(int rows, int columns){
    for(int i = 0; i < graph.size(); i++){
        string dir = graph[i].direction;        //get direction of the node
        int num = graph[i].number;              //get the number of the graph

        if(dir == "N"){
            for(int j = i; j >= 0; j-=columns){
                if(graph[j].color != graph[i].color){
                    graph[i].neighbors.push_back(&graph[j]);
                }
            }
        }
        else if(dir == "S"){
            for(int j = i; j < graph.size(); j+=columns){
                if(graph[j].color != graph[i].color){
                    graph[i].neighbors.push_back(&graph[j]);
                }
            }
        }
         else if(dir == "W"){
            int mod = num % columns;
            for(int j = i; j >= i - mod; j--){
                if(graph[j].color != graph[i].color){
                    graph[i].neighbors.push_back(&graph[j]);
                }
            }
        }
        else if(dir == "E"){
            int mod = (columns - 1) - (num % columns);
            for(int j = i; j <= mod + i; j++){
                if(graph[j].color != graph[i].color){
                    graph[i].neighbors.push_back(&graph[j]);
                }
            }
        }
        else if(dir == "NW"){
            int mod = num % columns;
            int r = graph[i].location.first;
            mod = min(mod, r);
            for(int j = i, k = 0; j >= 0, k <= mod; j-=columns+1, k++){
                if(graph[j].color != graph[i].color){
                    graph[i].neighbors.push_back(&graph[j]);
                }
            }
        } 
            else if(dir == "NE"){
            int mod = (columns - 1) - (num % columns);
            int r = graph[i].location.first;
            mod = min(mod, r);

            for(int j = i, k = 0; j >= 0 && k <= mod; j= j - (columns-1), k++){
                if(graph[j].color != graph[i].color){
                    graph[i].neighbors.push_back(&graph[j]);
                }
            }
        }
        else if(dir == "SE"){
            int mod = (columns - 1) - (num % columns);
            int r = (rows - 1) - graph[i].location.first;
            mod = min(mod, r);

            for(int j = i, k = 0; j <= graph.size() && k <= mod; j+=columns+1, k++){
                if(graph[j].color != graph[i].color){
                    graph[i].neighbors.push_back(&graph[j]);
                }
            }
        }
          else if(dir == "SW"){
            int mod = num % columns;
            int r = (rows - 1) - graph[i].location.first;
            mod = min(mod, r);

            for(int j = i, k = 0; j <= graph.size() && k <= mod; j+=columns-1, k++){
                if(graph[j].color != graph[i].color){
                    graph[i].neighbors.push_back(&graph[j]);
                }
            }
        }   
    }
}

void writeOutput(Node* cur){
    Node* next;
    stack<Node*> path;
    
    while(cur != NULL){
        path.push(cur);
        cur = cur->parent;
    }

    ofstream outputFile("output.txt");
     if (!outputFile.is_open()){
        cout << "Error opening file." <<endl;
       //return 1;
    }

    while(!path.empty()){
        cur = path.top();
        path.pop();
        int traveled = 0;
        if(!path.empty()){
             next = path.top();
        if(cur->direction == "N" || cur->direction == "S"){
           traveled = abs(cur->location.first - next->location.first);
        } else if (cur->direction == "E" || cur->direction == "W"){
            traveled = abs(cur->location.second - next->location.second);
        } else {
            traveled = abs(cur->location.second - next->location.second);
        }
        
        outputFile << traveled;
        outputFile << cur->direction;
        outputFile << " ";
        }
       
    }
      outputFile.close();
      return;
    }

void BFS(Node* begin, Node* end){
    queue<Node*> q;             //create queue for BFS search

    for(int i = 0; i < graph.size(); i++){      //set all nodes to not discovered and not explored
        graph[i].visited = false;
        graph[i].discovered = false;
    }

    q.push(begin);              //push first node to queue
    while(!q.empty()){          
        Node* cur = q.front();
        q.pop();

        cur->visited = true;
        
        if (cur == end){		//target was found in the maze
                writeOutput(cur);	//write to output
                return;
            }

        Node* arrow;
        for(int j = 0; j < cur->neighbors.size(); ++j){
           arrow = cur->neighbors[j];
            if(arrow->visited == false){
                arrow->parent = cur;
                q.push(arrow);
                arrow->discovered = true;
            }
        }
    }
    return;
}


int main() {


     //1. read in the file as a matrix of strings or as a matrix of structs
       
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()){
        cout << "Error opening file." <<endl;
        return 1;
    }

    int rows;
    int columns;

    inputFile >> rows;
    inputFile >> columns;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            char color;
            string dir;
            
            inputFile >> color; 
            inputFile >> dir;
            pair <int, int> location = make_pair(i, j);

            if (color == 'O'){
                Node newNode(color, graph.size(), location);
                graph.push_back(newNode);
                break;
            }
        
            Node newNode(color,dir.substr(1),graph.size(), location);
            graph.push_back(newNode);
        }
    }

   inputFile.close();
   findNeighbors(rows, columns);    //2. after reading the file, create the adjacency list

    //3. Perform BFS traversal and print path to output file
    BFS(&graph[0], &graph[graph.size() - 1]);

  return 0;
}
