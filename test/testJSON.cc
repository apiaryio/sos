#include<iostream>
#include<sstream>
#include "sosJSON.h"
#include "test.h"

int main(int argc, char** argv)
{
    std::stringstream output;
    sos::SerializeJSON serializer = sos::SerializeJSON();
    sos::Object root = sos::Object();

    build(root);

    serializer.process(root, output);
    std::cout << output.rdbuf() << std::endl;
}
