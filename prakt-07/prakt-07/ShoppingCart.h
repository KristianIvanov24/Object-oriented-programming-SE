#pragma once
#include "Item.h"

class ShoppingCart
{
private:
	Item* items;
	size_t count, capacity;

	void free();
	void copyFrom(const ShoppingCart& other);
	void moveFrom(ShoppingCart&& other) noexcept;
	void resize();
	void swap(size_t i1, size_t i2);
public:
	ShoppingCart();
	ShoppingCart(const ShoppingCart& other);
	ShoppingCart(ShoppingCart&& other) noexcept;
	ShoppingCart& operator=(const ShoppingCart& other);
	ShoppingCart& operator=(ShoppingCart&& other) noexcept;
	~ShoppingCart();

	void addItem(const Item& toAdd);
	void removeItem(const MyString& name);
	int itemsCount() const;
	bool exists(const MyString& name) const;
	bool isEmpty() const;
	double getPriceOf(const MyString& name) const;
	double totalPrice() const;
	void sortByName();
	void saveToBinary(std::ofstream& ofs) const;
	void readFromBinary(std::ifstream& ifs);
};

