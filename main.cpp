#include <gmpxx.h>
#include <iostream>
#include <stdexcept>

std::string getFormattedFloat(const mpf_class &value)
{
    mp_exp_t exponent;
    std::string str = value.get_str(exponent);
    if (value == 0.0) {
        return "0";
    } else if (exponent < 0) {
        return "0." + std::string((unsigned long) -exponent, '0') + str;
    } else if (exponent == 0) {
        return "0." + str;
    } else {
        long int length_diff = exponent - str.length();
        if (length_diff > 0) {
            return str + std::string((unsigned long) length_diff, '0');
        } else if (length_diff < 0) {
            return str.insert(str.length() + length_diff, ".");
        } else {
            return str;
        }
    }
}

int main(int argc, char *argv[])
{
    int d;

    if (argc < 2) {
        d = 9999;
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

    std::cout << getFormattedFloat(mean_value) << std::endl;

    return 0;
}