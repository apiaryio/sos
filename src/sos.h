//
//  sos.h
//  sos
//
//  Created by Pavan Kumar Sunkara on 10/01/15.
//  Copyright (c) 2015 Apiary Inc. All rights reserved.
//

#ifndef SOS_H
#define SOS_H

#include <string>
#include <vector>
#include <map>
#include <ostream>
#include <algorithm>

namespace sos {

    /** Forward Declaration */
    class Base;

    /** Key-value pairs (object) */
    typedef std::map<std::string, Base> KeyValues;

    /** List of keys for object (for deterministic output) */
    typedef std::vector<std::string> Keys;

    /** Array of values */
    typedef std::vector<Base> Bases;

    /** Value base structure */
    class Base {
    public:

        /** Enum for Type of the value */
        enum Type {
            NullType = 1, // Null
            StringType,   // A string
            NumberType,   // A number
            BooleanType,  // A boolean value
            ArrayType,    // An array
            ObjectType,   // An object
            UndefinedType = 0
        };

        /** Type of the value */
        Type type;

        /** String value */
        std::string string;

        /** Number value */
        double number;

        /** Boolean value */
        bool boolean;

        /** Object value */
        KeyValues& object();
        const KeyValues& object() const;

        Keys keys;

        /** Array value */
        Bases& array();
        const Bases& array() const;

        /** Constructor */
        Base(Type type_ = UndefinedType, std::string string_ = "", double number_ = 0, bool boolean_ = false);

        /** Copy constructor */
        Base(const Base& rhs);

        /** Assignment operator */
        Base& operator=(const Base& rhs);

        /** Destructor */
        ~Base() {};

    private:
        std::auto_ptr<KeyValues> m_object;
        std::auto_ptr<Bases> m_array;
    };

    class Null : public Base {
    public:

        /** Constructor */
        Null();
    };

    class String : public Base {
    public:

        /** Constructor */
        String(std::string string_ = "");
    };

    class Number : public Base {
    public:

        /** Constructor */
        Number(double number_ = 0);
    };

    class Boolean : public Base {
    public:

        /** Constructor */
        Boolean(bool boolean_ = false);
    };

    class Array : public Base {
    public:

        /** Constructor */
        Array();

        void push(const Base& value);
        void set(const size_t index, const Base& value);
    };

    class Object : public Base {
    public:

        /** Constructor */
        Object();

        void set(const std::string& key, const Base& value);
    };

    struct Serialize {

        /** Constructor */
        Serialize();

        /** Process */
        void process(const Base& node, std::ostream& os, int level = 0);

        virtual void null(std::ostream& os) = 0;
        virtual void string(const std::string& node, std::ostream& os) = 0;
        virtual void number(double node, std::ostream& os) = 0;
        virtual void boolean(bool node, std::ostream& os) = 0;
        virtual void array(const Base& node, std::ostream& os, int level) = 0;
        virtual void object(const Base& node, std::ostream& os, int level) = 0;

        virtual void indent(int level, std::ostream& os) = 0;
    };

    /**
     *  \brief  Escape every double quote in input string.
     *  \param  input   A string to escape its double quotes.
     *  \return A new string with double quotes escaped.
     */
    std::string escapeDoubleQuotes(const std::string& input);

    /**
     *  \brief  Escape new lines in input string.
     *  \param  input   A string to escape its new lines.
     *  \return A new string with lines escaped.
     *
     *  This function replaces all occurences of "\n" with "\\n".
     */
    std::string escapeNewlines(const std::string& input);
}

#endif
