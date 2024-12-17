#include <iostream>
#include <cstring>

enum class DataType {
    Integer,
    String,
    Boolean,
    Double
};

class Variant {
public:
    Variant(int value) : intValue(value), type(DataType::Integer) {}
    Variant(bool value) : boolValue(value), type(DataType::Boolean) {}
    Variant(double value) : doubleValue(value), type(DataType::Double) {}

    Variant(const char* value) : type(DataType::String) {
        strValue = new char[std::strlen(value) + 1];
        std::strcpy(strValue, value);
    }

    Variant(const Variant& other) {
        type = other.type;
        intValue = other.intValue;
        boolValue = other.boolValue;
        doubleValue = other.doubleValue;

        if (type == DataType::String && other.strValue) {
            strValue = new char[std::strlen(other.strValue) + 1];
            std::strcpy(strValue, other.strValue);
        }
    }

    ~Variant() {
        if (type == DataType::String) {
            delete[] strValue;
        }
    }

    DataType getType() const { return type; }
    int getIntValue() const { return intValue; }
    bool getBoolValue() const { return boolValue; }
    double getDoubleValue() const { return doubleValue; }
    const char* getStrValue() const { return strValue; }

private:
    int intValue = 0;
    bool boolValue = false;
    double doubleValue = 0.0;
    char* strValue = nullptr;
    DataType type;
};

class Node {
public:
    explicit Node(const Variant& value) : data(value), next(nullptr) {}

    Variant data;
    Node* next;
};

class VariantList {
public:
    ~VariantList() {
        clear();
    }

    void add(const Variant& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const VariantList& list);

private:
    Node* head = nullptr;

    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current->next;
            delete current;
            current = temp;
        }
        head = nullptr;
    }
};

std::ostream& operator<<(std::ostream& os, const VariantList& list) {
    Node* current = list.head;
    while (current != nullptr) {
        const Variant& var = current->data;
        switch (var.getType()) {
            case DataType::Integer:
                os << "[" << var.getIntValue() << "]";
                break;
            case DataType::Boolean:
                os << "[" << (var.getBoolValue() ? "true" : "false") << "]";
                break;
            case DataType::Double:
                os << "[" << var.getDoubleValue() << "]";
                break;
            case DataType::String:
                os << "[" << var.getStrValue() << "]";
                break;
        }
        if (current->next != nullptr) {
            os << " => ";
        }
        current = current->next;
    }
    return os;
}

int main() {
    VariantList list;
    list.add(42);
    list.add("World");
    list.add(true);
    list.add(3.14);

    std::cout << list << std::endl;
    return 0;
}
