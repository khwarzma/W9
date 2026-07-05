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

#include "../ast/ast.h"
#include <memory>
#include <string_view>

namespace w9::jit {

// واجهة مصغرة لمحاكاة ربط LLVM وتوليد كود الآلة (JIT Engine)
class JITCompiler {
public:
    JITCompiler() : is_llvm_initialized_(false) {
        initialize_llvm_backend();
    }
    
    ~JITCompiler() = default;

    // دالة فحص ما إذا كان التعبير أو الدالة تعتبر "Hot" وتستحق الترجمة إلى Native Code
    bool should_compile(size_t execution_count) const {
        return execution_count >= 10; // حد افتراضي: إذا تكرر الكود 10 مرات نقوم بترجمته فوراً
    }

    // دالة توليد كود الآلة الأصلي من الـ AST
    void compile_to_native(ast::Program* program);
    
    // دالة تنفيذ كود الآلة الذي تم توليده وحفظه في الذاكرة القابلة للتنفيذ (Executable Memory)
    double execute_native_block();

private:
    bool is_llvm_initialized_;
    void initialize_llvm_backend();
};

} // namespace w9::jit
