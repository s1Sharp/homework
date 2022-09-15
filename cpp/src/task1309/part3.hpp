#pragma once

#include <iostream>
#include <complex>
#include <cmath>
#include <limits>
#include <string>

namespace part3 {

// #define MY_MATH
#undef MY_MATH

    template <typename T>
    class QuadEquation
    {
        using complex_t = T;
    public:
        static inline const double mathPrecision = 1e-48;
        enum class EQUATION_STATE {
            ONE_REAL_EQ = 0,
            TWO_REAL_EQ,
            TWO_IMG_EQ,
            INF_EQ,
            NOT_EXISTS_EQ,
        };

    public:
        double m_a, m_b, m_c;
        std::complex<complex_t> m_z1, m_z2;
        EQUATION_STATE isEquationExists;

    public:
        double doubleLn(const double x) {
            if (x < mathPrecision * mathPrecision) {
                return (double)std::numeric_limits<double>::max();
            };
            double z = std::abs((x - 1) / (x + 1));
            double sum = 0.0, m = z;
            size_t iter = 0;
            do
            {
                sum += m;
                m *= z * z / (2 * ++iter + 1);
            } while (m > mathPrecision);

            return (x < 1 ? -2 : 2) * sum;
        }

        //exp(x) = 1 + x + (x^2)/2!+(x^3)/3!....+(x^n)/n!+.....
        double doubleExp(const double x) {
            double exp, tmp;
            size_t n = 1;
            for(exp = 1.0, tmp = 1.0; tmp >= mathPrecision; ++n){
                tmp *= (double)x / n;
                exp += tmp;
            }
            return exp;
        }

        double doubleSqrt(const double d) {
            constexpr double sqrtBase = static_cast<double> (1.0) / 2.0;
    #ifdef MY_MATH
            return doubleExp(sqrtBase * doubleLn(d));
    #else
            return std::exp(sqrtBase * std::log(d));
    #endif
        }

        std::complex<complex_t> complexSqrt(const std::complex<complex_t> &z) {
            double x = z.real() * z.real() + z.imag() * z.imag();
            const double c_module = doubleSqrt(x);
            const double fi = std::atan(z.imag() / z.real());
            return std::complex(c_module * std::cos(fi), c_module * std::sin(fi));
        }

        std::string whatSolve() {
            return std::to_string(m_a) +
                    std::string("*x^2 + ") +
                    std::to_string(m_b) +
                    std::string("*x + ") +
                    std::to_string(m_c) +
                    std::string(" = 0\n");
        }

        std::string whatEq() {
            switch (isEquationExists)
            {
            case EQUATION_STATE::ONE_REAL_EQ:
                return whatSolve() + std::string("one real equation: z1(") +
                        std::to_string(static_cast<double>(m_z1.real())) +
                        std::string(")\n");
                break;
            case EQUATION_STATE::TWO_REAL_EQ:
                return whatSolve() + std::string("two real equations: z1(") +
                        std::to_string(static_cast<double>(m_z1.real())) +
                        std::string(") , z2(") +
                        std::to_string(static_cast<double>(m_z2.real())) +
                        std::string(")\n");
                break;
            case EQUATION_STATE::TWO_IMG_EQ:
                return whatSolve() + std::string("two imagine equations: z1(") +
                    std::to_string(static_cast<double>(m_z1.real())) +
                    std::string(", ") +
                    std::to_string(static_cast<double>(m_z1.imag())) +
                    std::string(" * i) , z2(") +
                    std::to_string(static_cast<double>(m_z2.real())) +
                    std::string(", ") +
                    std::to_string(static_cast<double>(m_z2.imag())) +
                    std::string(" * i)");
                break;
            case EQUATION_STATE::INF_EQ:
                return whatSolve() + std::string("infinity equations\n");
                break;
            case EQUATION_STATE::NOT_EXISTS_EQ:
                return whatSolve() + std::string("equations not exists, \"A\" equal 0\n");
                break;        
            default:
                return std::string("error\n");
                break;
            }
        }
    public:
        QuadEquation(complex_t a, complex_t b, complex_t c) : m_a(a), m_b(b), m_c(c) {

            if (m_a == 0 && m_b == 0 && m_c == 0) {
                isEquationExists = EQUATION_STATE::INF_EQ;
                return;
            }

            if (m_a == 0) {
                isEquationExists = EQUATION_STATE::NOT_EXISTS_EQ;
                return;
            }

            const double D = (m_b * m_b - 4 * m_a * m_c);
            if (D == 0) {
                const double realRoot = (-m_b / (2 * m_a));
                m_z1 = m_z2 = std::complex<complex_t> (realRoot, 0.0);
                isEquationExists = EQUATION_STATE::ONE_REAL_EQ;
                return;
            }
            if (D < 0) {
                const double realRoot1 = -m_b / (2 * m_a);
                const double imgRoot1 = doubleSqrt(std::abs(D)) / (2 * m_a);
                const double realRoot2 = -m_b / (2 * m_a);
                const double imgRoot2 = -doubleSqrt(std::abs(D)) / (2 * m_a);
                m_z1 = std::complex<complex_t>(realRoot1, imgRoot1);
                m_z2 = std::complex<complex_t>(realRoot2, imgRoot2);
                isEquationExists = EQUATION_STATE::TWO_IMG_EQ;
                return;
            }
            if (D > 0) {
                const double realRoot1 = (-m_b + doubleSqrt(D)) / (2 * m_a);
                const double imgRoot1 = 0.0;
                const double realRoot2 = (-m_b - doubleSqrt(D)) / (2 * m_a);
                const double imgRoot2 = 0.0;
                m_z1 = std::complex<complex_t>(realRoot1, imgRoot1);
                m_z2 = std::complex<complex_t>(realRoot2, imgRoot2);
                isEquationExists = EQUATION_STATE::TWO_REAL_EQ;
                return;
            }
        }
    }; 

    void main3() {
        QuadEquation<double> q(1, 2, 3);
        std::cout << q.whatEq();
    }
}