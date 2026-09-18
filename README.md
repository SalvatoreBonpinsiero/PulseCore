<div align="center">

  <h1>⚡ PulseCore</h1>

  <p>
    <strong>Modern, standalone network and telemetry sentinel dashboard</strong>
  </p>

  <p>
    <a href="https://github.com/SalvatoreBonpinsiero/PulseCore/actions/workflows/release.yml">
    </a>
    <img src="https://img.shields.io/badge/C%2B%2B-20-00599C?logo=c%2B%2B&logoColor=white" alt="C++20" />
    <img src="https://img.shields.io/badge/GUI-Dear%20ImGui-blueviolet" alt="Dear ImGui" />
    <img src="https://img.shields.io/badge/Platform-Windows%20x64-0078D6?logo=windows&logoColor=white" alt="Platform" />
    <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License" />
  </p>

  <p>
    PulseCore is an ultra-fast hardware and socket telemetry tool engineered in <b>C++20</b> with <b>Dear ImGui</b>, <b>GLFW</b>, and hardware-accelerated <b>OpenGL 3.3</b>.
  </p>

  <br />

  <img src="https://raw.githubusercontent.com/SalvatoreBonpinsiero/PulseCore/refs/heads/main/prev.png" alt="PulseCore Dashboard Preview" width="850" style="max-width: 100%; border-radius: 8px;" />

</div>

<hr />

<h2>✨ Features</h2>

<table>
  <tr>
    <td width="50%">
      <h3>🔒 Fully Standalone</h3>
      <p>Statically linked C++ Runtime (<code>/MT</code>). Runs out-of-the-box on clean Windows installations without missing DLL errors (<code>VCRUNTIME140.dll</code>).</p>
    </td>
    <td width="50%">
      <h3>📦 Zero-Config Setup</h3>
      <p>Automated dependency management via CMake <code>FetchContent</code>. Downloads and compiles GLFW and ImGui automatically.</p>
    </td>
  </tr>
  <tr>
    <td width="50%">
      <h3>🪟 Clean GUI Experience</h3>
      <p>Subsystem set to Windows GUI. Launches instantly without flashing or keeping open a background black command-prompt window.</p>
    </td>
    <td width="50%">
      <h3>🎨 Custom Zinc/Violet Theme</h3>
      <p>Fine-tuned interface styling with custom rounded frames, low-contrast borders, and real-time ring buffer latency plotting.</p>
    </td>
  </tr>
</table>

<hr />

<h2>🚀 Getting Started</h2>

<h3>Method 1: One-Click Build (Windows)</h3>
<p>Clone the repository and run the automated batch script:</p>

<pre><code>git clone https://github.com/SalvatoreBonpinsiero/PulseCore.git
cd PulseCore
build.bat</code></pre>

<h3>Method 2: Manual CMake Build</h3>
<pre><code>git clone https://github.com/SalvatoreBonpinsiero/PulseCore.git
cd PulseCore
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release</code></pre>

<p>The executable will be generated at <code>build/Release/PulseCore.exe</code>.</p>

<hr />

<h2>📥 Prebuilt Binaries</h2>

<p>
  Standalone <code>PulseCore.exe</code> files are compiled automatically by CI workflows. You can download the latest version from:
</p>

<ul>
  <li><b><a href="https://github.com/SalvatoreBonpinsiero/PulseCore/releases">GitHub Releases</a></b> — Stable versioned tags.</li>
  <li><b><a href="https://github.com/SalvatoreBonpinsiero/PulseCore/actions">GitHub Actions Artifacts</a></b> — Bleeding-edge builds for each commit.</li>
</ul>

<hr />

<div align="center">
  <p>Developed with ❤️ by <a href="https://github.com/SalvatoreBonpinsiero"><b>Salvatore Bonpensiero</b></a></p>
</div>
