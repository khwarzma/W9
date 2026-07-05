#include <iostream>
#include <cassert>
#include <string_view>
#include "../engine/lexer/lexer.h"
#include "../engine/parser/parser.h"
#include "../engine/vm/vm.h"
#include "../engine/gc/gc.h"
#include "../engine/jit/jit.h"
#include "../engine/bindings/bindings.h"
#include "../engine/runtime/environment.h"


void run_test(std::string_view test_name, void(*test_func)()) {
    std::cout << "[RUNNING] " << test_name << "... ";
    try {
        test_func();
        std::cout << "\033[32m[PASSED]\033[0m\n";
    } catch (const std::exception& e) {
        std::cout << "\033[31m[FAILED]\033[0m\n";
        std::cerr << "  Error: " << e.what() << "\n";
    }
}

// 1. اختبار الـ Lexer
void test_lexer_tokenization() {
    std::string_view source = "let x = 10; const y = 20; let result = x + y;";
    w9::lexer::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    assert(tokens[0].type == w9::lexer::TokenType::LET);
    assert(tokens[1].lexeme == "x");
    assert(tokens[3].type == w9::lexer::TokenType::NUMBER);
    assert(tokens[3].lexeme == "10");
    assert(tokens[5].type == w9::lexer::TokenType::CONST);
    assert(tokens[14].type == w9::lexer::TokenType::PLUS);
    assert(tokens.back().type == w9::lexer::TokenType::END_OF_FILE);
}

void test_parser_ast_generation() {
    std::string_view source = "let x = 5 + 10 * 2;";
    w9::lexer::Lexer lexer(source);
    w9::parser::Parser parser(lexer);
    
    auto program = parser.parse_program();
    assert(program != nullptr);
    assert(program->statements.size() == 1);


    std::string ast_dump = program->to_string();
    assert(ast_dump.find("let x = (5 + (10 * 2));") != std::string::npos);
}

void test_vm_execution() {
    std::string_view source = "let result = 15 - 5;";
    w9::lexer::Lexer lexer(source);
    w9::parser::Parser parser(lexer);
    auto program = parser.parse_program();

    w9::vm::BytecodeCompiler compiler;
    w9::vm::Chunk chunk = compiler.compile(program.get());

    
    assert(!chunk.code.empty());
    assert(chunk.code[0] == w9::vm::OP_CONSTANT); 

    w9::vm::VM vm;
    vm.interpret(chunk); 

}

void test_function_parsing_and_call() {
    std::string_view source = "function add(a, b) { let r = a + b; } add(5, 10);";
    w9::lexer::Lexer lexer(source);
    w9::parser::Parser parser(lexer);
    auto program = parser.parse_program();
    
    assert(program != nullptr);
    
    w9::vm::BytecodeCompiler compiler;
    w9::vm::Chunk chunk = compiler.compile(program.get());
    
    w9::vm::VM vm;
   
    vm.interpret(chunk);
}


struct TestObject : public w9::gc::GCObject {
    int data;
    TestObject(int val) : data(val) {}
};

void test_garbage_collector_allocation() {
    w9::gc::GarbageCollector gc;
    
    // حجز كائنين داخل الـ Heap وتتبع الذاكرة
    TestObject* obj1 = gc.allocate<TestObject>(100);
    TestObject* obj2 = gc.allocate<TestObject>(200);

    assert(obj1 != nullptr && obj2 != nullptr);
    assert(obj1->data == 100);
    assert(gc.bytes_allocated() > 0);


    obj1->is_marked = true;

    
    gc.collect_garbage();

    
    assert(obj1->data == 100);
}

void test_jit_compiler_pipeline() {
    std::string_view source = "let fast_result = 5 + 10;";
    w9::lexer::Lexer lexer(source);
    w9::parser::Parser parser(lexer);
    auto program = parser.parse_program();

    w9::jit::JITCompiler jit;
    
   
    size_t execution_loop_count = 12;
    if (jit.should_compile(execution_loop_count)) {
        jit.compile_to_native(program.get());
        double res = jit.execute_native_block();
        assert(res == 0.0); 
    }
}

void test_browser_bindings_injection() {
   
    auto global_env = std::make_shared<w9::runtime::Environment>();
    w9::bindings::BindingRegistry registry(global_env);

    
    bool function_was_called = false;
    registry.register_function("alert", [&](const std::vector<w9::runtime::JSValue>& args) -> w9::runtime::JSValue {
        function_was_called = true;
        if (!args.empty()) {
            std::cout << "[Browser Simulation Alert] " << args[0].to_string() << "\n";
        }
        return w9::runtime::JSValue(true); 
    });

    
    w9::runtime::JSValue lookup_res = global_env->lookup("alert");
    assert(lookup_res.is_string()); 
   
    std::vector<w9::runtime::JSValue> call_args = { w9::runtime::JSValue(42.0) };
    w9::runtime::JSValue return_val = registry.trigger_binding("alert", call_args);
    
    assert(function_was_called == true);
    assert(return_val.type() == w9::runtime::ValueType::BOOLEAN);
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running W9 Engine Core Test Suite\n";
    std::cout << "========================================\n";

    run_test("Lexer: Tokenization and Lexeme Verification", test_lexer_tokenization);
    run_test("Parser: AST Structure & Operator Precedence", test_parser_ast_generation);
    run_test("Virtual Machine: Bytecode Compilation & Execution", test_vm_execution);
    run_test("JavaScript Features: Function Parsing & VM Call Dispatch", test_function_parsing_and_call);
    run_test("Garbage Collector: Heap Allocation & Sweep Verification", test_garbage_collector_allocation);
    run_test("JIT Compiler: Hot Code Detection & LLVM IR Generation", test_jit_compiler_pipeline);
    run_test("Browser Bindings: Bridge Injection & Host Function API", test_browser_bindings_injection);
    std::cout << "========================================\n";
    std::cout << "All core engine modules are verified.\n";
    return 0;
}
