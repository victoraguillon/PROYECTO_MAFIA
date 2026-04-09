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

void MafiaTree::print_alive_lineage(TreeNode* node, int level){
    if (!node) return;
    if (!node->is_dead){
        for (int i = 0; i < level; i++) cout << "  ";
        cout << "-" << node->name << " " << node->last_name 
        << (node->is_boss ? " [JEFE ACTUAL]" : "")
             << (node->in_jail ? " [EN PRISION]" : "") << endl;
    }

    print_alive_lineage(node->left, level + 1);
    print_alive_lineage(node->right, level + 1);
}

void MafiaTree::load_from_csv(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    CustomList nodes_list;
   while (getline(file, line)) {
        stringstream ss(line);
        string token;
        TreeNode* new_node = new TreeNode();
        getline(ss, token, ','); new_node->id = stoi(token);
        getline(ss, new_node->name, ',');
        getline(ss, new_node->last_name, ',');
        getline(ss, token, ','); new_node->gender = token[0];
        getline(ss, token, ','); new_node->age = stoi(token);
        getline(ss, token, ','); new_node->id_boss = stoi(token);
        getline(ss, token, ','); new_node->is_dead = stoi(token);
        getline(ss, token, ','); new_node->in_jail = stoi(token);
        getline(ss, token, ','); new_node->was_boss = stoi(token);
        getline(ss, token, ','); new_node->is_boss = stoi(token);

        nodes_list.push_back(new_node);
    }
    file.close();

    ListNode* current = nodes_list.head;
    while (current != nullptr) {
        TreeNode* node = current->tree_node;
        if (node->id_boss == 0) {
            root = node;
        } else {
            ListNode* search = nodes_list.head;
            TreeNode* boss_node = nullptr;
            while (search != nullptr) {
                if (search->tree_node->id == node->id_boss) {
                    boss_node = search->tree_node;
                    break;
                }
                search = search->next;
            }

            if (boss_node) {
                node->parent = boss_node;
                if (!boss_node->left) boss_node->left = node;
                else if (!boss_node->right) boss_node->right = node;
                else cout << "Alerta: Jefe " << boss_node->id << " ya tiene 2 sucesores." << endl;
            }
        }
        current = current->next;
    }
}

void MafiaTree::show_alive_succession() {
    cout << "\n--- Linea de Sucesion Actual (Solo Vivos) ---" << endl;
    print_alive_lineage(root, 0);
    cout << "---------------------------------------------\n";
}

TreeNode* MafiaTree::get_current_boss() {
    return find_boss_recursive(root);
}

TreeNode* MafiaTree::find_boss_recursive(TreeNode* node) {
    if (!node) return nullptr;
    if (node->is_boss) return node;
    TreeNode* left_res = find_boss_recursive(node->left);
    if (left_res) return left_res;
    return find_boss_recursive(node->right);
}

void MafiaTree::check_and_update_boss() {
    TreeNode* boss = get_current_boss();
    if (!boss) {
        cout << "No hay jefe actual asignado." << endl;
        return;
    }

    if (boss->is_dead  boss->in_jail  boss->age > 70) {
        cout << "El jefe actual (" << boss->name << ") ha muerto, ido a prision o pasado de los 70 anos. Iniciando sucesion..." << endl;
        
        boss->is_boss = false;
        boss->was_boss = true;

        TreeNode* new_boss = get_next_boss(boss, false);
        
        if (!new_boss) {
            cout << "No hay sucesores libres vivos. Buscando sucesor en prision..." << endl;
            new_boss = get_next_boss(boss, true);
        }

        if (new_boss) {
            new_boss->is_boss = true;
            cout << "NUEVO JEFE ASIGNADO: " << new_boss->name << " " << new_boss->last_name << endl;
        } else {
            cout << "CRITICO: No se encontraron candidatos vivos para la sucesion." << endl;
        }
    } else {
        cout << "El jefe actual (" << boss->name << ") se encuentra bien y en el cargo." << endl;
    }
}
