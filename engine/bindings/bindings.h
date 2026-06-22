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