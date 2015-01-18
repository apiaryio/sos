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

    sos::Array interests = sos::Array();
    sos::Array computer = sos::Array();

    computer.push(sos::String("algorithms"));
	computer.push(sos::String("programming"));

    interests.push(sos::String("cricket"));
    interests.push(computer);

    root.set("interests", interests);

    sos::Object social = sos::Object();

    social.set("facebook", sos::Boolean(true));
    social.set("linkedin", sos::Boolean(false));
    social.set("dribble", sos::Null());

    sos::Object github = sos::Object();

    github.set("username", sos::String("pksunkara"));

    sos::Array orgs = sos::Array();

    sos::Object apiary = sos::Object();
    sos::Object flatiron = sos::Object();

    apiary.set("id", sos::String("apiaryio"));
    apiary.set("members", sos::Number(20));

    flatiron.set("id", sos::String("flatiron"));
    flatiron.set("members", sos::Number(10));

    orgs.push(apiary);
    orgs.push(flatiron);

    github.set("orgs", orgs);
    social.set("github", github);
    root.set("contact", social);

    serializer.process(root, output);
    std::cout << output.rdbuf() << std::endl;
}
