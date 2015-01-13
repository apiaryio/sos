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

namespace sos {

    /** Forward Declaration */
    class Base;

    /** Key-value pairs (object) */
    typedef std::map<std::string, Base> KeyValues;

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
}

sos::Base::Base(Base::Type type_, std::string string_, double number_, bool boolean_)
: type(type_), string(string_), number(number_), boolean(boolean_)
{
    m_object.reset(::new KeyValues);
    m_array.reset(::new Bases);
}

sos::Base::Base(const sos::Base& rhs)
{
    this->type = rhs.type;
    this->string = rhs.string;
    this->number = rhs.number;
    this->boolean = rhs.boolean;

    this->m_object.reset(::new KeyValues(*rhs.m_object.get()));
    this->m_array.reset(::new Bases(*rhs.m_array.get()));
}

sos::Base& sos::Base::operator=(const sos::Base &rhs)
{
    this->type = rhs.type;
    this->string = rhs.string;
    this->number = rhs.number;
    this->boolean = rhs.boolean;

    this->m_object.reset(::new KeyValues(*rhs.m_object.get()));
    this->m_array.reset(::new Bases(*rhs.m_array.get()));

    return *this;
}

sos::KeyValues& sos::Base::object()
{
    if (!m_object.get())
        throw "no object key-values set";

    return *m_object;
}

const sos::KeyValues& sos::Base::object() const
{
    if (!m_object.get())
        throw "no object key-values set";

    return *m_object;
}

sos::Bases& sos::Base::array()
{
    if (!m_array.get())
        throw "no array values set";

    return *m_array;
}

const sos::Bases& sos::Base::array() const
{
    if (!m_array.get())
        throw "no array values set";

    return *m_array;
}

sos::Null::Null()
{
    type = NullType;
}

sos::String::String(std::string string_)
{
    type = StringType;
    string = string_;
}

sos::Number::Number(double number_)
{
    type = NumberType;
    number = number_;
}

sos::Boolean::Boolean(bool boolean_)
{
    type = BooleanType;
    boolean = boolean_;
}

sos::Array::Array()
: Base(ArrayType)
{}

void sos::Array::push(const sos::Base& value)
{
    array().push_back(value);
}

void sos::Array::set(const size_t index, const sos::Base& value)
{
    if (array().size() <= index)
        throw "not enough array values set";

    array().at(index) = value;
}

sos::Object::Object()
: Base(ObjectType)
{}

void sos::Object::set(const std::string& key, const sos::Base& value)
{
    object().operator[](key) = value;
}

sos::Serialize::Serialize()
{}

void sos::Serialize::process(const Base& root, std::ostream& os, int level)
{
    sos::Base::Type type = root.type;

    switch (type) {

        case Base::NullType:
            null(os);
            break;

        case Base::StringType:
            string(root.string, os);
            break;

        case Base::NumberType:
            number(root.number, os);
            break;

        case Base::BooleanType:
            boolean(root.boolean, os);
            break;

        case Base::ArrayType:
            array(root, os, level);
            break;

        case Base::ObjectType:
            object(root, os, level);
            break;

        default:
            break;
    }
}

#endif
