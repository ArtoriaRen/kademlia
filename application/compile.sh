g++ -std=c++11 -o example_first_peer.out example_first_peer.cpp -I../include ../build/debug/src/kademlia/libkademlia_static.a -lboost_system -lpthread -lcrypto

g++ -std=c++11 -o example_second_peer.out example_second_peer.cpp -I../include ../build/debug/src/kademlia/libkademlia_static.a -lboost_system -lpthread -lcrypto
