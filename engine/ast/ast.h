#pragma once

#include <memory>
#include <vector>
#include <string>
#include <string_view>

namespace w9::ast
{

    // الفئة الأساسية لكل عقد الشجرة
    class ASTNode
    {
    public:
        virtual ~ASTNode() = default;
        virtual std::string to_string() const = 0; // للمساعدة في تتبع الأخطاء وفحص المخرجات
    };

    // الفئة الأساسية للتعبيرات التي تُرجع قيمة (مثل: x + 5)
    class Expression : public ASTNode
    {
    };

    // الفئة الأساسية للعبارات التنفيذية التي لا تُرجع قيمة مباشرة (مثل: let x = 10;)
    class Statement : public ASTNode
    {
    };

    // عقدة البرنامج الرئيسي (تتكون من مجموعة من العبارات)
    class Program : public ASTNode
    {
    public:
        std::vector<std::unique_ptr<Statement>> statements;

        std::string to_string() const override
        {
            std::string result;
            for (const auto &stmt : statements)
            {
                result += stmt->to_string() + "\n";
            }
            return result;
        }
    };

    // عبارة الإعلان عن المتغيرات (Variable Declaration: let / const)
    class VariableDeclaration : public Statement
    {
    public:
        std::string_view identifier;
        std::unique_ptr<Expression> initializer;
        bool is_const;

        std::string to_string() const override
        {
            return (is_const ? "const " : "let ") + std::string(identifier) +
                   (initializer ? " = " + initializer->to_string() : "") + ";";
        }
    };

    // تعبير المعاملات الثنائية (Binary Expression: +, -, *, /)
    class BinaryExpression : public Expression
    {
    public:
        std::unique_ptr<Expression> left;
        std::string_view op;
        std::unique_ptr<Expression> right;

        std::string to_string() const override
        {
            return "(" + left->to_string() + " " + std::string(op) + " " + right->to_string() + ")";
        }
    };

    // تعبير المتغيرات المعرفة مسبقاً (Identifier Expression)
    class IdentifierLiteral : public Expression
    {
    public:
        std::string_view value;

        std::string to_string() const override
        {
            return std::string(value);
        }
    };

    // تعبير القيم الرقمية الأصيلة (Numeric Literal)
    class NumericLiteral : public Expression
    {
    public:
        std::string_view value; // نحتفظ بها كـ string_view لتمريرها للـ Runtime لاحقاً

        std::string to_string() const override
        {
            return std::string(value);
        }
    };
    // عبارة تعريف الدالة: function name(params) { body }
    class FunctionDeclaration : public Statement {
    public:
        std::string_view name;
        std::vector<std::string_view> parameters;
        std::vector<std::unique_ptr<Statement>> body;

        std::string to_string() const override {
            std::string result = "function " + std::string(name) + "(";
            for (size_t i = 0; i < parameters.size(); ++i) {
                result += std::string(parameters[i]) + (i < parameters.size() - 1 ? ", " : "");
            }
            result += ") {\n";
            for (const auto& stmt : body) {
                result += "  " + stmt->to_string() + "\n";
            }
            result += "}";
            return result;
        }
    };

    // تعبير استدعاء الدالة: name(arguments)
    class CallExpression : public Expression {
    public:
        std::unique_ptr<Expression> callee; // غالباً IdentifierLiteral باسم الدالة
        std::vector<std::unique_ptr<Expression>> arguments;

        std::string to_string() const override {
            std::string result = callee->to_string() + "(";
            for (size_t i = 0; i < arguments.size(); ++i) {
                result += arguments[i]->to_string() + (i < arguments.size() - 1 ? ", " : "");
            }
            result += ")";
            return result;
        }
    };

} // namespace w9::ast
