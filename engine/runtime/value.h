#pragma once

#include <string>
#include <variant>
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <utility>

namespace w9::runtime
{

    enum class ValueType
    {
        UNDEFINED,
        NULL_TYPE,
        BOOLEAN,
        NUMBER,
        STRING,
        OBJECT
    };

    class JSObject;

    // تمثيل القيمة الديناميكية لجافاسكريبت داخل C++
    class JSValue
    {
    public:
        std::variant<
            std::monostate,           // UNDEFINED
            std::nullptr_t,           // NULL_TYPE
            bool,                     // BOOLEAN
            double,                   // NUMBER
            std::string,              // STRING
            std::shared_ptr<JSObject> // OBJECT (سيتم ربطه بالـ GC لاحقاً)
            >
            as;

        JSValue() : as(std::monostate{}) {}
        JSValue(std::nullptr_t) : as(nullptr) {}
        JSValue(bool value) : as(value) {}
        JSValue(double value) : as(value) {}
        JSValue(std::string value) : as(std::move(value)) {}
        JSValue(std::shared_ptr<JSObject> value) : as(std::move(value)) {}

        ValueType type() const
        {
            return static_cast<ValueType>(as.index());
        }

        bool is_number() const { return type() == ValueType::NUMBER; }
        bool is_string() const { return type() == ValueType::STRING; }
        bool is_object() const { return type() == ValueType::OBJECT; }

        double as_number() const { return std::get<double>(as); }
        const std::string &as_string() const { return std::get<std::string>(as); }
        std::shared_ptr<JSObject> as_object() const { return std::get<std::shared_ptr<JSObject>>(as); }

        std::string to_string() const
        {
            switch (type())
            {
            case ValueType::UNDEFINED:
                return "undefined";
            case ValueType::NULL_TYPE:
                return "null";
            case ValueType::BOOLEAN:
                return std::get<bool>(as) ? "true" : "false";
            case ValueType::NUMBER:
                return std::to_string(std::get<double>(as));
            case ValueType::STRING:
                return std::get<std::string>(as);
            case ValueType::OBJECT:
                return "[object Object]";
            }
            return "unknown";
        }
    };

    // تمثيل الكائنات (Objects) والخصائص التابعة لها
    class JSObject
    {
    public:
        std::unordered_map<std::string, JSValue> properties;

        void set(const std::string &name, JSValue value)
        {
            properties[name] = std::move(value);
        }

        JSValue get(const std::string &name) const
        {
            auto it = properties.find(name);
            if (it != properties.end())
            {
                return it->second;
            }
            return JSValue(); // يُرجع undefined إذا لم تكن الخاصية موجودة
        }
    };

} // namespace w9::runtime