## CVPP  -  Computer Vision for C++ ##
### *Generic Machine Learning, Computer Vision and Robotics Library for C++*

---------------------------------------------------------------------------------------  
CVPP is a C++ library forked from [Vitor Campanholo Guizilini](https://bitbucket.org/vguizilini/cvpp/src/master/) that focuses on easy prototyping and testing. It introduces new classes that wrap around the API of various well-known open-source libraries and provide useful functionalities, that significantly increase productivity without compromising performance.

1. **Containers** - The base classes of CVPP, acting as building blocks for everything else. They perform operations using inherited methods and implements new ones that facilitate common calculations found in scientific research.
	* **Matrix** - Basic fixed-size data storage class, that maintains a pointer to an Eigen::Matrix structure.
	* **Vector** - Basic dynamic-size data storage class, that maintains a pointer to a std::vector structure.
	* **Image** - Basic image data storage class, that maintains a pointer to a cv::Mat structure.
	* **Device** - Basic GPU data storage class, that maintains a pointer to an arrayfire::array structure.
	
2. **Interfaces** - The input/output classes of CVPP, managing data visualization, user interaction and access to peripherals.
	* **CPPlot** - Basic plotting class, that uses OpenGL and SDL2 to generate environments for image reproduction,  2D/3D matlab-like graphics and 3D virtual worlds.
	* **CPPture** - Basic camera class, that uses OpenCV to access USB devices and GStreamer to access network streams.
	* **CPPrint** - Basic recording class, that uses OpenCV to store visual representations of data as individual images or encoded video.

---------------------------------------------------------------------------------------  
# *Installation*   

The CVPP library was tested on MacOS, but it should compile fine in other distributions.

From a fresh installation, do the following:

### Base Installation

##### INSTALL SYSTEM TOOLS

```
sudo apt-get install build-essential
sudo apt-get install git cmake cmake-gui
```

##### CLONE CVPP REPOSITORY

```
cd /path/to/cvpp_folder
git clone https://bitbucket.org/vguizilini/cvpp
```

##### INSTALL BASE DEPENDENCIES

```
sudo apt-get install libeigen3-dev
sudo apt-get install libboost-all-dev
sudo apt-get install zlib1g-dev
```

### Test Base Installation

##### SET CVPP PATH

```
gedit /path/to/cvpp_folder/cvpp/cmake/CVPP.cmake
(modify: CPP_INCLUDE_DIR "/path/to/cvpp_folder" )
```

##### COMPILE DEMO

```
cd /path/to/cvpp_folder/cvpp/demos/tutorials
mkdir build
cd build
cmake ..
make 
```

If it worked, you have now access to the basic version of CVPP. 
If you want more functionality, consider installing the following extensions (most demos will only
work if you have one or more of these extensions installed).

-----------------------------------------------------------------------------------------
### CUDA (GPU calculations)

##### INSTALL NVIDIA DRIVER

```
sudo add-apt-repository ppa:graphics-drivers/ppa
sudo apt-get update
sudo apt-get install nvidia-XXX-dev
reboot
```

##### DOWNLOAD CUDA TOOLKIT

[https://developer.nvidia.com/cuda-downloads](Link URL)

##### INSTALL CUDA TOOLKIT
```
sudo sh cuda_XXX.run
(Don't install NVIDIA Driver)
(install samples in /path/to/samples)
```

##### TEST INSTALLATION

```
cd /path/to/samples/1_Utilities/deviceQuery
make
./deviceQuery
```

##### EDIT .BASHRC

```
gedit ~/.bashrc
export PATH=$PATH:/usr/local/cuda/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib64
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/nvvm/lib64
```

-----------------------------------------------------------------------------------------
### MKL (Faster CPU calculations)

##### DOWNLOAD INTEL MKL

https://software.intel.com/en-us/intel-mkl

##### INSTALL INTEL MKL

```
sudo ./install_GUI.sh
(Follow instructions)
```

##### DETERMINE LINKING LIBRARIES

[https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor](Link URL)

-----------------------------------------------------------------------------------------
### OpenCV (Support to OpenCV library)

##### CLONE OPENCV REPOSITORIES

```
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
```

##### RUN CMAKE FOR FIRST CONFIGURATION

```
cd opencv
mkdir build
cd build
cmake ..
```

##### INSTALL DEPENDENCIES

```
sudo apt-get install libjpeg8-dev libtiff5-dev libjasper-dev libpng12-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libxvidcore-dev libx264-dev
sudo apt-get install libgtk-3-dev libxmu-dev 
sudo apt-get install libatlas-base-dev gfortran
sudo apt-get install libgstreamer1.0-dev
... any others you would like to add ...
```

##### RUN CMAKE-GUI TO CHANGE CONFIGURATION

```
cmake-gui ..
( modify: OPENCV_EXTRA_MODULES_PATH = /path/to/opencv_contrib/modules )
```

##### INSTALL CURRENT CONFIGURATION

```
make
sudo make install
```

-----------------------------------------------------------------------------------------
### ArrayFire (GPU calculations)

##### CLONE ARRAYFIRE REPOSITORY

```
git clone https://github.com/arrayfire/arrayfire.git
git submodule init
git submodule update
```

##### INSTALL DEPENDENCIES

```
sudo apt-get install libopenblas-dev libfftw3-dev liblapacke-dev
sudo apt-get install opencl-headers
sudo apt-get install libglfw3-dev
```

##### CONFIGURE AND INSTALL

```
cd arrayfire
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make 
sudo make install
```

-----------------------------------------------------------------------------------------
### OpenGL (Graphical interface) 

```
sudo apt-get install libsdl2-dev freeglut3-dev libflann-dev
```

-----------------------------------------------------------------------------------------
### VLFeat (Support to VLFeat library) 

```
sudo apt-get install libvlfeat-dev
```

-----------------------------------------------------------------------------------------
### NLOpt (Non-linear optimization) 

```
sudo apt-get install libnlopt-dev
```

-----------------------------------------------------------------------------------------
### CURL (File transfer) 

```
sudo apt-get install libcurl4-openssl-dev
```

---------------------------------------------------------------------------------------  
### Credit ###

This repo is forked from Vitor Campanholo Guizilini [https://bitbucket.org/vguizilini/cvpp/src/master/] with the following additional enhancements:

### TODO ###
- [ ] Compatible with OpenCV 4
- [ ] Test on Ubuntu 16.04
- [ ] Compatible with Metal on MacOS
- [x] Installation tips for MacOS




