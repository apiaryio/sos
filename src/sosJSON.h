//
//  sosJSON.h
//  sos
//
//  Created by Pavan Kumar Sunkara on 11/01/15.
//  Copyright (c) 2015 Apiary Inc. All rights reserved.
//

#ifndef SOS_JSON_H
#define SOS_JSON_H

#include "sos.h"

namespace sos {

    struct SerializeJSON : public Serialize {

        virtual void indent(size_t level, std::ostream& os) {

            for (size_t i = 0; i < level; ++i) {
                os << "  ";
            }
        }

        virtual void null(std::ostream& os) {

            os << "null";
        }

        virtual void string(const std::string& value, std::ostream& os) {

            std::string normalized = escapeBackslashes(value);
            normalized = escapeDoubleQuotes(normalized);
            normalized = escapeNewlines(normalized);

            os << "\"" << normalized << "\"";
        }

        virtual void number(double value, std::ostream& os) {

            os << value;
        }

        virtual void boolean(bool value, std::ostream& os) {

            os << (value ? "true" : "false");
        }

        virtual void array(const Base& value, std::ostream& os, size_t level) {

            os << "[";

            if (!value.array().empty()) {

                os << "\n";
                size_t i = 0;

                for (Bases::const_iterator it = value.array().begin(); it != value.array().end(); ++i, ++it) {

                    if (i > 0 && i < value.array().size()) {
                        os << ",\n";
                    }

                    indent(level + 1, os);
                    process(*it, os, level + 1);
                }

                os << "\n";
                indent(level, os);
            }

            os << "]";
        }

        virtual void object(const Base& value, std::ostream& os, size_t level) {

            os << "{";

            if (!value.keys.empty()) {

                os << "\n";
                size_t i = 0;

                for (Keys::const_iterator it = value.keys.begin(); it != value.keys.end(); ++i, ++it) {

                    if (i > 0 && i < value.keys.size()) {
                        os << ",\n";
                    }

                    indent(level + 1, os);
                    string(*it, os);

                    os << ": ";
                    process(value.object().at(*it), os, level + 1);
                }

                os << "\n";
                indent(level, os);
            }

            os << "}";
        }
    };
}

#endif
