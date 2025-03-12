#pragma once
#include <iostream>
#include <iterator>

// Estrutura do nó
template <typename T>
struct Node {
    T dado;
    Node* prox;
    Node(T val) : dado(val), prox(nullptr) {}
};

// Classe da lista encadeada
template <typename T>
class List {
private:
    Node<T>* prox;
    Node<T>* ant;
    size_t size;

public:
    List();
    ~List();

    void push_back(T val);
    void push_front(T val);
    void pop_front();
    void pop_back();
    void clear();
    bool empty() const;
    size_t length() const;
    void print() const;
    T& back();

    // Iteradores
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

    private:
        Node<T>* current;
        Node<T>* prev;
        const List<T>* list;

    public:
        Iterator(Node<T>* node, const List<T>* lst) : current(node), prev(nullptr), list(lst) {}

        reference operator*() { return current->dado; }
        pointer operator->() { return &(current->dado); }

        Iterator& operator++() {
            if (current) {
                prev = current;
                current = current->prox;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }

        friend class List<T>;
    };

    Iterator begin() { return Iterator(prox, this); }
    Iterator end() { return Iterator(nullptr, this); }
    Iterator begin() const { return Iterator(prox, this); }
    Iterator end() const { return Iterator(nullptr, this); }
    Iterator erase(Iterator it);
};

// Implementação dos métodos
template <typename T>
List<T>::List() : prox(nullptr), ant(nullptr), size(0) {}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
void List<T>::push_back(T val) {
    Node<T>* novoNode = new Node<T>(val);
    if (!prox) {
        prox = ant = novoNode;
    } else {
        ant->prox = novoNode;
        ant = novoNode;
    }
    size++;
}

template <typename T>
void List<T>::push_front(T val) {
    Node<T>* novoNode = new Node<T>(val);
    if (!prox) {
        prox = ant = novoNode;
    } else {
        novoNode->prox = prox;
        prox = novoNode;
    }
    size++;
}

template <typename T>
void List<T>::pop_front() {
    if (!prox) return;
    Node<T>* temp = prox;
    prox = prox->prox;
    delete temp;
    size--;
    if (!prox) ant = nullptr;
}

template <typename T>
void List<T>::pop_back() {
    if (!prox) return;
    if (prox == ant) {
        delete prox;
        prox = ant = nullptr;
    } else {
        Node<T>* temp = prox;
        while (temp->prox != ant) {
            temp = temp->prox;
        }
        delete ant;
        ant = temp;
        ant->prox = nullptr;
    }
    size--;
}

template <typename T>
void List<T>::clear() {
    while (prox) {
        pop_front();
    }
}

template <typename T>
bool List<T>::empty() const {
    return size == 0;
}

template <typename T>
size_t List<T>::length() const {
    return size;
}

template <typename T>
void List<T>::print() const {
    Node<T>* temp = prox;
    while (temp) {
        std::cout << temp->dado << " -> ";
        temp = temp->prox;
    }
    std::cout << "null" << std::endl;
}

template <typename T>
T& List<T>::back() {
    if (!ant) throw std::out_of_range("Lista vazia");
    return ant->dado;
}

template <typename T>
typename List<T>::Iterator List<T>::erase(Iterator it) {
    if (!prox || it.current == nullptr) return end();

    Node<T>* toDelete = it.current;
    Node<T>* nextNode = toDelete->prox;

    if (toDelete == prox) {
        pop_front();
        return Iterator(prox, this);
    } else {
        Node<T>* temp = prox;
        while (temp->prox && temp->prox != toDelete) {
            temp = temp->prox;
        }
        if (temp->prox == toDelete) {
            temp->prox = nextNode;
            if (toDelete == ant) {
                ant = temp;
            }
            delete toDelete;
            size--;
        }
    }
    return Iterator(nextNode, this);
}