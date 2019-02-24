//
// Created by gzbbxu on 2019/2/23.
//

#ifndef JNIDEMO_COMPILER_H
#define JNIDEMO_COMPILER_H

// Use this in the private section of a class declaration to ensure
// that the corresponding objects cannot be copy-constructed or
// assigned. For example:
//
//   class Foo {
//   public:
//       .... public declarations
//   private:
//       DISALLOW_COPY_AND_ASSIGN(Foo)
//       .... other private declarations
//   };
//


#define DISALLOW_COPY_AND_ASSIGN(T)  \
    T(const T& other); \
    T& operator=(const T& other)
#endif //JNIDEMO_COMPILER_H
