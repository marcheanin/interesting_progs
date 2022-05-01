#include <iostream>
#include <set>
#include <locale.h>

using namespace std;

struct Node {                               // ��������� ����� ������
    int val;
    Node* next;

    Node(int _val) : val(_val), next(nullptr) {}
};

struct List {
    Node* first;
    Node* last;

    List() : first(nullptr), last(nullptr) {} // ������������� ������

    bool is_empty() {                         // �������� �� �������
        return first == nullptr;
    }

    void push_back(int _val) {                // ���������� � �����
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void push_front(int _val){               // ���������� �������� � ������
        Node* p = new Node(_val);
        if (is_empty()){
            push_back(_val);
            return;
        }
        p->next = first;
        first = p;
    }

    void remove_first() {                     // �������� ������� �������� ������
        if (is_empty()) return;
        Node* p = first;
        first = p->next;
        delete p;
    }

    void remove_last() {                      // �������� ���������� ��������
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

    bool find(int _val) {                   // ����� �������� � ������
        Node* p = first;
        while (p && p->val != _val) p = p->next;
        return (p && p->val == _val) ? true : false;
    }

    int find_max(){                         // ����� ������������� �������� � ������
        Node* p = first;
        int mux = p->val;
        while(p){
            mux = max(mux, p->val);
            p = p->next;
        }
        return mux;
    }

    int find_min(){                         // ����� ������������ �������� � ������
        Node* p = first;
        int mun = p->val;
        while(p){
            mun = min(mun, p->val);
            p = p->next;
        }
        return mun;
    }

    int count_positive(){                   // ������� ���������� �������������
        Node* p = first;
        int res = 0;
        while(p){
            if (p->val > 0) res++;
            p = p->next;
        }
        return res;
    }

    void remove(int _val){              // �������� �������� �� �������� (�������)
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

    void replace_val(int Old, int New){     // ������ ���� ��������� ������ �� ��������� Old �� New
        Node* p = first;
        while(p){
            if (p->val == Old){
                p->val = New;
            }
            p = p->next;
        }
    }

    void remove_all(int _val){              // �������� ��������� �� �������� (����)
        while(find(_val)){
            remove(_val);
        }
    }

    int count_uniq(){                       // ���������� ���������� ���������
        set <int> res;
        Node* p = first;
        while(p){
            res.insert(p->val);
            p = p->next;
        }
        return res.size();
    }

    void print() {                            //�����
        if (is_empty()) return;
        Node* p = first;
        while (p) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }

    void delete_all(){                          // ������� ���� ������
        while(!is_empty()){
            remove_last();
        }
    }
};

bool compare_lists(List a, List b){              // ��������� �������� ��������� ���� �������
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
    List a;
    int s[] = {1, 2, 3, 3, 5, -1, 6, 6, 17};
    for (int i = 0; i < 9; i++){
        a.push_back(s[i]);
    }
    a.push_front(8);
    a.print();
    //a.delete_all();
    //a.print();
    a.remove_first();
    a.print();
    cout << a.find(3) << " " << a.find(20) << endl;
    cout << a.count_positive() << endl;
    cout << a.is_empty() << endl;
    cout << a.find_max() << " " << a.find_min() << endl;
    a.remove(3);
    a.print();
    a.remove_all(6);
    a.print();
    a.replace_val(-1, 7);
    a.print();
    a.delete_all();
    for (int i = 0; i < 9; i++){
        a.push_back(s[i]);
    }
    a.print();
    cout << a.count_uniq() << endl;
    List b;
    for (int i = 0; i < 9; i++){
        b.push_back(s[i]);
    }
    cout << compare_lists(a, b) << endl;
    b.remove_last();
    cout << compare_lists(a, b) << endl;
}
