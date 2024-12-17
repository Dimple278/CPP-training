#include <iostream>
#include <cstring>

enum class LetType {
    Char,
    Int,
    Double
};

class Let {
public:
    // Constructor for string
    Let(const char* str) : type(LetType::Char) {
        m_c = nullptr;
        if (str) {
            m_c = new char[std::strlen(str) + 1];
            std::strcpy(m_c, str);
        }
    }

    // Constructor for integer
    Let(int value) : type(LetType::Int) {
        m_i = value;
    }

    // Constructor for double
    Let(double value) : type(LetType::Double) {
        m_d = value;
    }

    // Copy constructor
    Let(const Let& other) : type(other.type) {
        switch (type) {
            case LetType::Char:
                m_c = other.m_c ? new char[std::strlen(other.m_c) + 1] : nullptr;
                if (m_c) std::strcpy(m_c, other.m_c);
                break;
            case LetType::Int:
                m_i = other.m_i;
                break;
            case LetType::Double:
                m_d = other.m_d;
                break;
        }
    }

    // Move constructor
    Let(Let&& other) noexcept : type(other.type) {
        switch (type) {
            case LetType::Char:
                m_c = other.m_c;
                other.m_c = nullptr;
                break;
            case LetType::Int:
                m_i = other.m_i;
                break;
            case LetType::Double:
                m_d = other.m_d;
                break;
        }
    }

    // Destructor
    ~Let() {
        cleanup();
    }

    // Assignment operator
    Let& operator=(const Let& other) {
        if (this != &other) {
            cleanup();
            type = other.type;
            switch (type) {
                case LetType::Char:
                    m_c = other.m_c ? new char[std::strlen(other.m_c) + 1] : nullptr;
                    if (m_c) std::strcpy(m_c, other.m_c);
                    break;
                case LetType::Int:
                    m_i = other.m_i;
                    break;
                case LetType::Double:
                    m_d = other.m_d;
                    break;
            }
        }
        return *this;
    }

    // Move assignment operator
    Let& operator=(Let&& other) noexcept {
        if (this != &other) {
            cleanup();
            type = other.type;
            switch (type) {
                case LetType::Char:
                    m_c = other.m_c;
                    other.m_c = nullptr;
                    break;
                case LetType::Int:
                    m_i = other.m_i;
                    break;
                case LetType::Double:
                    m_d = other.m_d;
                    break;
            }
        }
        return *this;
    }

    // Overloaded operators
    Let& operator+(int num) {
        if (type == LetType::Int) {
            m_i += num;
        }
        return *this;
    }

    Let& operator+(double num) {
        if (type == LetType::Double) {
            m_d += num;
        }
        return *this;
    }

    Let& operator+(const char* newStr) {
        if (type == LetType::Char && newStr) {
            size_t newLength = std::strlen(m_c) + std::strlen(newStr) + 1;
            char* temp = new char[newLength];
            std::strcpy(temp, m_c);
            std::strcat(temp, newStr);

            delete[] m_c;
            m_c = temp;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Let& let) {
        switch (let.type) {
            case LetType::Int:
                os << let.m_i;
                break;
            case LetType::Double:
                os << let.m_d;
                break;
            case LetType::Char:
                os << (let.m_c ? let.m_c : "");
                break;
        }
        return os;
    }

private:
    LetType type;
    union {
        char* m_c;
        int m_i;
        double m_d;
    };

    void cleanup() {
        if (type == LetType::Char && m_c) {
            delete[] m_c;
            m_c = nullptr;
        }
    }
};

int main() {
    Let a(1234);
    Let d(35.5);
    Let s("hello");

    a = a + 5;
    d = d + 5.5;
    s = s + " world";

    std::cout << "Integer: " << a << std::endl;
    std::cout << "Double: " << d << std::endl;
    std::cout << "String: " << s << std::endl;

    return 0;
}
