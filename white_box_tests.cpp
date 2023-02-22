//======== Copyright (c) 2022, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     Denys Petrovskyi <xpetro27@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Denys Petrovskyi
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//

TEST(HashMap, Ctor) {
    hash_map* tmpHash = hash_map_ctor();
    ASSERT_TRUE(NULL != tmpHash);
    hash_map_dtor(tmpHash);
}

TEST(HashMap, Reserved) {
    hash_map* tmpHash = hash_map_ctor();
    hash_map_state_code_t var = hash_map_reserve(tmpHash, 18); //test for empty map
    ASSERT_TRUE(OK == var);
    hash_map_put(tmpHash, "key1", 44);
    var = hash_map_reserve(tmpHash, 18); //test for nonempty map
    ASSERT_TRUE(OK == var);
    hash_map_dtor(tmpHash);
}

TEST(HashMap, Put) {
    hash_map* tmpHash = hash_map_ctor();
    hash_map_state_code_t var = hash_map_put(tmpHash, "key1", 44); //test for empty map
    ASSERT_TRUE(OK == var);
    var = hash_map_put(tmpHash, "key1", 45); //test for nonempty map
    ASSERT_TRUE(KEY_ALREADY_EXISTS == var);
    hash_map_dtor(tmpHash);
}

TEST(HashMap, Size) {
    hash_map* tmpHash = hash_map_ctor();
    size_t tmpSize = hash_map_size(tmpHash);
    ASSERT_TRUE(tmpSize == tmpHash->used);//test for empty map
    hash_map_put(tmpHash, "key1", 44);
    tmpSize = hash_map_size(tmpHash);
    ASSERT_TRUE(tmpSize == tmpHash->used);//test for nonempty map
    hash_map_dtor(tmpHash);
}

TEST(HashMap, Capacity) {
    hash_map* tmpHash = hash_map_ctor();
    size_t tmpSize = hash_map_capacity(tmpHash);
    ASSERT_TRUE(tmpSize == tmpHash->allocated);//test for empty map
    hash_map_put(tmpHash, "key1", 44);
    tmpSize = hash_map_capacity(tmpHash);
    ASSERT_TRUE(tmpSize == tmpHash->allocated);//test for nonempty map
    hash_map_dtor(tmpHash);
}

TEST(HashMap, Contains) {
    hash_map* tmpHash = hash_map_ctor();
    bool val = hash_map_contains(tmpHash, "key1");//test for empty map
    ASSERT_TRUE(!val);
    hash_map_put(tmpHash, "key1", 44);
    val = hash_map_contains(tmpHash, "key1");//test for nonempty map
    ASSERT_TRUE(val);
    hash_map_dtor(tmpHash);
}

TEST(HashMap, Get) {
    hash_map* tmpHash = hash_map_ctor();
    int* a = (int*)malloc(sizeof(int));
    hash_map_state_code_t var = hash_map_get(tmpHash, "key1", a);
    ASSERT_TRUE(var == KEY_ERROR); //test for empty map
    hash_map_put(tmpHash, "key1", 44);
    var = hash_map_get(tmpHash, "key1", a);
    ASSERT_TRUE(var == OK); //test for nonempty map
    free(a);
    hash_map_dtor(tmpHash);
}

TEST(HashMap, Pop) {
    hash_map* tmpHash = hash_map_ctor();
    int* a = (int*)malloc(sizeof(int));
    hash_map_state_code_t var = hash_map_pop(tmpHash, "key1", a);
    ASSERT_TRUE(var == KEY_ERROR);//test for empty map
    hash_map_put(tmpHash, "key1", 44);
    var = hash_map_pop(tmpHash, "key1", a);
    ASSERT_TRUE(var == OK);//test for nonempty map
    free(a);
    hash_map_dtor(tmpHash);
}

TEST(HashMap, Remove) {
    hash_map* tmpHash = hash_map_ctor();
    hash_map_state_code_t var = hash_map_remove(tmpHash, "key1");
    ASSERT_TRUE(var == KEY_ERROR);//test for empty map
    hash_map_put(tmpHash, "key1", 44);
    var = hash_map_remove(tmpHash, "key1");
    ASSERT_TRUE(var == OK);//test for nonempty map
    hash_map_dtor(tmpHash);
}

/*** Konec souboru white_box_tests.cpp ***/
