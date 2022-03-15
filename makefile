launch:	compil start
	

compil:
	g++ hash_main.cpp hash.cpp list_for_str/list.cpp -o a.exe

start:
	./a.exe

