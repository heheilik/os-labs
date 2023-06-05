.PHONY: run build clean test
.IGNORE: clean


cpp_std = -std=c++14
clang_call = clang++ $(cpp_std)

test_libs = -lgtest -lgtest_main


obj_dir  = .build/obj
bin_dir  = .build/bin
test_dir = .build/test

main_target_obj = $(obj_dir)/main.o $(obj_dir)/state.o


run : build
	.build/bin/main

build : $(bin_dir)/main

test : build
	$(clang_call) $(test_libs) -c -o $(test_dir)/state_test.o test/state_test.cpp
	$(clang_call) $(test_libs) -o $(test_dir)/state_test $(test_dir)/state_test.o $(obj_dir)/state.o
	.build/test/state_test --gtest_color=yes

clean :
	rm -r .build
	mkdir -p $(bin_dir) $(obj_dir) $(test_dir)


$(bin_dir)/main : $(main_target_obj)
	$(clang_call) -o $(bin_dir)/main $(main_target_obj)

$(obj_dir)/main.o : src/main.cpp $(obj_dir)/state.o
	$(clang_call) -c -o $(obj_dir)/main.o src/main.cpp

$(obj_dir)/state.o : src/state.cpp src/state.hpp
	$(clang_call) -c -o $(obj_dir)/state.o src/state.cpp
