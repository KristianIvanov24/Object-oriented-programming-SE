#include <cstdint>

// нека сме създали Bitset(13) и сме добавили 1, 5, 11, т.е. множеството ни е {1, 5, 11};
// тогава ще имаме два bucket-a и битовете ще изглеждат така:
// data[0] = 00100010 
// data[1] = 00001000

class Bitset {
  public:
    static constexpr unsigned bitsInByte = 8;
    static constexpr unsigned elementsInBucket = sizeof(uint8_t) * bitsInByte;

    Bitset(unsigned n);

    Bitset(const Bitset &);

    Bitset &operator=(const Bitset &);

    ~Bitset();

    unsigned getN() const;

    void add(unsigned);
    void remove(unsigned);
    bool contains(unsigned) const;

    void print() const;

    static Bitset unionSets(const Bitset &, const Bitset &);
    static Bitset intersection(const Bitset &, const Bitset &);

  private:
    unsigned maxN;
    uint8_t *data;
    unsigned bucketsCount;

    void free();
    void copyFrom(const Bitset &);

    unsigned getBucketIndex(unsigned n) const;
    unsigned getBitIndex(unsigned n) const;
};
