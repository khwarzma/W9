/*
 * Copyright 2026 Khwarzma Company
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <vector>
#include <cstdint>
#include "../runtime/value.h" // استخدام الملف وفقاً لهيكليتك الحالية
#include "../ast/ast.h"

namespace w9::vm {

// الأكواد التشغيلية للمحرك (Opcodes)
enum Opcode : uint8_t {
    OP_CONSTANT,  // تحميل قيمة ثابتة إلى المكدس
    OP_ADD,       // جمع أعلى قيمتين في المكدس
    OP_SUB,       // طرح أعلى قيمتين في المكدس
    OP_MUL,       // ضرب أعلى قيمتين في المكدس
    OP_DIV,       // قسمة أعلى قيمتين في المكدس
    OP_DEFINE_GLOBAL, // تعريف متغير عام
    OP_GET_GLOBAL,    // جلب متغير عام
    OP_SET_GLOBAL,    // تعديل متغير عام
    OP_CALL,          // استدعاء دالة وإنشاء إطار استدعاء جديد
    OP_RETURN     // إنهاء التنفيذ
};

// حاوية لتخزين تعليمات البايت والثوابت (Bytecode Chunk)
struct Chunk {
    std::vector<uint8_t> code;
    std::vector<runtime::JSValue> constants;

    void write(uint8_t byte) {
        code.push_back(byte);
    }

    size_t add_constant(runtime::JSValue value) {
        constants.push_back(value);
        return constants.size() - 1;
    }
};

// فئة الـ Bytecode Compiler لتحويل الـ AST إلى تعليمات خطية
class BytecodeCompiler {
public:
    BytecodeCompiler() = default;
    Chunk compile(ast::Program* program);

private:
    Chunk chunk_;
    void compile_statement(ast::Statement* stmt);
    void compile_expression(ast::Expression* expr);
};

// الآلة الافتراضية المبنية على المكدس (Stack-based VM)
class VM {
public:
    VM() = default;
    void interpret(const Chunk& chunk);

private:
    std::vector<runtime::JSValue> stack_; // مكدس التنفيذ الافتراضي
    
    void push(runtime::JSValue value) { stack_.push_back(value); }
    runtime::JSValue pop() {
        auto val = stack_.back();
        stack_.pop_back();
        return val;
    }
};

} // namespace w9::vm
