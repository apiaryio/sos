//
//  sosYAML.h
//  sos
//
//  Created by Pavan Kumar Sunkara on 12/01/15.
//  Copyright (c) 2015 Apiary Inc. All rights reserved.
//

#ifndef SOS_YAML_H
#define SOS_YAML_H

#include "sos.h"

namespace sos {

    struct SerializeYAML : public Serialize {

        void indent(int level, std::ostream& os) {

            for (int i = 0; i < level; ++i) {
                os << "  ";
            }
        }

        void null(std::ostream& os) {
        }

        void string(const std::string& node, std::ostream& os) {
        }

        void number(double node, std::ostream& os) {
        }

        void boolean(bool node, std::ostream& os) {
        }

        void array(const Base& node, std::ostream& os, int level) {

            os << "[";

            if (!node.array().empty()) {

                os << "\n";
                size_t i = 0;

                for (Bases::const_iterator it = node.array().begin(); it != node.array().end(); ++i, ++it) {

                    if (i > 0 && i < node.array().size()) {
                        os << ",\n";
                    }

                    indent(level + 1, os);
                    process(*it, os, level + 1);
                }
            }

            os << "]";
        }

        void object(const Base& node, std::ostream& os, int level) {

            os << "{";

            if (!node.object().empty()) {

                os << "\n";
                size_t i = 0;

                for (KeyValues::const_iterator it = node.object().begin(); it != node.object().end(); ++i, ++it) {

                    if (i > 0 && i < node.object().size()) {
                        os << ",\n";
                    }
                    
                    indent(level + 1, os);
                    string(it->first, os);
                    
                    os << ": ";
                    process(it->second, os, level + 1);
                }
            }
            
            os << "}";
        }
    };
}

#endif
