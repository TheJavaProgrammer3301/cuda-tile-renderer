TARGET = MyCUDAProject
SRC = src/main.cu

all:
	nvcc -o $(TARGET) $(SRC)
clean:
	rm -f $(TARGET)
