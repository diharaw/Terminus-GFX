# Terminus-GFX

[![License: MIT](https://img.shields.io/packagist/l/doctrine/orm.svg)](https://opensource.org/licenses/MIT)

## What is it?
A cross-platform graphics API abstraction layer which provides you with an API similar to Vulkan across all backends, in order to leverage almost all the best features of each graphics API while maintaing fine-grained control and portablility.

### NOTE: This library is undergoing large changes and is currently not in a usable state.

## Backends
* OpenGL (4.1 - 4.6) [80%]
* OpenGL ES 2.0 [0%]
* OpenGL ES 3.0 [50%]
* Direct3D 11 [60%]
* Direct3D 12 [0%]
* Vulkan [0%]
* Metal [40%]
* WebGL 1.0 [0%]
* WebGL 2.0 [0%]

## Building
The entire build process is handled through CMake. At generation time, specify the graphics API backend you wish to use. If you don't select one, the best fit for your operating system will be automatically chosen.

## License
```
Copyright (c) 2018 Dihara Wijetunga

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```