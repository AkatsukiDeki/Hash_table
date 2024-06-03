#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <random>

template<typename Key, typename Value, template<typename...> class Container = std::list>
class HashTable {
    struct Pair {
        enum class Status { EMPTY, OCCUPIED, DELETED };
        Key _key;
        Value _value;
        Status _status;

        Pair() : _key(), _value(), _status(Status::EMPTY) {}
        Pair(const Key& key, const Value& value) : _key(key), _value(value), _status(Status::OCCUPIED) {}
    };

    std::vector<Pair> _data;
    size_t _size;

    size_t hash(const Key& key) const {
        return key % _data.size();
    }

    void grow() {
        std::vector<Pair> new_data;
        new_data.resize(_data.size() * 1.7);
        _size = 0;
        std::swap(new_data, _data);
        for (auto& pair : _data) {
            if (pair._status == Pair::Status::OCCUPIED) {
                insert(pair._key, pair._value);
            }
        }
    }

public:
    // Конструктор пустой хэш-таблицы заданного размера
    HashTable(const size_t size) {
        if (size == 0)
            throw std::invalid_argument("Size = 0");
        _size = 0;
        _data.resize(size, Pair());
    }

    // Конструктор, заполняющий хэш-таблицу случайными значениями
    HashTable(const size_t size, std::mt19937& rng) {
        if (size == 0)
            throw std::invalid_argument("Size = 0");
        _size = 0;
        _data.resize(size, Pair());
        std::uniform_int_distribution<Key> key_dist;
        std::uniform_int_distribution<Value> value_dist;
        for (size_t i = 0; i < size; ++i) {
            insert(key_dist(rng), value_dist(rng));
        }
    }

    // Конструктор копирования
    HashTable(const HashTable& other) {
        _data = other._data;
        _size = other._size;
    }

    // Деструктор
    ~HashTable() = default;

    // Оператор присваивания
    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            _data = other._data;
            _size = other._size;
        }
        return *this;
    }

    // Печать содержимого
    void print() const {
        for (const auto& pair : _data) {
            if (pair._status == Pair::Status::OCCUPIED) {
                std::cout << "Key: " << pair._key << ", Value: " << pair._value << std::endl;
            }
        }
    }

    void insert(const Key& key, const Value& value) {
        double load_factor = _size / (_data.size() + 0.0);
        if (load_factor >= 0.7) grow();

        size_t index = hash(key);
        size_t originalIndex = index;

        while (_data[index]._status == Pair::Status::OCCUPIED || _data[index]._status == Pair::Status::DELETED) {
            if (_data[index]._key == key) {
                _data[index]._value = value;
                return;
            }
            index = (index + 1) % _data.size();
            if (index == originalIndex) throw std::runtime_error("Hash table is full");
        }

        _data[index]._key = key;
        _data[index]._value = value;
        _data[index]._status = Pair::Status::OCCUPIED;
        ++_size;
    }

    void insert_or_assign(const Key& key, const Value& value) {
        Value* ptr = search(key);
        if (ptr) {
            *ptr = value;
        }
        else {
            insert(key, value);
        }
    }

    bool contains(const Value& value) const {
        for (const auto& pair : _data) {
            if (pair._status == Pair::Status::OCCUPIED && pair._value == value) {
                return true;
            }
        }
        return false;
    }

    Value* search(const Key& key) {
        size_t index = hash(key);
        size_t originalIndex = index;

        while (_data[index]._status != Pair::Status::EMPTY) {
            if (_data[index]._status == Pair::Status::OCCUPIED && _data[index]._key == key) {
                return &_data[index]._value;
            }
            index = (index + 1) % _data.size();
            if (index == originalIndex) return nullptr;
        }

        return nullptr;
    }

    bool erase(const Key& key) {
        size_t index = hash(key);
        size_t originalIndex = index;

        while (_data[index]._status != Pair::Status::EMPTY) {
            if (_data[index]._status == Pair::Status::OCCUPIED && _data[index]._key == key) {
                _data[index]._status = Pair::Status::DELETED;
                --_size;
                return true;
            }
            index = (index + 1) % _data.size();
            if (index == originalIndex) return false;
        }

        return false;
    }

    int count(const Key& key) {
        int count = 0;
        size_t index = hash(key);
        size_t originalIndex = index;

        while (_data[index]._status != Pair::Status::EMPTY) {
            if (_data[index]._status == Pair::Status::OCCUPIED && _data[index]._key == key) {
                ++count;
            }
            index = (index + 1) % _data.size();
            if (index == originalIndex) break;
        }

        return count;
    }

    double load_factor() const {
        return static_cast<double>(_size) / _data.size();
    }
    size_t size() const {
        return _size;
    }
};

#endif // HASHTABLE_H
