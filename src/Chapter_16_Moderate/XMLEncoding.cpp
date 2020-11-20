#include <iostream>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, std::string> code_map = {{"family", "1"}, {"person", "2"}, {"firstName", "3"}, {"lastName", "4"}, {"state", "5"}};

class Attribute {
    public:
        Attribute(std::string tag, std::string val) : value(val) {
            _tag_code = code_map[tag];
        }
        std::string get_tag_code() {
            return _tag_code;
        }
        std::string value;
    private:
        std::string _tag_code;
};

class Element {
    public:
        Element(std::string name, std::string val = "") : value(val) {
            _name_code = code_map[name];
        }
        std::string get_name_code() {
            return _name_code;
        }
        std::vector<Attribute> attributes;
        std::string value;
        std::vector<Element> children;
    private:
        std::string _name_code;
};

void encode(std::string value, std::string& code) {
    code += value + " ";
}

void encode(Attribute attribute, std::string& code) {
    encode(attribute.get_tag_code(), code);
    encode(attribute.value, code);
}

void encode(Element root, std::string& code) {
    encode(root.get_name_code(), code);
    for(Attribute a : root.attributes) {
        encode(a, code);
    }
    encode("0", code);
    if(root.value != "") {
        encode(root.value, code);
    } else {
        for(Element child : root.children) {
            encode(child, code);
        }
    }
    encode("0", code);
}

/**
 * XML Encoding: Since XML is very verbose, you are given a way of encoding it where each tag gets
 * mapped to a pre-defined integer value. The language/grammar is as follows:
 * Element -> Tag Attributes END Children END
 * Attribute -> Tag Value
 * END -> 0
 * Tag -> some predefined mapping to int
 * Value -> string value
 * For example, the following XML might be converted into the compressed string below (assuming a 
 * mapping of family -> 1, person -> 2, firstName -> 3, lastName -> 4, state -> 5).
 * <family lastName="McDowell" state="CA">
 *      <person firstName="Gayle">Some Message</person>
 * </family>
 * Becomes:
 * 1 4 McDowell 5 CA 0 2 3 Gayle 0 Some Message 0 0
 * Write code to print the encoded version of an XML element (passed in Element and Attribute
 * objects).
 */
int main() {
    Element root("family");
    root.attributes.push_back(Attribute("lastName", "McDowell"));
    root.attributes.push_back(Attribute("state", "CA"));

    Element child("person", "Some Message");
    child.attributes.push_back(Attribute("firstName", "Gayle"));

    root.children.push_back(child);

    std::string code = "";
    encode(root, code);
    std::cout << code << '\n';
}