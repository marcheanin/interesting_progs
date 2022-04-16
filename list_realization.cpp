#include <iostream>
#include <set>

using namespace std;

struct Node {                               // структура узлов списка
    int val;
    Node* next;

    Node(int _val) : val(_val), next(nullptr) {}
};

struct List {
    Node* first;
    Node* last;

    List() : first(nullptr), last(nullptr) {} // инициализация списка

    bool is_empty() {                         // проверка на пустоту
        return first == nullptr;
    }

    void push_back(int _val) {                // добавление в конец
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void push_front(int _val){               // добавление элемента в начало
        Node* p = new Node(_val);
        if (is_empty()){
            push_back(_val);
            return;
        }
        p->next = first;
        first = p;
    }

    void remove_first() {                     // удаление первого элемента списка
        if (is_empty()) return;
        Node* p = first;
        first = p->next;
        delete p;
    }

    void remove_last() {                      // удаление последнего элемента
        if (is_empty()) return;
        if (first == last){
            remove_first();
            return;
        }
        Node* p = first;
        while(p->next != last) p = p->next;
        p->next = nullptr;
        delete last;
        last = p;
    }

    bool find(int _val) {                   // поиск элемента в списке
        Node* p = first;
        while (p && p->val != _val) p = p->next;
        return (p && p->val == _val) ? true : false;
    }

    int find_max(){                         // поиск максимального элемента в списке
        Node* p = first;
        int mux = p->val;
        while(p){
            mux = max(mux, p->val);
            p = p->next;
        }
        return mux;
    }

    int find_min(){                         // поиск минимального элемента в списке
        Node* p = first;
        int mun = p->val;
        while(p){
            mun = min(mun, p->val);
            p = p->next;
        }
        return mun;
    }

    int count_positive(){                   // подсчет количества положительных
        Node* p = first;
        int res = 0;
        while(p){
            if (p->val > 0) res++;
            p = p->next;
        }
        return res;
    }

    void remove(int _val){              // удаление элемента по значению (первого)
        if (is_empty()) return;
        if (first->val == _val){
            remove_first();
            return;
        }
        if (last->val == _val){
            remove_last();
            return;
        }
        if (!find(_val)){
            cout << "No element" << endl;
            return;
        }
        Node* slow = first;
        Node* fast = first->next;
        while(fast && fast->val != _val){
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = fast->next;
        delete fast;
    }

    void replace_val(int Old, int New){     // замена всех элементов списка со значением Old на New
        Node* p = first;
        while(p){
            if (p->val == Old){
                p->val = New;
            }
            p = p->next;
        }
    }

    void remove_all(int _val){              // удаление элементов по значению (всех)
        while(find(_val)){
            remove(_val);
        }
    }

    int count_uniq(){                       // количество уникальных элементов
        set <int> res;
        Node* p = first;
        while(p){
            res.insert(p->val);
            p = p->next;
        }
        return res.size();
    }

    void print() {                            //вывод
        if (is_empty()) return;
        Node* p = first;
        while (p) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }

    void delete_all(){                          // удалить весь список
        while(!is_empty()){
            remove_last();
        }
    }
};

bool compare_sets(List a, List b){              // сравнение множеств элементов двух списков
    set <int> res1;
    Node* p = a.first;
    while(p){
        res1.insert(p->val);
        p = p->next;
    }

    set <int> res2;
    p = b.first;
    while(p){
        res2.insert(p->val);
        p = p->next;
    }

    return res1 == res2;
}

int main() {
}
