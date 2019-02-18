#----- compile with static library. Output file size is 3MB and 4.5MB.---------
#g++ -std=c++11 -o example_first_peer.out example_first_peer.cpp -I../include ../build/debug/src/kademlia/libkademlia_static.a -lboost_system -lpthread -lcrypto -DKADEMLIA_ENABLE_DEBUG

#g++ -std=c++11 -o example_second_peer.out example_second_peer.cpp -I../include ../build/debug/src/kademlia/libkademlia_static.a -lboost_system -lpthread -lcrypto -DKADEMLIA_ENABLE_DEBUG

#----- compile with dynamic library. Output file size is 0.17MB and 0.21MB, but require add file path to LD_LIBRARY_PATH and export it.---------
g++ -std=c++11 -o example_first_peer.out example_first_peer.cpp -I../include -L../build/debug/src/kademlia/ -lkademlia -lboost_system -lpthread -lcrypto -DKADEMLIA_ENABLE_DEBUG

g++ -std=c++11 -o example_second_peer.out example_second_peer.cpp -I../include -L../build/debug/src/kademlia/ -lkademlia -lboost_system -lpthread -lcrypto -DKADEMLIA_ENABLE_DEBUG
