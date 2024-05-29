
release:
	#bazel build --cxxopt=-std=c++17 //:main
	bazel build --config=linux_asan --cxxopt=-std=c++17 //:main
