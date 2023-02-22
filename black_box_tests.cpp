//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Denys Petrovskyi <xpetro27@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Denys Petrovskyi
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>
#include <stdio.h>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//


TEST(EmptyTree, InsertNode) {
    BinaryTree *tmpTree = new BinaryTree;
    std::pair<bool, Node_t *> newNode = tmpTree->InsertNode(1);
    ASSERT_TRUE(newNode.first == true);
    delete(tmpTree);
}

TEST(EmptyTree, DeleteNode) {
    BinaryTree *tmpTree = new BinaryTree;
    bool result = tmpTree->DeleteNode(1);
    ASSERT_TRUE(result == false);
    delete(tmpTree);
}

TEST(EmptyTree, FindNode) {
    BinaryTree *tmpTree = new BinaryTree;
    Node_t* result = tmpTree->FindNode(1);
    ASSERT_TRUE(NULL == result);
    delete(tmpTree);
}


TEST(NonEmptyTree, InsertNode) {
    BinaryTree *tmpTree = new BinaryTree;
    std::pair<bool, Node_t *> newNode = tmpTree->InsertNode(1);
    ASSERT_TRUE(newNode.first == true);
    newNode = tmpTree->InsertNode(1);
    ASSERT_TRUE(newNode.first == false);
    newNode = tmpTree->InsertNode(4);
    ASSERT_TRUE(newNode.first == true);
    delete(tmpTree);
}

TEST(NonEmptyTree, DeleteNode) {
    BinaryTree *tmpTree = new BinaryTree;
    tmpTree->InsertNode(1);
    bool result = tmpTree->DeleteNode(1);
    ASSERT_TRUE(result == true);
    result = tmpTree->DeleteNode(5);
    ASSERT_TRUE(result == false);
    delete(tmpTree);
}

TEST(NonEmptyTree, FindNode) {
    BinaryTree *tmpTree = new BinaryTree;
    tmpTree->InsertNode(1);
    Node_t* result = tmpTree->FindNode(4);
    ASSERT_TRUE(NULL == result);
    result = tmpTree->FindNode(1);
    ASSERT_TRUE(NULL != result);
    delete(tmpTree);
}


TEST(TreeAxioms, Axiom1) {
    BinaryTree *tmpTree = new BinaryTree;
    std::vector<int> keys = {1,5,7,11,56};
    std::vector<std::pair<bool, Node_t*>> out;
    std::vector<Node_t*> leaf;
    tmpTree->InsertNodes(keys, out);
    tmpTree->GetLeafNodes(leaf);
    for(Node_t* i: leaf) {
        ASSERT_TRUE(i->color != 0);
    }
    delete(tmpTree);
}

TEST(TreeAxioms, Axiom2) {
    BinaryTree *tmpTree = new BinaryTree;
    std::vector<int> keys = {1,5,7,11,56};
    std::vector<std::pair<bool, Node_t*>> out;
    std::vector<Node_t*> all;
    tmpTree->InsertNodes(keys, out);
    tmpTree->GetAllNodes(all);
    for(Node_t* i: all) {
        if(i->color == 0) {
            ASSERT_TRUE(i->pRight->color != 0);
            ASSERT_TRUE(i->pLeft->color != 0);
        }
    }
    delete(tmpTree);
}

TEST(TreeAxioms, Axiom3) {
    BinaryTree *tmpTree = new BinaryTree;
    std::vector<int> keys = {1,5,7,11,56};
    std::vector<std::pair<bool, Node_t*>> out;
    std::vector<Node_t*> leaf;
    Node_t* root = tmpTree->GetRoot();
    tmpTree->InsertNodes(keys, out);
    tmpTree->GetLeafNodes(leaf);
    int blackLength = -1;
    for(Node_t* i: leaf) {
        int blackLengthTmp = 0;
        Node_t* tmpNode = i->pParent;
        while(tmpNode != root){
            if(tmpNode->color != 0) {
                blackLengthTmp++;
            }
            tmpNode = tmpNode->pParent;
        }
        if(blackLength == -1) {
            blackLength = blackLengthTmp;
        }
        else {
            ASSERT_TRUE(blackLength == blackLengthTmp);
        }
    }
    delete(tmpTree);
}


/*** Konec souboru black_box_tests.cpp ***/
