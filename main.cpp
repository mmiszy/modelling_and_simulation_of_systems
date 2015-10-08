#include <gmpxx.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

using integer = int;

std::string round(const std::string &str, const integer &decimals)
{
    if (str.length() <= decimals)
    {
        return str;
    }
    std::string ret(str);
    int next_decimal = str[decimals] - '0';
    if (next_decimal >= 5)
    {
        ret.replace((unsigned long) decimals - 1, 1, 1, (char) (str[decimals - 1] + 1));
    }

    return ret.substr(0, (unsigned long) decimals);
}

std::string getFormattedFloat(const mpf_class &value, const integer &d)
{
    mp_exp_t exponent;
    std::string str = value.get_str(exponent);
    bool isNegative = (str[0] == '-');

    if (value == 0.0)
    {
        return "0";
    }
    else if (exponent < 0)
    {
        if (d <= -exponent)
        {
            return "0";
        }

        integer decimals = (integer) (d + exponent);

        if (decimals < 0)
        {
            decimals = 0;
        }
        str = str.substr((unsigned long) isNegative);

        return (isNegative ? std::string("-") : std::string("")) + "0." + std::string((unsigned long) -exponent, '0') +
               round(str, decimals);
    }
    else if (exponent == 0)
    {
        str = str.substr((unsigned long) isNegative);
        return (isNegative ? std::string("-") : std::string("")) + "0." + round(str, d);
    }
    else
    {
        long int length_diff = exponent - str.length();
        if (length_diff > 0)
        {
            return str + std::string((unsigned long) length_diff, '0');
        }
        else if (length_diff < 0)
        {
            integer decimals = (integer) (str.length() + length_diff + d + isNegative);
            integer decimal_point_position = (integer) (str.length() + length_diff + isNegative);

            str = round(str, decimals);

            if (decimal_point_position == str.length())
            {
                return str;
            }

            return str.insert((unsigned long) decimal_point_position, ".");
        }
        else
        {
            return str;
        }
    }
}

int main(int argc, char *argv[])
{
    integer d;

    if (argc < 2)
    {
        d = 7;
    }
    else
    {
        d = std::stoi(argv[1]);
    }

    integer n = 0;
    mpf_set_default_prec(640);

    mpz_class input;
    std::string input_str;

    mpz_class sum_of_terms;
    sum_of_terms = "0";

    mpz_class sum_of_squared_terms;
    sum_of_squared_terms = "0";

    integer longest_period = 1;
    integer current_period = 1;
    integer current_period_index = 1;
    integer longest_period_index = 1;

    mpz_class last_value;
    bool has_started = false;

    while (std::cin >> input_str)
    {
        input = input_str.c_str();
        sum_of_terms += input;
        sum_of_squared_terms += input * input;
        ++n;

        if (has_started)
        {
            if (last_value == input)
            {
                ++current_period;
            }
            else
            {
                current_period_index = n;
                current_period = 1;
            }
        }
        else
        {
            has_started = true;
        }
        last_value = input;
        if (current_period > longest_period)
        {
            longest_period = current_period;
            longest_period_index = current_period_index;
        }
    }

    mpf_class sum_of_terms_float = mpf_class(sum_of_terms);
    mpf_class sum_of_squared_terms_float = mpf_class(sum_of_squared_terms);

    mpf_class mean_value;
    mean_value = sum_of_terms_float / n;

    mpf_class variance;
    variance = sum_of_squared_terms_float / n - mean_value * mean_value;

    std::cout << getFormattedFloat(mean_value, d) << std::endl;
    std::cout << getFormattedFloat(variance, d) << std::endl;
    std::cout << longest_period_index << std::endl;

    return 0;
}