#include "pricing.hpp"

PriceT parse_fixed8(const std::string& s) {
    // Parse a fixed-8-decimal string to an exact integer without going via double:
    // "76162.18000000" -> 7616218000000. Going through a double loses the last unit
    // on values like 76162.18 and 8.20, which creates duplicate price levels.

    const std::size_t dot = s.find('.');
    
    std::string whole;
    std::string frac;

    if (dot == std::string::npos){
        //if there is no decimal point, the whole part is the entire string and the fractional part is "0"
        whole = s;
        frac = "0";
    }
    else{
        whole = s.substr(0, dot); //get the whole part of the string
        frac = s.substr(dot + 1); //get the fractional part of the string
    }

    frac.resize(8, '0'); //pad the fractional part with zeros to 8 digits

    return std::stoll(whole + frac); //concatenate the whole and fractional parts and convert to integer 

}

