//
//  main.cpp
//  test-libsos
//
//  Created by Pavan Kumar Sunkara on 1/21/15.
//  Copyright (c) 2015 Apiary Inc. All rights reserved.
//

#define CATCH_CONFIG_MAIN /// < Let catch generate the main()

#include "catch.hpp"
#include "sosJSON.h"
#include "sosYAML.h"
#include "test.h"

TEST_CASE("Serailize JSON", "[sos][json]")
{
    std::stringstream output;
    std::string expected = \
    "{\n"\
    "  \"username\": \"pksunkara\",\n"\
    "  \"age\": 25,\n"\
    "  \"height\": 1.75,\n"\
    "  \"interests\": [\n"\
    "    \"cricket\",\n"\
    "    [\n"\
    "      \"algorithms\",\n"\
    "      \"programming\"\n"\
    "    ]\n"\
    "  ],\n"\
    "  \"contact\": {\n"\
    "    \"facebook\": true,\n"\
    "    \"linkedin\": false,\n"\
    "    \"dribble\": null,\n"\
    "    \"github\": {\n"\
    "      \"username\": \"pksunkara\",\n"\
    "      \"orgs\": [\n"\
    "        {\n"\
    "          \"id\": \"apiaryio\",\n"\
    "          \"members\": 20\n"\
    "        },\n"\
    "        {\n"\
    "          \"id\": \"flatiron\",\n"\
    "          \"members\": 10\n"\
    "        }\n"\
    "      ]\n"\
    "    }\n"\
    "  }\n"\
    "}";

    sos::SerializeJSON serializer = sos::SerializeJSON();
    sos::Object root = sos::Object();

    build(root);
    serializer.process(root, output);

    REQUIRE(output.str() == expected);
}

TEST_CASE("Serialize YAML", "[sos][yaml]")
{
    std::stringstream output;
    std::string expected = \
    "username: \"pksunkara\"\n"\
    "age: 25\n"\
    "height: 1.75\n"\
    "interests:\n"\
    "  - \"cricket\"\n"\
    "  -\n"\
    "    - \"algorithms\"\n"\
    "    - \"programming\"\n"\
    "contact:\n"\
    "  facebook: true\n"\
    "  linkedin: false\n"\
    "  dribble: null\n"\
    "  github:\n"\
    "    username: \"pksunkara\"\n"\
    "    orgs:\n"\
    "      -\n"\
    "        id: \"apiaryio\"\n"\
    "        members: 20\n"\
    "      -\n"\
    "        id: \"flatiron\"\n"\
    "        members: 10";

    sos::SerializeYAML serializer = sos::SerializeYAML();
    sos::Object root = sos::Object();

    build(root);
    serializer.process(root, output);

    REQUIRE(output.str() == expected);
}
