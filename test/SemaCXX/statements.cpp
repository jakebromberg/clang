// RUN: %clang_cc1 %s -fsyntax-only -pedantic -verify

void foo() { 
  return foo();
}

// PR6451 - C++ Jump checking
struct X {
  X();
};

void test2() {
  goto later;  // expected-error {{cannot jump}}
  X x;         // expected-note {{jump bypasses variable initialization}} 
later:
  ;
}

namespace PR6536 {
  struct A {};
  void a() { goto out; A x; out: return; }
}

void test3() {
    __asm__ ("":"+r" (test3)); // expected-error{{invalid lvalue in asm output}}
}

void test4();                // expected-note{{possible target for call}}
void test4(int) {            // expected-note{{possible target for call}}
  // expected-error@+1{{overloaded function could not be resolved}}
  __asm__ ("":"+r" (test4)); // expected-error{{invalid lvalue in asm output}}
}
void test5() {
  char buf[1];
  __asm__ ("":"+r" (buf));
}
