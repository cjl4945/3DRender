# 🎮 3D Renderer  

## 📌 Overview  
This project is a **custom-built 3D rendering engine** developed in **C++**, leveraging **OpenGL and SDL2** for real-time graphics. Designed for **mid-level software engineers**, it serves as both an **educational tool** and a **foundation for advanced rendering techniques**.  

## ✨ Features  
✔️ **Modular 3D Engine** – Clean separation of rendering, camera, shader, and resource management components.  
✔️ **Dynamic Lighting & Shading** – Supports **flat** and **Gouraud shading** with full transformation support.  
✔️ **Asynchronous Resource Loading** – Uses **multithreaded resource management** for efficient texture handling.  
✔️ **Real-Time UI Controls** – Integrated **ImGui** for **live parameter tweaking** and debugging.  
✔️ **Camera System & Z-Buffering** – Perspective projection with proper **depth ordering** and smooth movement.  
✔️ **Multithreaded Rendering (Optional)** – Optimized performance for **handling complex 3D scenes**.  

## 🛠️ Technologies Used  
- **C++17** – Core programming language for performance and control.  
- **OpenGL (or Custom Rasterizer)** – Implements the rendering pipeline.  
- **SDL2** – Manages window creation and input handling.  
- **GLM** – Handles matrix and vector math.  
- **stb_image** – Loads textures efficiently.  
- **ImGui** – Provides **real-time UI** for debugging and scene control.    

## 🚀 Getting Started  

### ✅ Prerequisites  
Ensure you have the following installed on your system:  
- **C++17 or later**  
- **CMake**  
- **SDL2 & OpenGL**  

### 🔧 Installation  
1️⃣ Clone the repository:  
   ```bash
   git clone https://github.com/cjl4945/3DRender.git
   ```  
2️⃣ Navigate into the project directory:  
   ```bash
   cd 3DRender
   ```  
3️⃣ Build the project:  
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```  

### 🎮 Running the Renderer  
To launch the renderer, run:  
```bash
./3DRender
```  

## 🎮 Controls & Usage  
🕹️ **WASD + Mouse** – Move and look around the scene.  
🔹 **ESC** – Toggle pause menu (ImGui-based UI for **real-time parameter adjustments**).  
🎨 Modify shader settings to **test different lighting effects dynamically**.  

## 🚧 Future Enhancements  
📌 Implement **Phong shading** for more realistic lighting.  
📌 Add **real-time shadows** using shadow mapping.  
📌 Optimize performance with **spatial partitioning structures**.  
📌 Support additional **3D model formats**.  

## 👤 Contributors  
Developed by **Chase Lewis**.  

## 📜 License  
This project is licensed under the **MIT License**. See the `LICENSE` file for details. 
