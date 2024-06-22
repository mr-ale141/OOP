#include <cassert>
#include <concepts>
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <tuple>

// Написать коллекцию

class X {
public:
    X() {
        G();
    }
    ~X()
    {
        G();
    }

    void G()
    {
        F();
    }

    virtual void F() {
        std::cout << "X" << std::endl;
    }
};

class Y :public X
{
public:
    void F() override {
        std::cout << "Y" << std::endl;
    }

};

void FFF()
{
    Y y;

}

struct Person
{
    unsigned id = 0;
    std::string name;
    std::string surname;
    int age = 0;

    std::string* operator->()
    {
        return &((*this).name);
    }
};

static bool operator<(const Person& left, const Person& right)
{
    return left.id < right.id;
}

std::ostream& operator<<(std::ostream& out, const Person& p)
{
    return out << "{ id:" << p.id << ", name: " << p.name
        << ", surname: " << p.surname << ", age: " << p.age << "}";
}

class PersonRepository final
{
public:
    // Добавляет человека в коллекцию
    void AddPerson(Person p)
    {
        if (m_persons.contains(p.id))
            throw std::invalid_argument("ERROR! Inserting with a repeated key!");

        unsigned newId = p.id;

        m_persons.insert(
            std::make_pair(
                p.id,
                std::move(p)
            )
        );

        std::string_view newName(m_persons.find(newId)->second.name);
        std::string_view newSurname(m_persons.find(newId)->second.surname);

        bool isNameInserted = false;
        try
        {
            InsertName(newName, newId);
            isNameInserted = true;
            InsertSurname(newSurname, newId);
        }
        catch (...)
        {
            if (isNameInserted)
                DeleteName(newName, newId);
            m_persons.erase(newId);
            throw;
        }
    }

    // Удаляет человека из коллекции с идентификатором, равным id
    void RemovePerson(unsigned id)
    {
        if (m_persons.contains(id) == false)
            return;

        auto itForDel = m_persons.find(id);

        DeleteName(itForDel->second.name, id);
        DeleteSurname(itForDel->second.surname, id);

        m_persons.erase(itForDel);
    }

    const Person* FindPersonById(unsigned id) const
    {
        if (m_persons.contains(id))
            return &m_persons.at(id);

        // Возвращает человека с указанным id либо nullptr, если такого человека нет.
        // Поиск должен выполняться за время, не хуже чем O(log N)
        return nullptr;
    }

    // Callback - это любой тип, который можно использовать как функцию,
    // принимающую Person по константной ссылке.
    template <std::invocable<const Person&> Callback>
    void EnumeratePeople(Callback&& callback)
    {
        for (auto it = m_persons.begin(); it != m_persons.end(); ++it)
            callback(it->second);
    }

    // Ищет всех людей с указанным именем и для каждого из них вызывает callback
    template <std::invocable<const Person&> Callback>
    void FindAllPeopleWithName(std::string_view name, Callback&& callback) const
    {
        auto& set = m_personsNames.find(name)->second;

        for (auto i : set)
        {
            callback(m_persons.find(i)->second);
        }
    }

    // Ищет всех людей с указанным именем и для каждого из них вызывает callback
    template <std::invocable<const Person&> Callback>
    void FindAllPeopleWithSurname(std::string_view surname, Callback&& callback) const
    {
        auto& set = m_personsSurnames.find(surname)->second;

        for (auto i : set)
        {
            callback(m_persons.find(i)->second);
        }
    }
private:
    void DeleteName(std::string_view name, unsigned id)
    {
        auto it = m_personsNames.find(name);
        assert(it != m_personsNames.end());
        it->second.erase(it->second.find(id));
    }

    void DeleteSurname(std::string_view surname, unsigned id)
    {
        auto it = m_personsSurnames.find(surname);
        assert(it != m_personsSurnames.end());
        it->second.erase(it->second.find(id));
    }

    void InsertName(std::string_view name, unsigned id)
    {
        if (m_personsNames.contains(name))
        {
            auto it = m_personsNames.find(name);
            it->second.insert(id);
            return;
        }

        bool isNameInserted = false;
        try
        {
            m_personsNames[name];
            isNameInserted = true;
            m_personsNames.find(name)->second.insert(id);
        }
        catch (...)
        {
            if (isNameInserted)
                m_personsNames.erase(name);
            throw;
        }
    }

    void InsertSurname(std::string_view surname, unsigned id)
    {
        if (m_personsSurnames.contains(surname))
        {
            auto it = m_personsSurnames.find(surname);
            it->second.insert(id);
            return;
        }

        bool isNameInserted = false;
        try
        {
            m_personsSurnames[surname];
            isNameInserted = true;
            m_personsSurnames.find(surname)->second.insert(id);
        }
        catch (...)
        {
            if (isNameInserted)
                m_personsSurnames.erase(surname);
            throw;
        }
    }

    std::unordered_map<unsigned, Person> m_persons;
    std::unordered_map<std::string_view, std::set<unsigned>> m_personsNames;
    std::unordered_map<std::string_view, std::set<unsigned>> m_personsSurnames;
};

int main()
{
    PersonRepository people;
    people.AddPerson({ .id = 1, .name = "Lev", .surname = "Tolstoy", .age = 18 });
    people.AddPerson({ .id = 2, .name = "Alexey", .surname = "Tolstoy", .age = 25 });
    people.AddPerson({ .id = 3, .name = "Fedor", .surname = "Dostoevsky", .age = 40 });
    people.AddPerson({ .id = 4, .name = "Boris", .surname = "Akunin", .age = 35 });
    people.AddPerson({ .id = 5, .name = "Vladimir", .surname = "Vysotsky", .age = 35 });
    people.AddPerson({ .id = 6, .name = "Vladimir", .surname = "Nabokov", .age = 47 });

    const auto p = people.FindPersonById(5);
    assert(p != nullptr && p->surname == "Vysotsky");

    const auto p2 = people.FindPersonById(42);
    assert(p2 == nullptr);

    std::cout << "_______ Print ALL _______" << std::endl;
    people.EnumeratePeople([](const Person& person) {
        std::cout << person << std::endl;
        });

    std::cout << "_______ Print 'Vladimir' _______" << std::endl;
    people.FindAllPeopleWithName("Vladimir", [](const Person& person) {
        std::cout << person << std::endl;
        });

    std::cout << "_______ Print 'Tolstoy' _______" << std::endl;
    people.FindAllPeopleWithSurname("Tolstoy", [](const Person& person) {
        std::cout << person << std::endl;
        });

    std::cout << "_______ DELETE #4 _______" << std::endl;
    people.RemovePerson(4);

    people.EnumeratePeople([](const Person& person) {
        std::cout << person << std::endl;
        });

    Person person{ 5, "Name", "Surname", 23 };
    std::cout << person->size() << std::endl;

    Person* const pp = &person;
    auto ppp = pp + 1;

    std::set<Person> setPerson;
    setPerson.insert({ .id = 1, .name = "Lev", .surname = "Tolstoy", .age = 18 });
    setPerson.insert({ .id = 2, .name = "Alexey", .surname = "Tolstoy", .age = 25 });
    for (auto& i : setPerson)
        std::cout << i << std::endl;
}

