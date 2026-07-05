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

#include "../runtime/value.h"
#include "../runtime/environment.h" // تتبع لملف البيئة الخاص بالـ Scopes
#include <string_view>
#include <functional>

namespace w9::bindings {

// تعريف نوع الدالة التي يمكن استقبالها من الـ C++ (Host Function)
// تستقبل قائمة من معاملات جافاسكريبت وتُرجع قيمة جافاسكريبت
using HostFunction = std::function<runtime::JSValue(const std::vector<runtime::JSValue>&)>;

class BindingRegistry {
public:
    // ربط المحرك ببيئة الـ Runtime الخارجية
    explicit BindingRegistry(std::shared_ptr<runtime::Environment> env) : global_env_(env) {}

    // دالة تسجيل دالة C++ أصلية داخل بيئة جافاسكريبت (مثال: تسجيل console.log)
    void register_function(std::string_view name, HostFunction func);

    // دالة محاكاة استدعاء دالة محقونة من الخارج
    runtime::JSValue trigger_binding(std::string_view name, const std::vector<runtime::JSValue>& args);

private:
    std::shared_ptr<runtime::Environment> global_env_;
    std::unordered_map<std::string, HostFunction> host_functions_;
};

} // namespace w9::bindings
