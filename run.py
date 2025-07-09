import os
import sys
import subprocess
import platform
import shutil

def is_windows():
    return platform.system() == "Windows"

def clean_build_dir(build_dir):
    cmake_cache = os.path.join(build_dir, "CMakeCache.txt")
    if os.path.exists(cmake_cache):
        print("🧹 Cleaning old CMake cache...")
        shutil.rmtree(build_dir)

def main():
    root_dir = os.path.dirname(os.path.abspath(__file__))
    build_dir = os.path.join(root_dir, "build")
    source_dir = root_dir  # указывает на CMakeLists.txt

    clean_build_dir(build_dir)
    os.makedirs(build_dir, exist_ok=True)

    # Step 1: Configure with CMake
    cmake_cmd = ["cmake", source_dir]
    print("🛠️  Configuring project with CMake...")
    result = subprocess.run(cmake_cmd, cwd=build_dir)
    if result.returncode != 0:
        print("❌ CMake configuration failed")
        sys.exit(1)

    # Step 2: Build
    build_cmd = ["cmake", "--build", "."]
    print("🔨 Building project...")
    result = subprocess.run(build_cmd, cwd=build_dir)
    if result.returncode != 0:
        print("❌ Build failed")
        sys.exit(1)

    # Step 3: Run
 #   executable = "Sim.exe" if is_windows() else "./Sim"
#    print(f"🚀 Running {executable}...")
 #   run_cmd = [executable] if is_windows() else [os.path.join(".", "Sim")]
  #  result = subprocess.run(run_cmd, cwd=build_dir)

   # if result.returncode != 0:
    #    print("⚠️ Program exited with errors.")

if __name__ == "__main__":
    main()
