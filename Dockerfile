FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake\
    g++-9\
    pkg-config\
    libopencv-dev\
    libstdc++-9-dev -V

RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 100

# Set working directory
WORKDIR /app

# Copy source code to the container
COPY . .

# Install necessary tools and build OpenCV manually
RUN apt-get update && apt-get install -y \
    wget \
    unzip

# Download OpenCV
RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.5.3.zip \
    && unzip opencv.zip \
    && rm opencv.zip

# Build OpenCV
RUN cd opencv-4.5.3 \
    && mkdir build \
    && cd build \
    && cmake -G 'Unix Makefiles' .. \
    && make -j$(nproc) \
    && make install

# Build the program
RUN g++ -std=c++14 -o do_you_see_what_i_see do_you_see_what_i_see.cpp `pkg-config --cflags --libs opencv4`

# Set environment variables
ENV OPENCV_DIR=/usr/local
ENV LD_LIBRARY_PATH=/usr/local/lib:${LD_LIBRARY_PATH}

# Make the script executable
RUN chmod +x /app/entrypoint.sh

# Set the entry point
ENTRYPOINT ["/bin/bash", "-c", "/app/entrypoint.sh \"$1\"", "--"]
CMD []



