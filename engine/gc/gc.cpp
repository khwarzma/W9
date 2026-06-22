#include "gc.h"
#include <iostream>

namespace w9::gc {

GarbageCollector::~GarbageCollector() {
    // تنظيف كافة الكائنات المتبقية في الذاكرة عند إغلاق المحرك
    GCObject* current = head_;
    while (current != nullptr) {
        GCObject* next = current->next;
        delete current;
        current = next;
    }
}

void GarbageCollector::collect_garbage() {
    std::cout << "[GC] Starting Garbage Collection Cycle...\n";
    std::cout << "[GC] Bytes before collection: " << bytes_allocated_ << "\n";

    // الخطوة 1: الـ Mark (سيتم ربطها بـ Root Set والـ Execution Stack الخاص بالـ VM في الخطوات المتقدمة)
    // حالياً نترك الكائنات بدون مَرك محاكاةً لوجود كائنات غير مستخدمة (Unreachable)

    // الخطوة 2: الـ Sweep (تنظيف الذاكرة غير المستخدمة)
    sweep();

    std::cout << "[GC] Garbage Collection Finished.\n";
    std::cout << "[GC] Bytes after collection: " << bytes_allocated_ << "\n";
}

void GarbageCollector::sweep() {
    GCObject** previous = &head_;
    GCObject* current = head_;

    while (current != nullptr) {
        if (current->is_marked) {
            // الكائن مستخدم: نقوم بإلغاء العلامة للمرة القادمة، وننتقل للكائن التالي
            current->is_marked = false;
            previous = &current->next;
            current = current->next;
        } else {
            // الكائن غير مستخدم (Unreachable): نقوم بفكه من القائمة وحذفه من الذاكرة
            GCObject* unreached = current;
            current = current->next;
            *previous = current;

            // في المحرك الحقيقي، نحتاج لحساب الحجم الفعلي للكائن المحذوف، هنا نستخدم حجم تقريبي
            bytes_allocated_ -= sizeof(*unreached); 
            delete unreached;
        }
    }
}

} // namespace w9::gc
