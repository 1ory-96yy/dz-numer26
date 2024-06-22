#include <iostream>
#include <exception>
#include <string>

namespace MathOperations {

    class MathException : public std::exception {
    public:
        virtual const char* what() const throw() {
            return "Math error occurred";
        }
    };

    class DivideByZeroException : public MathException {
    public:
        const char* what() const throw() {
            return "Attempted to divide by zero";
        }
    };

    class OutOfMemoryException : public std::exception {
    public:
        const char* what() const throw() {
            return "Out of memory";
        }
    };

} 

namespace FileOperations {

    class FileException : public std::exception {
    private:
        std::string message;
    public:
        FileException(const std::string& msg) : message(msg) {}

        const char* what() const throw() {
            return message.c_str();
        }
    };

} 

namespace DataStructures {

    class EmptyListException : public std::exception {
    public:
        const char* what() const throw() {
            return "Attempted to delete from empty list";
        }
    };

    class DoublyLinkedList {
    private:
        struct Node {
            int data;
            Node* prev;
            Node* next;

            Node(int value) : data(value), prev(nullptr), next(nullptr) {}
        };

        Node* head;
        Node* tail;

    public:
        DoublyLinkedList() : head(nullptr), tail(nullptr) {}

        ~DoublyLinkedList() {
            Node* current = head;
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            head = tail = nullptr;
        }

        bool isEmpty() const {
            return head == nullptr;
        }

        void append(int value) {
            Node* newNode = new Node(value);
            if (isEmpty()) {
                head = tail = newNode;
            }
            else {
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
            }
        }

        void deleteNode(int value) {
            if (isEmpty()) {
                throw EmptyListException();
            }

            Node* current = head;
            while (current) {
                if (current->data == value) {
                    if (current->prev) {
                        current->prev->next = current->next;
                    }
                    if (current->next) {
                        current->next->prev = current->prev;
                    }
                    if (current == head) {
                        head = current->next;
                    }
                    if (current == tail) {
                        tail = current->prev;
                    }
                    delete current;
                    return;
                }
                current = current->next;
            }

            throw std::runtime_error("Value not found in the list");
        }

        void printList() const {
            Node* current = head;
            while (current) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    };

}

int main() {
    try {
        DataStructures::DoublyLinkedList dll;

        dll.append(1);
        dll.append(2);
        dll.append(3);

        dll.printList();

        dll.deleteNode(2);
        dll.printList();

        dll.deleteNode(4);
    }
    catch (const DataStructures::EmptyListException& e) {
        std::cerr << "Empty list exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
    }

    return 0;
}
