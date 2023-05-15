## Do You See What I See

---

### Prerequisites
```
#### NOTE: submodule for opencv must be initialized (see root level README.md)
cd "<REPO_PATH>/third-party/opencv"
mkdir build
cd build
cmake ..
make -j4
sudo make install
```

---

### Compile and run
```
cd "<REPO_PATH>/do_you_see_what_i_see"
base='do_you_see_what_i_see' && g++ -std=c++14 "${base}.cpp" $(pkg-config --libs --cflags opencv4) -o "${base}.out" && "./${base}.out" '<PATH_TO_IMAGE>'
```

---

### Note

Within the file "do_you_see_me_now.cpp", I implemented `ConvertToFloatArray()` that takes image pixel data and converts to an array of 32-bit floating-point pixel data normalized to the range 0.0 to 1.0 and ordered as Red, Green, Blue, and Alpha, with the Alpha being set to 1.0 if the input image lacked an alpha channel.

`PrintData(data, size_in);` and `PrintFloatData(float_data, size_out);` are commented near the bottom of `do_you_see_what_i_see.cpp` and can be used to print input pixel data or normalized float pixel data.
