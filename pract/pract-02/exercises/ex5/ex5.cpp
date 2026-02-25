#include <iostream>

namespace constants {
    const size_t MAX_COEFF = 20;
}

struct Polynomial {
    int coeff[constants::MAX_COEFF];
	size_t degree;
};

Polynomial initPolynomial(size_t degree, const int* coeffs)
{
    Polynomial p;
    if (degree >= constants::MAX_COEFF || !coeffs) {
        std::cout << "Invalid input!" << std::endl;
        return p;
    }

    p.degree = degree;

    for (int i = 0; i <= degree; i++) {
        p.coeff[i] = coeffs[i];
    }
    return p;
}

double evaluatePolynomial(const Polynomial& p, double x)
{
    double res = 0.0;

    for (int i = 0; i <= p.degree; i++) {
        res += p.coeff[i] * pow(x, i);
    }
    return res;
}

Polynomial addPolynomials(const Polynomial& p1, const Polynomial& p2)
{
    Polynomial res;
    size_t maxDegree = (p1.degree >= p2.degree) ? p1.degree : p2.degree;

    for (int i = 0; i <= maxDegree; i++) {

        int coeff1 = (i <= p1.degree) ? p1.coeff[i] : 0;
        int coeff2 = (i <= p2.degree) ? p2.coeff[i] : 0;

        res.coeff[i] = coeff1 + coeff2;
        if(coeff1 + coeff2 != 0) {
            res.degree = i;
		}
    }
    return res;
}

Polynomial subtractPolynomials(const Polynomial& p1, const Polynomial& p2)
{
    Polynomial res;
    size_t maxDegree = (p1.degree >= p2.degree) ? p1.degree : p2.degree;

    for (int i = 0; i <= maxDegree; i++) {

        int coeff1 = (i <= p1.degree) ? p1.coeff[i] : 0;
        int coeff2 = (i <= p2.degree) ? p2.coeff[i] : 0;

        res.coeff[i] = coeff1 - coeff2;
        if (coeff1 - coeff2 != 0) {
            res.degree = i;
        }
    }
    return res;
}

Polynomial multiplyPolynomials(const Polynomial& p1, const Polynomial& p2)
{
    Polynomial res;
    res.degree = p1.degree + p2.degree;

    if(res.degree >= constants::MAX_COEFF) {
        std::cout << "Polynomial will exceed maximum allowed degree of 20" << std::endl;
        return res;
	}

    for (int i = 0; i <= p1.degree; i++) {
        for (int j = 0; j <= p2.degree; j++) {
            res.coeff[i + j] += p1.coeff[i] * p2.coeff[j];
        }
    }
    return res;
}

void printPolynomial(const Polynomial& p)
{
    bool first = true;
    for (int i = p.degree; i >= 0; i--) {
        if (p.coeff[i] != 0) {
            if (!first && p.coeff[i] > 0) std::cout << " + ";
            if (p.coeff[i] < 0) std::cout << " - ";

            int absVal = std::abs(p.coeff[i]);
            if (absVal != 1 || i == 0) std::cout << absVal;

            std::cout << "x^" << i;
            first = false;
        }
    }
    if (first) std::cout << "0x^0";
    std::cout << std::endl;
}

int main()
{
    int c1[] = { 5, 2, 3 };
    int c2[] = { 1, 4 };

    Polynomial p1 = initPolynomial(2, c1);
    Polynomial p2 = initPolynomial(1, c2);

    std::cout << "P1: "; printPolynomial(p1);
    std::cout << "P2: "; printPolynomial(p2);

    double val = evaluatePolynomial(p1, 2.0);
    std::cout << "\nP1 x=2: " << val << std::endl;

    Polynomial pSum = addPolynomials(p1, p2);
    std::cout << "+: "; printPolynomial(pSum);

    Polynomial pSub = subtractPolynomials(p1, p2);
    std::cout << "-: "; printPolynomial(pSub);

    Polynomial pMul = multiplyPolynomials(p1, p2);
    std::cout << "*: "; printPolynomial(pMul);

    return 0;
}