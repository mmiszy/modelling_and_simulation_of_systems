#include <gmpxx.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

using precision = int;

std::string round(const std::string &str, const precision &decimals)
{
    if (str.length() <= decimals) {
        return str;
    }
    std::string ret(str);
    int next_decimal = str[decimals] - '0';
    if (next_decimal >= 5) {
        ret.replace((unsigned long) decimals - 1, 1, 1, (char) (str[decimals - 1] + 1));
    }

    return ret.substr(0, (unsigned long) decimals);
}

std::string getFormattedFloat(const mpf_class &value, const precision &d)
{
    mp_exp_t exponent;
    std::string str = value.get_str(exponent);
    bool isNegative = (str[0] == '-');

    if (value == 0.0) {
        return "0";
    } else if (exponent < 0) {
        if (d <= -exponent) {
            return "0";
        }

        precision decimals = (precision) (d + exponent);

        if (decimals < 0) {
            decimals = 0;
        }
        str = str.substr((unsigned long) isNegative);

        return (isNegative ? std::string("-") : std::string("")) + "0." + std::string((unsigned long) -exponent, '0') +
               round(str, decimals);
    } else if (exponent == 0) {
        str = str.substr((unsigned long) isNegative);
        return (isNegative ? std::string("-") : std::string("")) + "0." + round(str, d);
    } else {
        long int length_diff = exponent - str.length();
        if (length_diff > 0) {
            return str + std::string((unsigned long) length_diff, '0');
        } else if (length_diff < 0) {
            precision decimals = (precision) (str.length() + length_diff + d + isNegative);
            precision decimal_point_position = (precision) (str.length() + length_diff + isNegative);

            str = round(str, decimals);

            if (decimal_point_position == str.length()) {
                return str;
            }

            return str.insert((unsigned long) decimal_point_position, ".");
        } else {
            return str;
        }
    }
}

int main(int argc, char *argv[])
{
    precision d;

    if (argc < 2) {
        d = 7;
    } else {
        d = std::stoi(argv[1]);
    }

    int n = 0;
    mpf_set_default_prec(640);

    mpz_class input;
    std::string input_str;

    mpz_class accumulator;
    accumulator = "0";

    while (std::cin >> input_str) {
        input = input_str.c_str();
        accumulator += input;
        ++n;
    }

    mpf_class mean_value;
    mean_value = mpf_class(accumulator) / n;

    std::cout << getFormattedFloat(mean_value, d) << std::endl;

    return 0;
}