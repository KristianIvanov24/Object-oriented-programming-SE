#include <iostream>

template < typename U, typename V>
class MyPair
{
private:
	U u;
	V v;
public:
	U& getU() const;
	V& getV() const;

	void setU(const U& u);
	void setV(const V& v);
};

template<typename U, typename V>
inline U& MyPair<U, V>::getU() const
{
	return u;
}

template<typename U, typename V>
inline V& MyPair<U, V>::getV() const
{
	return v;
}

template<typename U, typename V>
inline void MyPair<U, V>::setU(const U& u)
{
	this->u = u;
}

template<typename U, typename V>
inline void MyPair<U, V>::setV(const V& v)
{
	this->v = v;
}

template<typename U, typename V>
bool operator==(const MyPair<U, V>& lhs, const MyPair<U, V>& rhs)
{
	return (lhs.getU() == rhs.getU() && lhs.getV() == rhs.getV());
}

template<typename U, typename V>
bool operator!=(const MyPair<U, V>& lhs, const MyPair<U, V>& rhs)
{
	return !lhs == rhs;
}

template<typename U, typename V>
bool operator<(const MyPair<U, V>& lhs, const MyPair<U, V>& rhs)
{
	return (lhs.getu() < rhs.getU() && lhs.getV() < rhs.getV());
}
