#include <nlohmann/json.hpp> //for json parsing 
#include <iostream>
#include "pricing.hpp" //quotes search your project directory first, then system directories
#include <iomanip> //for std::setprecision
#include "types.hpp" //for PriceT and QtyT

using json = nlohmann::json; //alias for nlohmann::json

int main() {
    const std::string raw = R"({"e": "depthUpdate", "E":1789323230114, "s":"BTCUSDT", "U": 100063830821, "u":100063830829, "b":[["76162.18000000","0.00032000"],["69589.81000000","0.00432000"]], "a":[["77500.73000000","0.00000000"],["77500.94000000","0.00000000"],["77500.94000000","0.00000000"]]})";
    const json ev = json::parse(raw);



    std::cout << std::fixed << std::setprecision(8); //set the precision for floating point numbers

    std::cout << "symbol   " << ev["s"].get<std::string>() << "\n";    //get the symbol from the json object
    std::cout << "first id  " << ev["U"].get<std::uint64_t>() << "\n";   //get the first id from the json object
    std::cout << "final id   " << ev["u"].get<std::uint64_t>() << "\n";   //get the final id from the json object 
    std::cout << "bid levels   " << ev["b"].size() << "\n";    //get the number of bid levels from the json object
    std::cout << "ask levels   " << ev["a"].size() << "\n";   //get the number of ask levels from the json object

    std::cout << "\n";


    for (const auto& ask : ev.at("a")) {  //iterate over the asks
        const PriceT ask_price = parse_fixed8(ask[0].get<std::string>());
        const QtyT ask_qty = parse_fixed8(ask[1].get<std::string>());
        if (ask_qty == 0){
            std::cout << "DELETE   " << ask_price << "\n";
        }
        else {
            std::cout << "ASK   " << ask_price << "| Quantity   " << ask_qty << "\n";
        }
    }



    return 0;
}