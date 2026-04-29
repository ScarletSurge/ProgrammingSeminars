#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iomanip>

#include "trie.h"

class polynomial final
{

public:

    struct monomial final
    {

        char const *variables_alphabet = "abcdefghijklmnopqrstuvwxyz";

        double coefficient;
        trie variables_degrees;

    public:

        explicit monomial(
            char const *string_representation) :
            variables_degrees(variables_alphabet)
        {
            // "312.101"
            // "312.101*"
            // "312.101*xy*x^2*abc^7*x"
            // "xy*x^3*abc^7*x^4"
            char const *sr = string_representation;
            char variable_name_buf[9], *vnb = variable_name_buf;
            int variable_degree;

            if (*sr == '\0')
            {
                throw std::invalid_argument("");
            }

            if (isdigit(*sr)) // reading coefficient
            {
                coefficient = 0.0;
                bool dot_met = false;
                double degree_of_10 = 1.0;

                while (*sr != '\0' && *sr != '*')
                {
                    if (*sr == '.')
                    {
                        if (dot_met)
                        {
                            throw std::invalid_argument("");
                        }
                        
                        dot_met = true;
                    }
                    else if (!isdigit(*sr))
                    {
                        throw std::invalid_argument("");
                    }
                    else if (!dot_met)
                    {
                        coefficient = coefficient * 10.0 + *sr - '0';
                    }
                    else
                    {
                        degree_of_10 /= 10;
                        coefficient += (*sr - '0') * degree_of_10;
                    }

                    ++sr;
                }
            }
            else if (islower(*sr))
            {
                coefficient = 1.0;
            }
            else
            {
                throw std::invalid_argument("");
            }

            while (*sr != '\0')
            {
                if (*sr == '*')
                {
                    if (*++sr == '\0')
                    {
                        throw std::invalid_argument("");
                    }
                }

                while (islower(*sr))
                {
                    *vnb++ = *sr++;
                    if (vnb - variable_name_buf == 9)
                    {
                        throw std::invalid_argument("");
                    }
                }
                if (vnb == variable_name_buf)
                {
                    throw std::invalid_argument("");
                }

                *vnb = '\0';
                vnb = variable_name_buf;
                if (*sr == '*')
                {
                    variable_degree = 1;
                }
                else if (*sr == '^')
                {
                    if (!isdigit(*++sr))
                    {
                        throw std::invalid_argument("");
                    }
                    variable_degree = 0;
                    while (*sr != '\0' && *sr != '*')
                    {
                        if (!isdigit(*sr))
                        {
                            throw std::invalid_argument("");
                        }

                        variable_degree = variable_degree * 10 + *sr++ - '0';
                    }
                }
                else if (*sr == '\0')
                {
                    variable_degree = 1;
                }
                else
                {
                    throw std::invalid_argument("");
                }

                try
                {
                    variables_degrees.find(variable_name_buf) += variable_degree;
                }
                catch (std::logic_error const &)
                {
                    variables_degrees.insert(variable_name_buf, variable_degree);
                }
            }
        }

        friend std::ostream &operator<<(
            std::ostream &stream,
            monomial const &obj)
        {
            stream << std::setprecision(4) << obj.coefficient;
            // obj.variables_degrees.
        }

    };

    struct monomial_list_item
    {

        monomial value;
        monomial_list_item *next;

    };

public:

    monomial_list_item *first_monomial;

};

#endif