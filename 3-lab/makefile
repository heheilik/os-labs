.PHONY: run build clean

obj_dir = .build/obj
bin_dir = .build/bin

cpp_std = -std=c++11


run : build
	$(bin_dir)/main

build : $(bin_dir)/main
	
clean :
	rm -r .build
	mkdir -p $(bin_dir) $(obj_dir)


$(bin_dir)/main : $(obj_dir)/main.o
	clang++ $(cpp_std) -lboost_thread-mt -o $(bin_dir)/main $(obj_dir)/main.o


$(obj_dir)/main.o : src/main.cpp
	clang++ $(cpp_std) -c src/main.cpp -o $(obj_dir)/main.o
