#pragma once

#include <vector>
#include <cstddef>
#include "../runtime/value.h" // تتبع لموقع ملف الـ Value في مخرجاتك السابقة

namespace w9::gc {

// الهيكل الأساسي لأي كائن يتم حشوه داخل الـ Heap المخصص للمحرك
struct GCObject {
    bool is_marked; // علم لتحديد ما إذا كان الكائن مستخدماً (لخوارزمية Mark-and-Sweep مستقبلاً)
    GCObject* next; // مؤشر لربط كافة الكائنات في القائمة المتصلة (Linked List) التابعة للـ Heap
};

class GarbageCollector {
public:
    GarbageCollector() : head_(nullptr), bytes_allocated_(0), threshold_(1024 * 1024) {} // 1MB threshold كبداية
    ~GarbageCollector();

    // دالة لحجز كائن جديد داخل الـ Heap وتتبع الذاكرة
    template<typename T, typename... Args>
    T* allocate(Args&&... args) {
        // حجز الذاكرة للكائن المخصص الذي يرث من GCObject
        T* object = new T(std::forward<Args>(args)...);
        
        // ربط الكائن بالقائمة المتصلة لجامع القمامة
        GCObject* gc_header = static_cast<GCObject*>(object);
        gc_header->is_marked = false;
        gc_header->next = head_;
        head_ = gc_header;

        bytes_allocated_ += sizeof(T);
        
        // إذا تجاوزنا الحد المسموح، نطلق عملية التنظيف تلقائياً
        if (bytes_allocated_ > threshold_) {
            collect_garbage();
        }

        return object;
    }

    void collect_garbage();
    void set_threshold(size_t limit) { threshold_ = limit; }
    size_t bytes_allocated() const { return bytes_allocated_; }

private:
    GCObject* head_;           // رأس القائمة المتصلة لكافة الكائنات المحجوزة
    size_t bytes_allocated_;   // حجم الذاكرة المستهلكة حالياً بالبايت
    size_t threshold_;         // الحد الأقصى للذاكرة قبل بدء التنظيف التلقائي

    void sweep();
};

} // namespace w9::gc