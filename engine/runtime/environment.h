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

#include "value.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

namespace w9::runtime {

class Environment {
public:
    // بناء سكوب جديد، مع إمكانية ربطه بالسكوب الأب (Outer/Parent Scope)
    explicit Environment(std::shared_ptr<Environment> outer = nullptr) 
        : outer_(std::move(outer)) {}

    // حجز متغير جديد (let / const)
    void define(const std::string& name, JSValue value, bool is_const = false) {
        if (bindings_.find(name) != bindings_.end()) {
            throw std::runtime_error("Identifier '" + name + "' has already been declared");
        }
        bindings_[name] = {std::move(value), is_const};
    }

    // تعديل قيمة متغير موجود (Assignment) مع تتبع الـ Scope Chain والتحقق من الـ const
    void assign(const std::string& name, JSValue value) {
        auto it = bindings_.find(name);
        if (it != bindings_.end()) {
            if (it->second.is_const) {
                throw std::runtime_error("Assignment to constant variable '" + name + "'");
            }
            it->second.value = std::move(value);
            return;
        }

        if (outer_) {
            outer_->assign(name, std::move(value));
            return;
        }

        throw std::runtime_error("Variable '" + name + "' is not defined");
    }

    // جلب قيمة المتغير
    JSValue lookup(const std::string& name) {
        auto it = bindings_.find(name);
        if (it != bindings_.end()) {
            return it->second.value;
        }

        if (outer_) {
            return outer_->lookup(name);
        }

        throw std::runtime_error("Variable '" + name + "' is not defined");
    }

private:
    struct VariableBinding {
        JSValue value;
        bool is_const;
    };

    std::shared_ptr<Environment> outer_;
    std::unordered_map<std::string, VariableBinding> bindings_;
};

} // namespace w9::runtime
