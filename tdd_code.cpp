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
    return myNode;
}

std::vector<Edge> Graph::edges() const{
    return myEdge;
}

Node* Graph::addNode(size_t nodeId) {
    if(Node* tmpNode = (Node*)malloc(sizeof(struct Node))){
        tmpNode->id = nodeId;
        tmpNode->color = 0;
        myNode.push_back(tmpNode);
        return tmpNode;
    }
    return nullptr;
}

bool Graph::addEdge(const Edge& edge){
    if(edge.a != edge.b) {
        myEdge.push_back(edge);
        return true;
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
            //if(permission)
                //myEdge.push_back(edges[i]);
        }
    }
}

Node* Graph::getNode(size_t nodeId){
    return nullptr;
}

bool Graph::containsEdge(const Edge& edge) const{
    return false;
}

void Graph::removeNode(size_t nodeId){
}

void Graph::removeEdge(const Edge& edge){
}

size_t Graph::nodeCount() const{
    return 42;
}

size_t Graph::edgeCount() const{
    return 42;
}

size_t Graph::nodeDegree(size_t nodeId) const{
    return 42;
}

size_t Graph::graphDegree() const{
    return 42;
}

void Graph::coloring(){
}

void Graph::clear() {
    myNode.clear();
    myEdge.clear();
}

/*** Konec souboru tdd_code.cpp ***/
