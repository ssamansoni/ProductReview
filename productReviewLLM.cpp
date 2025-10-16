#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>   // For _popen and _pclose
#include <array>    // For a fixed-size buffer
#include "json.hpp"
using json = nlohmann::json;

using namespace std;
//API key
string api_key = "YOUR_GROQ_API_KEY";

string getLLMresponse(string product,string prompt){
    
    prompt = "These are the reviews and ratings by customer for product " + product + " Summarize all reviews " + prompt;
    string command = "curl -s -X POST https://api.groq.com/openai/v1/chat/completions "
                          "-H \"Content-Type: application/json\" "
                          "-H \"Authorization: Bearer " + api_key + "\" "
                          "-d \"{\\\"model\\\": \\\"moonshotai/kimi-k2-instruct-0905\\\", "
                          "\\\"messages\\\": [{\\\"role\\\": \\\"user\\\", \\\"content\\\": \\\"" + prompt + "\\\"}]}\"";

    string result;
    FILE* pipe = _popen(command.c_str(), "r"); // "r" means read mode

    if (!pipe) {
        std::cerr << "Couldn't start command." << std::endl;
        return "no reponse";
    }

    array<char, 256> buffer;
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    _pclose(pipe);
               json data = json::parse(result);

               std::string text = data["choices"][0]["message"]["content"];
                bool bold = false;
               string content;
               for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '*' && i + 1 < text.size() && text[i + 1] == '*') {
            bold = !bold;
            if (bold)
                content+="";   // turn bold ON
            else
                content+="";   // turn bold OFF
            ++i; // skip next '*'
        } else {
            content+=text[i];
        }
    }
return content;
}

struct ProductReview {
    int review_id;
    string product_id;
    string text;
    int rating;
};

map<string,string> reviews;
string getSummary(string product){
     return getLLMresponse(product,reviews[product]);
}

int main() {
    
    ifstream file("reviews.json");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file reviews.json" << std::endl;
        return 1; // Indicate an error
    }
    json reviews_data;
    try {
        file >> reviews_data;
    } catch (json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return 1; // Indicate an error
    }

    

    for(const auto &review:reviews_data){
        string product_id=review["product_id"];
        string text=review["text"];
        int rating=review["rating"];
                 
        if(reviews.find(product_id)==reviews.end()){
             reviews[product_id]="";
        }
        reviews[product_id]+=text + " " + to_string(rating) + " " ;
    }
    
     vector<string> v;
     for(auto x:reviews){
     v.push_back(x.first);
     }
     
     while(true){
     cout<<"Select the product by serial id "<<endl;
     for(int i=0;i<v.size();i++){
         cout<<i+1<<" "<<v[i]<<endl;
        }
       int id;
       cin>>id;
       
       if(id>v.size()){
        cout<<"Invalid input"<<endl;continue;       
       }
       
       id--;
       string product=v[id];
       cout<<getSummary(product)<<endl;
       if(true)break;
      }
       
    return 0;
}