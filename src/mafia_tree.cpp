#include "mafia_tree.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// IMPLEMENTACIÓN DE ESTRUCTURAS

TreeNode::TreeNode():left(nullptr), right(nullptr), parent(nullptr) {}  

ListNode::ListNode(TreeNode* node): tree_node(node), next(nullptr) {}

CustomList::CustomList(): head(nullptr) {}

CustomList::~CustomList() {
    ListNode* current = head;
    while (current!= nullptr) {
       ListNode* next_node = current->next;
        delete current;
        current = next_node;
    }
}

void CustomList::push_back(TreeNode* node) {
    ListNode* new_node = new ListNode(node);
    if (!head) {
        head = new_node;
        return;
    }
    ListNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
 }

 // IMPLEMENTACIÓN DEL ÁRBOL DE MAFIA 

MafiaTree::MafiaTree(): root(nullptr) {}

TreeNode* MafiaTree::search_node(TreeNode* current, int id){
    if (!current) return nullptr;
    if (current->id == id) return current;

    TreeNode* found_left = search_node(current->left, id);
    if (found_left) return found_left;
    return search_node(current->right, id);

}

TreeNode* MafiaTree::find_valid_candidate_in_subtree(TreeNode* current, bool allow_jailed){
    if (!current) return nullptr;
  
    bool is_valid = !current->is_dead && (allow_jailed || !current->in_jail);
    if (is_valid) return current;

    TreeNode* left_cand = find_valid_candidate_in_subtree(current->left, allow_jailed);
    if (left_cand) return left_cand;
    return find_valid_candidate_in_subtree(current->right, allow_jailed);
}

TreeNode* MafiaTree::get_next_boss(TreeNode* dead_boss, bool allow_jailed){
    if (!dead_boss) return nullptr;

    TreeNode* cand = find_valid_candidate_in_subtree(dead_boss->left, allow_jailed);
    if (cand) return cand;
    cand = find_valid_candidate_in_subtree(dead_boss->right, allow_jailed);
    if (cand) return cand;

    TreeNode* current_parent = dead_boss->parent;
    TreeNode* current_node = dead_boss;

    while (current_parent != nullptr) {
        TreeNode* sibling = (current_parent->left == current_node) ? current_parent->right : current_parent->left;

        if (sibling) {
            cand = find_valid_candidate_in_subtree(sibling->left, allow_jailed);
            if (cand) return cand;
            cand = find_valid_candidate_in_subtree(sibling->right, allow_jailed);
            if (cand) return cand;

            bool sibling_valid = !sibling->is_dead && (allow_jailed || !sibling->in_jail);
            if (sibling_valid) return sibling;
        }
        current_node = current_parent;
        current_parent = current_parent->parent;
    }
    return nullptr;
}

