#include<iostream>
#include<sstream>
#include "sosJSON.h"

int main(int argc, char** argv)
{
    std::stringstream output;
    sos::SerializeJSON serializer = sos::SerializeJSON();
    sos::Object root = sos::Object();

    root.set("username", sos::String("pksunkara"));
    root.set("age", sos::Number(25));
    root.set("height", sos::Number(1.75));

    sos::Array tags = sos::Array();

    tags.push(sos::String("cricket"));
    tags.push(sos::String("computer"));

    root.set("tags", tags);

    sos::Object social = sos::Object();

    social.set("facebook", sos::Boolean(true));
    social.set("linkedin", sos::Boolean(false));
    social.set("dribble", sos::Null());

    root.set("contact", social);

    serializer.process(root, output);
    std::cout << output.rdbuf() << std::endl;
}
