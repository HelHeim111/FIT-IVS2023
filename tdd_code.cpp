//======== Copyright (c) 2023, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"

/*int myFindNodeId(std::vector<Node*>vec, size_t id) {
    for(int i = 0; i < vec.size(); i++) {
        if(vec[i]->id == id){
            return i;
        }
    }
    return -1;
}*/

Graph::Graph(){}

Graph::~Graph(){}

std::vector<Node*> Graph::nodes() {
    std::vector<Node*> nodes;
    nodes = myNode;
    return nodes;
}

std::vector<Edge> Graph::edges() const{
    std::vector<Edge> edges;
    edges = myEdge;
    return edges;
}

Node* Graph::addNode(size_t nodeId) {
    bool exists = true;
    for(int i = 0; i < myNode.size(); i++){
        if(myNode[i]->id == nodeId) {
            exists = false;
            break;
        }
    }
    if(exists){
        if(Node* tmpNode = (Node*)malloc(sizeof(struct Node))){
            tmpNode->id = nodeId;
            tmpNode->color = 0;
            myNode.push_back(tmpNode);
            return tmpNode;
        }
    }
    return nullptr;
}

bool Graph::addEdge(const Edge& edge){
    bool permission = true;
    if(edge.a != edge.b) {
        for(int j = 0; j < myEdge.size(); j++){
                if(edge.operator==(myEdge[j])) {
                    permission = false;
                    break;
                }
            }
            if(permission){
                addNode(edge.a);
                addNode(edge.b);
                myEdge.push_back(edge);
                return true;
            }
        
    }
    return false;
}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for(int i = 0; i < edges.size(); i++) {
        bool permission = true;
        if(edges[i].a != edges[i].b) {
            for(int j = 0; j < myEdge.size(); j++){
                if(edges[i].operator==(myEdge[j])) {
                    permission = false;
                    break;
                }
            }
            if(permission){
                addNode(edges[i].a);
                addNode(edges[i].b);
                myEdge.push_back(edges[i]);
            }
        }
    }
}

Node* Graph::getNode(size_t nodeId){
    for(auto vec : myNode) {
        if(vec->id == nodeId){
            return vec;
        }
    }
    return nullptr;
}

bool Graph::containsEdge(const Edge& edge) const{
    for(auto vec : myEdge) {
        if(edge.operator==(vec)) {
            return true;
        }
    }
    return false;
}

void Graph::removeNode(size_t nodeId){
    bool exists = false;
    for(int i = 0; i < myNode.size(); i++) {
        if(myNode[i]->id == nodeId) {
            myNode.erase(myNode.begin() + i);
            exists = true;
            break;
        }
    }
    if(!exists) {
        throw std::out_of_range("");
    }

     
    while(true) {
        bool completed = true;
        for(auto vec : myEdge) {
            if(vec.a == nodeId || vec.b == nodeId) {
                removeEdge(vec);
                completed = false;
                break;
            }
        }
        if(completed)
            break;
    }
}

void Graph::removeEdge(const Edge& edge){
    bool exists = false;
    for(int i = 0; i < myEdge.size(); i++) {
        if(edge.operator==(myEdge[i])) {
            myEdge.erase(myEdge.begin() + i);
            exists = true;
            break;
        }
    }
    if(!exists) {
        throw std::out_of_range("");
    }
}

size_t Graph::nodeCount() const{
    return myNode.size();
}

size_t Graph::edgeCount() const{
    return myEdge.size();
}

size_t Graph::nodeDegree(size_t nodeId) const{
    bool exists = false;
    for(auto vec : myNode) {
        if(vec->id == nodeId){
            exists = true;
            break;
        }
    }
    if(!exists){
        throw std::out_of_range("");
    }

    size_t degree = 0;
    for(auto vec : myEdge) {
        if(vec.a == nodeId || vec.b == nodeId) {
            degree++;
        }
    }
    return degree;
}

size_t Graph::graphDegree() const{
    size_t maxDegree = 0;
    for(auto vec : myNode) {
        if(nodeDegree(vec->id) > maxDegree) {
            maxDegree = nodeDegree(vec->id);
        }
    }
    return maxDegree;
}

void Graph::coloring(){
    size_t allColors = graphDegree() + 1;
    std::vector<size_t> availableColors;
    for(auto v : myNode) {
        for(int i = 1; i <= allColors; i++) {
            availableColors.push_back(i);
        }
        if(v->color == 0) {
            for(auto tmpVec : myEdge) {
                if(tmpVec.a == v->id) {
                    if(getNode(tmpVec.b)->color != 0) {
                        for(int i = 0; i < availableColors.size(); i++) {
                            if(availableColors[i] == getNode(tmpVec.b)->color) {
                                availableColors.erase(availableColors.begin() + i);
                            }
                        }
                    }           
                }
                if(tmpVec.b == v->id) {
                    if(getNode(tmpVec.a)->color != 0) {
                        for(int i = 0; i < availableColors.size(); i++) {
                            if(availableColors[i] == getNode(tmpVec.a)->color) {
                                availableColors.erase(availableColors.begin() + i);
                            }
                        }
                    }
                }
            }
            v->color = availableColors[0];
        }
        availableColors.clear();
    }
}

void Graph::clear() {
    myNode.clear();
    myEdge.clear();
}

/*** Konec souboru tdd_code.cpp ***/
