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