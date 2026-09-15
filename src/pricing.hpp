#pragma once //only include this file once per translation unit
#include <string> 
#include "types.hpp" //for PriceT and QtyT

PriceT parse_fixed8(const std::string& s);
// Types only — kept free of function declarations so any header can include it cheaply.


