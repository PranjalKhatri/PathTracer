# PathTracer
![A rendered image](./readme_images/cover.png)



A CPU-based path tracer implemented in C++ with multi-threading support, designed as a learning project in physically based rendering.
# Features
<ul>
<li>Multi-threaded CPU Execution: Leverages all available CPU cores for faster rendering.</li>
<li> Scene Support: Includes built‑in primitives (sphere, plane, Quad) and custom scene loading.</li>
<li>Configurable Rendering:
    <ul>
    <li>Adjustable samples per pixel (SPP)</li>
    <li>Adjustable camera and bg</li>
    <li>Adjustable Image resolution (width × height)</li>
    </ul>
<li>Simple Image Output: Saves rendered frames in PPM format.</li>
</ul>

# Getting Started
## Prerequisites
C++17 compliant compiler

Build system: CMake (≥ 3.27.8)

```bash
# Clone
git clone https://github.com/PranjalKhatri/PathTracer.git
cd PathTracer
cd cpu
```

```bash
mkdir build && cd build
cmake ..
cmake --build .
```
Based on your build system executable will be generated in corresponding directory(Debug for MSVC, in build folder for unix makeFiles etc..)

PathTraceroptimized.exe will have fastmath and o3 whereas the pathtracer.exe is the one without compiler optimizations.