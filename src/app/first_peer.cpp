/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   first_peer.cpp
 * Author: liuyangren
 *
 * Created on February 18, 2019, 5:18 PM
 */

#include <cstdlib>
#include <future>
#include <iostream>
#include <iterator>
#include <vector>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/v6_only.hpp>
#include <boost/system/system_error.hpp>
#include "../../include/kademlia/error.hpp"
#include "../../include/kademlia/endpoint.hpp"
#include "../../include/kademlia/first_session.hpp"
//using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    //-----------Initialization--------
        // The session need to know at least one member of the
        // distributed table to find neighbors.
        kademlia::endpoint const initial_peer_ipv4{ "127.0.0.1", 27980 };
        kademlia::endpoint const initial_peer_ipv6{ "::1", 27981 };

        kademlia::first_session f{ initial_peer_ipv4, initial_peer_ipv6};
        std::cout << "setting up first peer complete." << std::endl;


        // Run the library main loop in a dedicated thread.
        auto main_loop_result = std::async( std::launch::async
                        , &kademlia::first_session::run, &f );
        std::cout << "initialized" << std::endl;


        //-------------clean up ---------------
        // Once we've finished, abort the session::run()
        // blocking call.
//      f.abort();

        auto failure = main_loop_result.get();
        std::cout << failure.message()<< std::endl;
        if ( failure != kademlia::RUN_ABORTED )
                std::cerr << failure.message() << std::endl;

    return 0;
}

