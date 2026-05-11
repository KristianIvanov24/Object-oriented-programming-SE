#include <functional>
#include <memory>
#include <vector>

template <typename T>
class Repository
{
protected:
    std::vector<std::unique_ptr<T>> data;

public:
    Repository() = default;
    virtual ~Repository() = default;

    void add(std::unique_ptr<T> item);
    void addAll(std::vector<std::unique_ptr<T>> items);

    std::vector<const T*> getAll() const;
    size_t size() const;
    bool isEmpty() const;
    bool contains(std::function<bool(const T&)> pred) const;
    const T* findWhere(std::function<bool(const T&)> pred) const;
    std::vector<const T*>
    findAllWhere(std::function<bool(const T&)> pred) const;

    bool update(size_t index, std::unique_ptr<T> item);
    bool updateWhere(
        std::function<bool(const T&)> pred, std::function<void(T&)> transform);

    void clear();
    bool remove(size_t index);
    bool removeWhere(std::function<bool(const T&)> pred);
};

template <typename T>
void Repository<T>::add(std::unique_ptr<T> item)
{
    data.push_back(std::move(item));
}

template <typename T>
void Repository<T>::addAll(std::vector<std::unique_ptr<T>> items)
{
    for (auto& item : items)
    {
        data.push_back(std::move(item));
    }
}

template <typename T>
std::vector<const T*> Repository<T>::getAll() const
{
    std::vector<const T*> result;
    for (auto& item : data)
    {
        result.push_back(item.get());
    }
    return result;
}

template <typename T>
size_t Repository<T>::size() const
{
    return data.size();
}

template <typename T>
bool Repository<T>::isEmpty() const
{
    return data.size() == 0;
}

// template <typename T>
// template <typename Pred>
// bool Repository<T>::contains(Pred pred) const
// {
//     for (const auto& item : data)
//     {
//         const T& constItem = *item;
//         if (pred(constItem))
//         {
//             return true;
//         }
//     }
//     return false;
// }

template <typename T>
bool Repository<T>::contains(std::function<bool(const T&)> pred) const
{
    for (const auto& item : data)
    {
        if (pred(*item))
        {
            return true;
        }
    }
    return false;
}

template <typename T>
const T* Repository<T>::findWhere(std::function<bool(const T&)> pred) const
{
    for (const auto& item : data)
    {
        if (pred(*item))
        {
            return item.get();
        }
    }
    return nullptr;
}

template <typename T>
std::vector<const T*>
Repository<T>::findAllWhere(std::function<bool(const T&)> pred) const
{
    std::vector<const T*> result;
    for (const auto& item : data)
    {
        if (pred(*item))
        {
            result.push_back(item.get());
        }
    }
    return result;
}

template <typename T>
bool Repository<T>::update(size_t index, std::unique_ptr<T> item)
{
    if (index >= data.size())
    {
        return false;
    }

    data[index] = std::move(item);
    return true;
}

template <typename T>
bool Repository<T>::updateWhere(
    std::function<bool(const T&)> pred, std::function<void(T&)> transform)
{
    bool hasTransformed = false;
    for (auto& item : data)
    {
        if (pred(*item))
        {
            transform(*item);
            hasTransformed = true;
        }
    }
    return hasTransformed;
}

template <typename T>
void Repository<T>::clear()
{
    data.clear();
}

template <typename T>
bool Repository<T>::remove(size_t index)
{
    if (index >= data.size())
    {
        return false;
    }
    data.erase(data.begin() + index);
    return true;
}

template <typename T>
bool Repository<T>::removeWhere(std::function<bool(const T&)> pred)
{
    size_t removed = std::erase_if(
        data, [&](const std::unique_ptr<T>& uptr) { return pred(*uptr); });

    return removed > 0;
}
