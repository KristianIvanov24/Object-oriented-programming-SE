Какво ще отпечата следния фрагмент, ако файлът "input.txt" съдържа:
```
123 abv prakt
```


```c++
int main() 
{
	std::ifstream ifs("input.txt");

	if (!ifs.is_open())
		return 1;

	int a = 0;
	char buffer[1024];

	ifs.seekg(1, std::ios::cur);
	ifs >> a;
	std::cout << a << std::endl;
	std::cout << ifs.tellg() << std::endl;

	ifs.clear();

	ifs.getline(buffer, 1024, 'b');
	std::cout << buffer << std::endl;
	std::cout << ifs.tellg() << std::endl;
	std::cout << (char)ifs.get() << std::endl;

	ifs.get(buffer, 1024, 'c');
	std::cout << buffer << std::endl;
	std::cout << ifs.tellg() << std::endl;

	ifs.clear();
	std::cout << ifs.tellg() << std::endl;

	ifs.close();

	return 0;
}
```
