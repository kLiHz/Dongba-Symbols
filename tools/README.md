# Practical Tools

## Grid Printer

| Name       | Function                                                    |
| ---------- | ----------------------------------------------------------- |
| grid.cpp   | Draw grid on an image for user to write symbols on.         |

- `grid` supports customizing grid rows, columns and resolution (length of a square), as well as grid line width, color, background color.
- Currently, the corresponing grid cutter requires that the result grid image to be written symbols on with softwares that will keep the original image resolution (e.g. Photoshop). PNG format is recommended.
- To compile and run it, `boost-program-options`, **C++17** and **OpenCV 4** is required.
- This program is more like demostrating concept. More user-friendly programs (for example, one running in web browsers) is welcome.

Example:

```console
$ ./grid -l 256 -b 10 -c 4 -r 8 -f grid1.png
Rows:                     8
Cols:                     4
Pixel in length:          256 px
Grid line width:          19 px
Grid line color (RGB):    [0, 255, 0]
Background color (RGB):   [255, 255, 255]
Display Only:             false
Output filename:          grid1.png
```

## Grid Cutter

| Name       | Function                                                    |
| ---------- | ----------------------------------------------------------- |
| cut.cpp    | Cut grid image into slices.                                 |

- Currently this grid cutter takes the same options (rows, columns, grid line thickness and grid resolution) as what is used to generate the grid image, and cut the image (whose resolution should remain unchanges) into slices.
- That is to say, this program should be use together with the "Grid Painter" above.
- To compile and run it, **OpenCV** and **C++17** is required.
- This program is more like demostrating a concept. A more user-friendly program (for example, one running in web browsers) that can read printed grid from paper through camera or scanner is welcome.

Example:

```console
$ ./cut -l=256 -b=10 -c=4 -r=8 -i='grid1.png' -o='output/grid1_.png'
Rows:                         8
Cols:                         4
Pixel in length:              256 px
Grid line thickness:          10 px
Grid line width:              19 px
Input filename:               7.png
Output:                       output/grid1_.png
Output prefix:                output/grid1_
Output extension              .png
```

## mkdir

| Name       | Function                                                    |
| ---------- | ----------------------------------------------------------- |
| mkdir.py   | Generating sequential directories in the filesystem.        |

- `mkdir` can help user generates sequential 4-digit-number-named directories in the filesystem. 
- To run this script, **Python 3** is required.

Example:

```console
$ py mkdir.py ./output/ 995 1016
```

## rename

| Name       | Function                                                    |
| ---------- | ----------------------------------------------------------- |
| rename.cpp | Renaming all files in certain subdirectories.               |

- `rename` can help user renaming all files under certain subdirectories which all lies in a same `root` directory.
- To compile and run it, **C++17** is required.

Example:

```console
PS> ./rename 'D:\test\output' 19011443                                     
Root directory is: D:\test\output
Files will be renamed as:
    D:\test\output/<subdir>/19011443_<subdirname>_<i>.<extension>
- Now entering: "D:\\test\\output\\1760"
- Now entering: "D:\\test\\output\\1761"
- Now entering: "D:\\test\\output\\1762"
Finished!
```


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

