.PHONY: run build clean

obj_dir = .build/obj
bin_dir = .build/bin

cpp_std = -std=c++11


run : build
	$(bin_dir)/main

build : $(bin_dir)/main $(bin_dir)/creator $(bin_dir)/reporter
	

clean : 
	rm -r .build
	mkdir -p $(bin_dir) $(obj_dir)/main $(obj_dir)/creator $(obj_dir)/reporter .build/data

$(bin_dir)/main : $(obj_dir)/main/main.o
	clang++ $(cpp_std) -o $(bin_dir)/main $(obj_dir)/main/main.o

$(bin_dir)/creator : $(obj_dir)/creator/main.o
	clang++ $(cpp_std) -o $(bin_dir)/creator $(obj_dir)/creator/main.o

$(bin_dir)/reporter : $(obj_dir)/reporter/main.o
	clang++ $(cpp_std) -o $(bin_dir)/reporter $(obj_dir)/reporter/main.o


$(obj_dir)/main/main.o : src/main/main.cpp
	clang++ $(cpp_std) -c src/main/main.cpp -o $(obj_dir)/main/main.o

$(obj_dir)/creator/main.o : src/creator/main.cpp
	clang++ $(cpp_std) -c src/creator/main.cpp -o $(obj_dir)/creator/main.o

$(obj_dir)/reporter/main.o : src/reporter/main.cpp
	clang++ $(cpp_std) -c src/reporter/main.cpp -o $(obj_dir)/reporter/main.o
