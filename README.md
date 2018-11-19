# Sandbox for template expressions

Expression : **-X+aY+bZ**

For now :
- `CLoop` : simple C loop, easily vectorized by compiler but not user friendly
- `ObjectOperator` : operator overloading on a vector-like class
- `VirtualObject` : class hierarchy to create AST at runtime
- `TemplateExpressions_1` : creating AST at compile time with CRTP
- `TemplateExpressions_2` : creating AST at compile time using visitor and dispatching
- `ConceptExpressions_1` : creating AST at compile time using concepts
- `ConceptExpressions_2` : creating AST at compile time using concepts and visitor and dispatching
- `Metaclass` (WIP) : overriding external collection in order to be used easily in user defined expression

# License
 
Copyright 2018 Vivien MILLE

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.