#include <iostream>
#include <string>
#include <vector>

using namespace std;

// "Інтерфейс" (віртуальний клас) для операцій з адресою
class IAddressable {
public:
    virtual ~IAddressable() = default;
    virtual void updateAddress(const string& street, const string& city, const string& country) = 0;
};

// Клас Адреса, що реалізує IAddressable
class Address : public IAddressable {
private:
    string street;
    string city;
    string country;

public:
    Address() = default;
    
    Address(const string& street, const string& city, const string& country)
        : street(street), city(city), country(country) {}

    void updateAddress(const string& street, const string& city, const string& country) override {
        this->street = street;
        this->city = city;
        this->country = country;
    }

    string getFullAddress() const {
        return street + ", " + city + ", " + country;
    }

    friend ostream& operator<<(ostream& os, const Address& address) {
        os << "Адреса: " << address.getFullAddress();
        return os;
    }
};

// Клас Особа з використанням Делегування
class Person {
private:
    string name;
    string phone;
    Address* address;

public:
    Person(const string& name, const string& phone)
        : name(name), phone(phone) {
        address = new Address();
    }

    ~Person() {
        delete address;
    }

    // Делегування: Передача операцій з адресою об'єкту адреси
    void setAddress(const string& street, const string& city, const string& country) {
        address->updateAddress(street, city, country);
    }

    string getAddress() const {
        return address->getFullAddress();
    }

    void setName(const string& name) { this->name = name; }
    void setPhone(const string& phone) { this->phone = phone; }
    
    string getName() const { return name; }
    string getPhone() const { return phone; }

    friend ostream& operator<<(ostream& os, const Person& person) {
        os << "=== Інформація про особу ===\n";
        os << "Ім'я: " << person.name << "\n";
        os << "Телефон: " << person.phone << "\n";
        os << *person.address << "\n";
        return os;
    }
};

// Клас Записна книжка
class Notebook {
private:
    vector<Person*> entries;
    string notebookName;

public:
    Notebook(const string& name) : notebookName(name) {}

    ~Notebook() {
        for (Person* person : entries) {
            delete person;
        }
    }

    void addEntry(Person* person) {
        entries.push_back(person);
    }

    friend ostream& operator<<(ostream& os, const Notebook& notebook) {
        os << "\n======== " << notebook.notebookName << " ========\n";
        for (size_t i = 0; i < notebook.entries.size(); ++i) {
            os << *notebook.entries[i] << "\n";
        }
        return os;
    }
};

int main() {
    cout << "Варіант №5: Записна книжка з інформацією про особу та адресу" << endl;
    cout << "Використання Делегування та Інтерфейсу\n" << endl;

    // Створення записної книжки
    Notebook notebook("Моя адресна книга");

    // Створення осіб та додавання їх до записної книжки
    Person* person1 = new Person("Іван Петренко", "+380-67-123-4567");
    person1->setAddress("вул. Хрещатик, 123", "Київ", "Україна");
    
    Person* person2 = new Person("Марія Коваленко", "+380-95-987-6543");
    person2->setAddress("пр. Свободи, 456", "Львів", "Україна");

    // Додавання записів до записної книжки
    notebook.addEntry(person1);
    notebook.addEntry(person2);

    // Відображення записної книжки
    cout << notebook << endl;

    // Зміна адреси через делегування
    cout << "Змінюємо адресу Івана Петренка...\n" << endl;
    person1->setAddress("вул. Нова, 999", "Одеса", "Україна");
    
    // Відображення записної книжки після зміни адреси
    cout << notebook << endl;

    return 0;
}