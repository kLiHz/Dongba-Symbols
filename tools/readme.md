# Practical Tools



## resize

| Name       | Function                                                    |
| ---------- | ----------------------------------------------------------- |
| resize.cpp | recursively resize and rewrite all images under a directory |

- `resize` receives a parameter from the command line and use it as `input_path`. If not received, it will ask user to manually input the name of the working directory.
- To compile and run it, **OpenCV** and **C++17** is required.

Example:

```bash
g++ resize.cpp -o resize -std=c++17 `pkg-config --libs opencv4`
./resize ../images
```

