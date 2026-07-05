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
#include "bindings.h"
#include <iostream>

namespace w9::bindings {

void BindingRegistry::register_function(std::string_view name, HostFunction func) {
    std::string func_name(name);
    
    // حفظ الدالة في القاموس الداخلي للجسر
    host_functions_[func_name] = func;

    // حقن معرف الدالة داخل الـ Runtime Environment الخاص بجافاسكريبت ككائن متاح للـ VM
    // نضع قيمة رقمية أو كائن رمزي يدل على أنها دالة أصلية (Native Function)
    global_env_->define(func_name, runtime::JSValue(func_name + "() [Native Code]"), true);
    
    std::cout << "[Bindings] Successfully injected External Host Function: " << func_name << "\n";
}

runtime::JSValue BindingRegistry::trigger_binding(std::string_view name, const std::vector<runtime::JSValue>& args) {
    std::string func_name(name);
    auto it = host_functions_.find(func_name);
    if (it != host_functions_.end()) {
        // تنفيذ دالة الـ C++ الأصلية مباشرة وإرجاع نتيجتها للمحرك
        return it->second(args);
    }
    return runtime::JSValue(); // undefined في حال عدم الوجود
}

} // namespace w9::bindings
